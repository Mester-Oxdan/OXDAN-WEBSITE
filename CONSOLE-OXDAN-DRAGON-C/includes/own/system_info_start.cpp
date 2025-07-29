#include <windows.h>
#include <shlobj_core.h>
#include "all_diclarations.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <comdef.h>
#include <Wbemidl.h>
#include <string>
#include <set>

#pragma comment(lib, "wbemuuid.lib")

// Include the necessary Boost headers
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

void query_wmi(const BSTR query, const BSTR field, const wchar_t* label)
{
	HRESULT hres;

	// Initialize COM
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres)) {
		
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!COM init failed!)\n");
		printf("\033[0;37m");
		               
		check_start_start();
	}

	// Initialize Security
	hres = CoInitializeSecurity(NULL, -1, NULL, NULL,
		RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL, EOAC_NONE, NULL);
	if (FAILED(hres)) {
		
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Security init failed!)\n");
		printf("\033[0;37m");
		
		CoUninitialize();
		check_start_start();
	}

	// Get WMI Locator
	IWbemLocator* pLoc = nullptr;
	hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hres)) {
		
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!WbemLocator creation failed!)\n");
		printf("\033[0;37m");
		CoUninitialize();
		check_start_start();
	}

	// Connect to WMI namespace
	IWbemServices* pSvc = nullptr;
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"),
		NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hres)) {
		
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!WMI connection failed!)\n");
		printf("\033[0;37m");
		 
		pLoc->Release();
		CoUninitialize();
		check_start_start();
	}

	// Set proxy
	hres = CoSetProxyBlanket(pSvc,
		RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
		RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL, EOAC_NONE);
	if (FAILED(hres)) {
		
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Proxy blanket failed!)\n");
		printf("\033[0;37m");
		 
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		check_start_start();
	}

	// Perform query
	IEnumWbemClassObject* pEnumerator = nullptr;
	hres = pSvc->ExecQuery(
		_bstr_t("WQL"),
		query,
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	if (FAILED(hres)) {
		
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Query failed!)\n");
		printf("\033[0;37m");
		 
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		check_start_start();
	}

	// Get result
	IWbemClassObject* pclsObj = nullptr;
	ULONG uReturn = 0;
	std::set<std::wstring> printed;

	while (pEnumerator) {
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (uReturn == 0) break;

		if (field != nullptr) {
			VARIANT vtProp;
			hr = pclsObj->Get(field, 0, &vtProp, 0, 0);
			if (SUCCEEDED(hr) && vtProp.vt == VT_BSTR) {
				std::wstring value(vtProp.bstrVal);
				if (printed.insert(value).second) {
					std::wcout << label << L": " << value << std::endl;
				}
			}
			VariantClear(&vtProp);
		}

		pclsObj->Release();
	}


	// Cleanup
	pSvc->Release();
	pLoc->Release();
	pEnumerator->Release();
	CoUninitialize();
}

void system_info_start()
{
	if (IsUserAnAdmin() == true)
	{
		printf("\n");
		printf("You are: 'Super User/Admin' ");
		Sleep(1);
	}

	else if (IsUserAnAdmin() == false)
	{
		printf("\n");
		printf("You are: 'User' \n");
		Sleep(1);
	}
	printf("Language: 'English' \n");
	Sleep(1);

	#ifdef linux

	printf("System: 'Linux' \n");
	Sleep(1);
	
	#endif

	#ifdef _WIN32

	printf("System: 'Windows' \n");
	Sleep(1);

	#else

	printf("System: 'Unknown' \n");
	Sleep(1);

	#endif

	char szPath[128] = "";
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	gethostname(szPath, sizeof(szPath));
	printf("Hostname: ");
	printf("%s", szPath);
	Sleep(1);
	printf("\n");
	WSACleanup();

	WSADATA wsa;
	char hostname[128];
	char* IP;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Error code: %d ", WSAGetLastError(), "!)\n");
		printf("\033[0;37m");
		               

	}

	if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR)
	{

		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Error: %d", WSAGetLastError(), "!)\n");
		printf("\033[0;37m");
		               


	}

	struct hostent* he;
	struct in_addr** addr_list;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		printf("(!Get host by name failed: %d ", WSAGetLastError(), "!)\n");
		printf("\033[0;37m");
		               

	}

	addr_list = (struct in_addr**)he->h_addr_list;

	int i = 0; addr_list[i] != NULL;
	IP = inet_ntoa(*addr_list[i]);
	printf("IPv4 Address: %s\n", IP);
	Sleep(1);
	WSACleanup();

	string url = "http://ip-api.com/json/"; // http://ip-api.com/json/
	string response;

	try {
		// Use the C++ standard library to make a HTTP GET request
		array<char, 128> buffer;
		string command = "curl -s " + url;
		unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(command.c_str(), "r"), _pclose);
		if (!pipe) {
			throw runtime_error("popen() failed!");
		}

		while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
			response += buffer.data();
		}

	}
	catch (const exception& e) {
		//cerr << "Error: " << e.what() << endl;
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		cout << "(!Error: " << e.what() << "!)\n";
		printf("\033[0;37m");
		               
	}

	// Parse the JSON response using Boost.PropertyTree
	boost::property_tree::ptree pt;
	istringstream is(response);
	read_json(is, pt);

	string query = pt.get<string>("query");

	cout << "Network Ip Address: \033[0;37m" << query << endl;
	Sleep(1);
	WSACleanup();
	
	// CPU
	query_wmi(_bstr_t(L"SELECT Name FROM Win32_Processor"), _bstr_t(L"Name"), L"CPU Name");
	Sleep(1);

	// GPU
	query_wmi(_bstr_t(L"SELECT Name FROM Win32_VideoController"), _bstr_t(L"Name"), L"GPU Name");
	Sleep(1);

	// RAM
	query_wmi(_bstr_t(L"SELECT Manufacturer FROM Win32_PhysicalMemory"), _bstr_t(L"Manufacturer"), L"RAM Manufacturer");
	Sleep(1);
	query_wmi(_bstr_t(L"SELECT PartNumber FROM Win32_PhysicalMemory"), _bstr_t(L"PartNumber"), L"RAM Part Number");
	Sleep(1);


	#ifdef linux

	printf("Version: 2.2024 [ENGLISH] (C/C++) [LINUX] \n");
	Sleep(1);

	#endif

	#ifdef _WIN32

	printf("Version: 2.2024 [ENGLISH] (C/C++) [WINDOWS] \n");
	Sleep(1);

	#else

	printf("Version: 2.2024 [ENGLISH] (C/C++) [UNKNOWN] \n");
	Sleep(1);

	#endif

	check_start_start();
}