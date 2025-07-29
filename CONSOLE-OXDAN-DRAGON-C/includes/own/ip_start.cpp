#include <windows.h>
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

// Include the necessary Boost headers
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

void ip_start()
{
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
		printf("(!Error Code: %d ", WSAGetLastError(), "!)\n");
		printf("\033[0;37m");
		_getch();
		1;
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
		_getch();

		1;
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
		printf("(!get host by name failed: %d ", WSAGetLastError(), "!)\n");
		printf("\033[0;37m");
		_getch();

		1;
	}

	addr_list = (struct in_addr**)he->h_addr_list;


	int i = 0; addr_list[i] != NULL;
	IP = inet_ntoa(*addr_list[i]);
	printf("\n\033[0;33mIPv4 Address:\033[0;37m %s\n", IP);

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
		cerr << "Error: " << e.what() << endl;
	}

	// Parse the JSON response using Boost.PropertyTree
	boost::property_tree::ptree pt;
	istringstream is(response);
	read_json(is, pt);

	string query = pt.get<string>("query");

	cout << "\033[0;33mNetwork Ip Address: \033[0;37m" << query << endl;

	WSACleanup();

	check_start_start();
}