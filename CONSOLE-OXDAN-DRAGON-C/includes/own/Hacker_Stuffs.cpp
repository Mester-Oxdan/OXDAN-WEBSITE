#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include "all_diclarations.h"
#include <shlobj_core.h>
#include <boost/algorithm/string.hpp>

using namespace std;

#define UNICODE

void Hacker_Stuffs()
{
	if (x == "dll_injector") // dll_injector (+)
	{
		try
		{
			inject_prog_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "file_injector") // file_injector (+)
	{
		try
		{
			//inject_prog_2_start();
			string cmd_gh = "start ";
			cmd_gh += oxdan_dragon_c;
			cmd_gh += "\\includes\\own\\test_python_py_file_injector.py"; //test_python_phone_number.py
			system(cmd_gh.c_str());
			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "cor_desk") // cor_desk (+)
	{
		try
		{
			cor_desk_start();
		}

		catch (...)
		{
			check_start_start();
		}

	}

	/*else if (x == "phone_search") // phone_search (+)
	{
		try
		{
			string cmd_gh = "start ";
			cmd_gh += oxdan_dragon_c;
			cmd_gh += "\\includes\\own\\test_python_phone_number.py"; //test_python_phone_number.py
			system(cmd_gh.c_str());
			check_start_start();
		}

		catch (...)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter phone number with country code!)\n");
			printf("\033[0;37m");
			check_start_start();
		}

	}*/

	else if (x == "mimikatz") // mimikatz (+)
	{
		try
		{
			printf("\n");
			string cmd_io = "start " + oxdan_dragon_c + "\\includes\\own\\includes\\mimikatz-master\\mimikatz-master\\x64\\mimikatz.exe";
			system(cmd_io.c_str());
			//printf(cmd_io.c_str());
			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}

	}

	else if (boost::starts_with(writex, "john")) // john (+)
	{
		try
		{

			cout << " " << endl;
			// Split the input into a vector of strings

			vector<std::wstring> command;
			std::wstring word;
			for (char c : writex) {
				if (c == ' ') {
					command.push_back(word);
					word = L"";
				}
				else {
					word += c;
				}
			}
			if (!word.empty()) {
				command.push_back(word);
			}

			command.erase(command.begin());

			// Remove "cmd" from the command vector
//			command.erase(remove(command.begin(), command.end(), "hydra"), command.end());

			wchar_t bufw[256];
			int nchar = GetEnvironmentVariableW(L"OXDAN-DRAGON-C_W", bufw, 256);

			std::wstring oxdan_dragon_w(bufw);

			std::wstring separator = L" ";
			std::wstring right_command = L"";

			// std::wstring widestr = std::wstring(oxdan_dragon_c.begin(), oxdan_dragon_c.end());
			std::wstring widecstr_2(L"\\includes\\own\\includes\\john_the_ripper\\run\\john.exe");
			//right_command += L'"' + oxdan_dragon_w + widecstr_2 + L'"';
			right_command += oxdan_dragon_w + widecstr_2;
			right_command = L"\"" + right_command + L"\"";
			right_command = L"\"" + right_command + L"\"";

			for (const std::wstring& cmd : command) {
				right_command += separator + cmd;
			}

			_wsystem(right_command.c_str());
			//cout << " " << endl;


			//cout << " " << endl;



			check_start_start();

		}

		catch (...)
		{

			check_start_start();
		}
	}

	else if (boost::starts_with(writex, "nmap")) // nmap (+)
	{
		try
		{

			cout << " " << endl;
			// Split the input into a vector of strings

			vector<string> command;
			string word;
			for (char c : writex) {
				if (c == ' ') {
					command.push_back(word);
					word = "";
				}
				else {
					word += c;
				}
			}
			if (!word.empty()) {
				command.push_back(word);
			}

			// Remove "cmd" from the command vector
			//command.erase(remove(command.begin(), command.end(), "nmap"), command.end());

			string separator = " ";
			string right_command = "";
			//right_command += oxdan_dragon_c + "\\includes\\own\\includes\\john_the_ripper\\run\\john.exe ";

			for (const string& cmd : command) {
				right_command += separator + cmd;
			}

			system(right_command.c_str());
			//cout << " " << endl;


			//cout << " " << endl;



			check_start_start();

		}

		catch (...)
		{

			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Install nmap!)\n");
			printf("\033[0;37m");
			check_start_start();
		}
	}

	else if (boost::starts_with(writex, "metasploit")) // metasploit (+)
	{
		try
		{
			//cout << " " << endl;
			// Split the input into a vector of strings

			vector<std::wstring> command;
			std::wstring word;
			for (char c : writex) {
				if (c == ' ') {
					command.push_back(word);
					word = L"";
				}
				else {
					word += c;
				}
			}
			if (!word.empty()) {
				command.push_back(word);
			}

			command.erase(command.begin());

			// Remove "cmd" from the command vector
//			command.erase(remove(command.begin(), command.end(), "hydra"), command.end());

			wchar_t bufw[256];
			int nchar = GetEnvironmentVariableW(L"OXDAN-DRAGON-C_W", bufw, 256);

			std::wstring oxdan_dragon_w(bufw);

			std::wstring separator = L" ";
			std::wstring right_command = L"";

			// std::wstring widestr = std::wstring(oxdan_dragon_c.begin(), oxdan_dragon_c.end());
			std::wstring widecstr_2(L"C:\\metasploit\\console.bat");
			//right_command += L'"' + oxdan_dragon_w + widecstr_2 + L'"';
			right_command += widecstr_2;
			right_command = L"\"" + right_command + L"\"";
			right_command = L"\"" + right_command + L"\"";

			for (const std::wstring& cmd : command) {
				right_command += separator + cmd;
			}

			_wsystem(right_command.c_str());
			//cout << " " << endl;


			//cout << " " << endl;



			check_start_start();

		}

		catch (...)
		{

			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Install metasploit!)\n");
			printf("\033[0;37m");
			check_start_start();
		}
	}

	else if (boost::starts_with(writex, "aircrack-ng")) // aircrack-ng (+)
	{
		try
		{
			cout << " " << endl;
			// Split the input into a vector of strings

			vector<std::wstring> command;
			std::wstring word;
			for (char c : writex) {
				if (c == ' ') {
					command.push_back(word);
					word = L"";
				}
				else {
					word += c;
				}
			}
			if (!word.empty()) {
				command.push_back(word);
			}

			command.erase(command.begin());

			// Remove "cmd" from the command vector
//			command.erase(remove(command.begin(), command.end(), "hydra"), command.end());

			wchar_t bufw[256];
			int nchar = GetEnvironmentVariableW(L"OXDAN-DRAGON-C_W", bufw, 256);

			std::wstring oxdan_dragon_w(bufw);

			std::wstring separator = L" ";
			std::wstring right_command = L"";

			// std::wstring widestr = std::wstring(oxdan_dragon_c.begin(), oxdan_dragon_c.end());
			std::wstring widecstr_2(L"\\includes\\own\\includes\\aircrack-ng\\aircrack-ng_1\\bin\\aircrack-ng.exe");
			//right_command += L'"' + oxdan_dragon_w + widecstr_2 + L'"';
			right_command += oxdan_dragon_w + widecstr_2;
			right_command = L"\"" + right_command + L"\"";
			right_command = L"\"" + right_command + L"\"";

			for (const std::wstring& cmd : command) {
				right_command += separator + cmd;
			}

			_wsystem(right_command.c_str());
			//cout << " " << endl;


			//cout << " " << endl;



			check_start_start();

		}

		catch (...)
		{

			check_start_start();
		}
	}

	else if (boost::starts_with(writex, "sqlmap")) // sqlmap (+)
	{
		try
		{
			cout << " " << endl;
			// Split the input into a vector of strings

			vector<std::wstring> command;
			std::wstring word;
			for (char c : writex) {
				if (c == ' ') {
					command.push_back(word);
					word = L"";
				}
				else {
					word += c;
				}
			}
			if (!word.empty()) {
				command.push_back(word);
			}

			command.erase(command.begin());

			// Remove "cmd" from the command vector
//			command.erase(remove(command.begin(), command.end(), "hydra"), command.end());

			wchar_t bufw[256];
			int nchar = GetEnvironmentVariableW(L"OXDAN-DRAGON-C_W", bufw, 256);

			std::wstring oxdan_dragon_w(bufw);

			std::wstring separator = L" ";
			std::wstring right_command = L"";

			// std::wstring widestr = std::wstring(oxdan_dragon_c.begin(), oxdan_dragon_c.end());
			std::wstring widecstr_2(L"\\includes\\own\\includes\\sqlmap\\sqlmap.py");
			//right_command += L'"' + oxdan_dragon_w + widecstr_2 + L'"';
			right_command += oxdan_dragon_w + widecstr_2;
			right_command = L"\"" + right_command + L"\"";
			right_command = L"\"" + right_command + L"\"";

			for (const std::wstring& cmd : command) {
				right_command += separator + cmd;
			}

			_wsystem(right_command.c_str());
			//cout << " " << endl;


			//cout << " " << endl;



			check_start_start();

		}

		catch (...)
		{

			check_start_start();
		}
	}

	else if (boost::starts_with(writex, "hydra")) // hydra (+)
	{
		try
		{
			cout << " " << endl;
			// Split the input into a vector of strings

			vector<std::wstring> command;
			std::wstring word;
			for (char c : writex) {
				if (c == ' ') {
					command.push_back(word);
					word = L"";
				}
				else {
					word += c;
				}
			}
			if (!word.empty()) {
				command.push_back(word);
			}

			command.erase(command.begin());

			// Remove "cmd" from the command vector
//			command.erase(remove(command.begin(), command.end(), "hydra"), command.end());

			wchar_t bufw[256];
			int nchar = GetEnvironmentVariableW(L"OXDAN-DRAGON-C_W", bufw, 256);
			
			std::wstring oxdan_dragon_w(bufw);

			std::wstring separator = L" ";
			std::wstring right_command = L"";
			
			// std::wstring widestr = std::wstring(oxdan_dragon_c.begin(), oxdan_dragon_c.end());
			std::wstring widecstr_2(L"\\includes\\own\\includes\\hydra_windows\\hydra.exe");
			//right_command += L'"' + oxdan_dragon_w + widecstr_2 + L'"';
			right_command += oxdan_dragon_w + widecstr_2;
			right_command = L"\"" + right_command + L"\"";
			right_command = L"\"" + right_command + L"\"";

			for (const std::wstring& cmd : command) {
				right_command += separator + cmd;
			}

			_wsystem(right_command.c_str());
			//cout << " " << endl;


			//cout << " " << endl;



			check_start_start();

		}

		catch (...)
		{

			check_start_start();
		}
	}

	else if (x == "con_wifi") // con_wifi (+)
	{
		try
		{
			con_wifi_start();
			check_start_start();
		}

		catch (...)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter valid information!)\n");
			printf("\033[0;37m");
			check_start_start();
		}

	}

	else if (x == "wifi_hack") // wifi_hack (+)
	{
		try
		{
			wifi_hack_start();
			check_start_start();
		}

		catch (...)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter valid information!)\n");
			printf("\033[0;37m");
			check_start_start();
		}

	}

	else if (x == "ascii_code") // ascii_code (+)
	{
		try
		{
			ascii_code_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "morse_code_cipher") // morse_code_cipher (+)
	{
		try
		{
			initialize_morse_to_english();
			morse_code_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "caesar_cipher") // caesar_cipher (+)
	{
		try
		{
			cuaser_cipher_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "my_wifi_pas") // my_wifi_pas (+)
	{
		try
		{
			my_wifi_pas_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "get_ip_website") // get_ip_website (+)
	{
		try
		{

			char buf[256];
			string fert = tokens[1];

			WSADATA d;
			if (WSAStartup(MAKEWORD(2, 2), &d) != 0) {
				fprintf(stderr, "Failed to initialize.\n");
				1;
			}

			string hostname = fert; // char
			struct hostent* host;
			if ((host = gethostbyname(hostname.c_str())) == NULL) {
				printf("\033[0;31m");
				printf("\n");
				printf("(!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				printf("(!Site not found!)\n");
				printf("\033[0;37m");
				check_start_start();
				
			}

			cout << "\n\033[0;33mIp address of \033[0;37m" << fert << " \033[0;33mis:\033[0;37m " << inet_ntoa(*(struct in_addr*)host->h_addr_list[0]) << "\n";

			WSACleanup();

			check_start_start();
		}

		catch (...)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Site not found!)\n");
			printf("\033[0;37m");
			check_start_start();
		}
	}

	else if (x == "auto_clicker") // auto_clicker (+)
	{
		try
		{
			auto_clicker_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "ip_search") // ip_search (+)
	{
		try
		{
			ip_search_start();
		}

		catch (...)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter network ip address!)\n");
			printf("\033[0;37m");
			check_start_start();
		}
	}

	else if (x == "pas_gen") // pas_gen (+)
	{
		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter pas_gen option!)\n");
			printf("\033[0;37m");

			check_start_start();
		}

		else
		{
			char buf[256];
			string name = tokens[1];

			if (name == "w" || name == "W") // pas gen w (+)
			{
				try
				{
					pas_gen_w_start();
				}

				catch (...)
				{
					check_start_start();
				}
			}
			else if (name == "u" || name == "U") // pas gen u (+)
			{
				try
				{
					pas_gen_u_start();
				}

				catch (...)
				{
					check_start_start();
				}
			}

			else if (name == "nw" || name == "NW") // pas gen nw (+)
			{
				try
				{
					pas_gen_nw_start();
				}

				catch (...)
				{
					check_start_start();
				}
			}

			else if (name == "n" || name == "N")
			{
				try
				{
					pas_gen_n_start();
				}

				catch (...)
				{
					check_start_start();
				}
			}

			else
			{
				printf("\033[0;31m");
				printf("\n");
				printf("(!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				printf("(!Enter pas_gen option!)\n");
				printf("\033[0;37m");

				check_start_start();
			}
		}
	}
}