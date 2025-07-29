#include <windows.h>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "all_diclarations.h"

using namespace std;

string exec(const char* cmd) {
	char buffer[128];
	string result = "";
	FILE* pipe = _popen(cmd, "r");
	if (!pipe) throw runtime_error("_popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	}
	catch (...) {
		_pclose(pipe);
		throw;
	}
	_pclose(pipe);
	return result;
}

vector<string> getWifiList() {
	stringstream ss(exec("netsh wlan show profile").data());
	string input;
	vector<string> wifi;
	while (getline(ss, input))
		if (input.find("All User Profile") != string::npos)
			wifi.push_back(input.substr(27, input.length()));
	return wifi;
}

string getPassword(string ssid) {
	string command = "netsh wlan show profile \"" + ssid + "\" key=clear";
	stringstream ss(exec(command.data()).data());
	string input;
	while (getline(ss, input)) {
		if (input.find("Key Content") != string::npos)
			return input.substr(29, input.length());
	}
	return "< NULL >";
}

void my_wifi_pas_start()
{
	printf("\n\033[0;31mWIFI_PASSWORDS: \033[0;37m\n");

	vector<string> wifi = getWifiList();
	//printf("\n\033[0;33mWifi:                            Password:\033[0;37m\n");
	for (string ssid : wifi)
	{
		printf("\n");
		cout << "SSID\t:\t" << ssid << "\n";
		cout << "Key\t:\t" << getPassword(ssid) << "\n\n";
	}

	check_start_start();
}