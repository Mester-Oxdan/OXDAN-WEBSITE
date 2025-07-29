#include <boost/asio.hpp>
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <direct.h>
#include <sstream>
#include "all_diclarations.h"
#include <process.h>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#pragma warning(disable : 4996).

using namespace std;
namespace fs = boost::filesystem;

std::vector<std::string> where(const std::string& cmd_name) {
	std::vector<std::string> result;

	const char* path_env = std::getenv("PATH");
	const char* ext_env = std::getenv("PATHEXT");

	if (!path_env || !ext_env)
		return result;

	std::vector<std::string> paths, exts;
	boost::split(paths, path_env, boost::is_any_of(";"));
	boost::split(exts, ext_env, boost::is_any_of(";"));

	for (const auto& dir : paths) {
		boost::filesystem::path base_path(dir);
		boost::filesystem::path full_path = base_path / cmd_name;

		if (boost::filesystem::exists(full_path))
			result.push_back(full_path.string());

		for (const auto& ext : exts) {
			std::string clean_ext = ext;
			if (!clean_ext.empty() && clean_ext[0] != '.')
				clean_ext = "." + clean_ext;

			boost::filesystem::path try_path = base_path / (cmd_name + clean_ext);
			if (boost::filesystem::exists(try_path))
				result.push_back(try_path.string());
		}
	}

	return result;
}

void handle_directory_or_file(const std::string& path) {
	try {
		fs::path p(path);

		if (fs::is_directory(p)) {
			bool has_files = false;

			for (fs::directory_iterator it(p); it != fs::directory_iterator(); ++it) {
				if (fs::is_regular_file(it->path())) {
					has_files = true;
					break;
				}
			}

			if (has_files) {
				cout << "\n\033[0;31mEnter 'esc' (for exit)\033[0;37m";
				std::string confirmation;
				std::cout << "\n\033[0;33mPath '" << path << "' is a Directory. Are you sure you want to delete this directory and its contents? (yes/no): \033[0;37m";
				std::getline(std::cin, confirmation);
				boost::to_lower(confirmation);
				boost::trim(confirmation);
				if (confirmation == "yes" || confirmation == "y") {
					fs::remove_all(p);
					//std::cout << "\n(!SUCCESS!) = (!Directory '" << path << "' !)\n";
					printf("\033[0;32m");
					printf("\n");
					printf("(!SUCCESS!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;33m");
					//printf("(!Enter path to directory!)\n");
					cout << "(!Directory '" << path << "' has been deleted successfully!)\n";
					printf("\033[0;37m");
				}
				else if (confirmation == "esc") {
					// Handle 'esc' as needed
					check_start_start();
				}
				else {
					//std::cout << "\n(!ERROR!) = (!!)\n";
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!Directory has not been deleted!)\n");
					printf("\033[0;37m");
				}
			}
			else {
				cout << "\n\033[0;31mEnter 'esc' (for exit)\033[0;37m";
				std::string confirmation;
				std::cout << "\n\033[0;33mPath '" << path << "' is an Empty Directory. Do you want to delete this empty directory? (yes/no): \033[0;37m";
				std::getline(std::cin, confirmation);
				boost::to_lower(confirmation);
				boost::trim(confirmation);
				if (confirmation == "yes" || confirmation == "y") {
					fs::remove(p);
					//std::cout << "\n(!SUCCESS!) = (!Empty directory '" << path << "' !)\n";
					printf("\033[0;32m");
					printf("\n");
					printf("(!SUCCESS!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;33m");
					//printf("(!Enter path to directory!)\n");
					cout << "(!Empty directory '" << path << "' has been deleted successfully!)\n";
					printf("\033[0;37m");
				}
				else if (confirmation == "esc") {
					// Handle 'esc' as needed
					check_start_start();
				}
				else {
					//std::cout << "\n(!ERROR!) = (!!)\n";
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					//printf("(!Enter path to directory!)\n");
					cout << "(!Empty directory has not been deleted!)\n";
					printf("\033[0;37m");
				}
			}
		}
		else if (fs::is_regular_file(p)) {
			cout << "\n\033[0;31mEnter 'esc' (for exit)\033[0;37m";
			std::string confirmation;
			std::cout << "\n\033[0;33mPath '" << path << "' is a file. Are you sure you want to delete this file? (yes/no): \033[0;37m";
			std::getline(std::cin, confirmation);
			boost::to_lower(confirmation);
			boost::trim(confirmation);
			if (confirmation == "yes" || confirmation == "y") {
				fs::remove(p);
				//std::cout << "\n(!SUCCESS!) = (!File '" << path << "' !)\n";
				printf("\033[0;32m");
				printf("\n");
				printf("(!SUCCESS!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;33m");
				//printf("(!Enter path to directory!)\n");
				cout << "(!File '" << path << "' has been deleted successfully!)\n";
				printf("\033[0;37m");
			}
			else if (confirmation == "esc") {
				// Handle 'esc' as needed
				check_start_start();
			}
			else {
				//std::cout << "\n(!ERROR!) = (!!)\n";
				printf("\033[0;31m");
				printf("\n");
				printf("(!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				//printf("(!Enter path to directory!)\n");
				cout << "(!File has not been deleted!)\n";
				printf("\033[0;37m");
			}
		}
		else {
			//std::cout << "\n(!ERROR!) = (!Path '" << path << "' is neither a file nor a directory!)\n";
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			//printf("(!Enter path to directory!)\n");
			cout << "(!Path '" << path << "' does not exists!)\n";
			printf("\033[0;37m");
		}
	}
	catch (const fs::filesystem_error& e) {
		//std::cout << "\n(!ERROR!) = (" <<  << ")\n";
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		//printf("(!" + e.what() + "!)\n");
		cout << "(!" << e.what() << "!)\n";
		printf("\033[0;37m");
	}
}

std::wstring utf8_to_wstring(const std::string& str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
	std::wstring wstr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
	wstr.resize(wcslen(wstr.c_str()));
	return wstr;
}

void list_directory_w(const std::wstring& path) {
	WIN32_FIND_DATAW findFileData;
	HANDLE hFind;

	std::wstring search_path = path + L"\\*";

	hFind = FindFirstFileW(search_path.c_str(), &findFileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		std::wcerr << L"Failed to open directory: " << path << std::endl;
		return;
	}

	std::wcout << L"\n\033[0;33mFILES: \n";
	do {
		const wchar_t* name = findFileData.cFileName;
		if (wcscmp(name, L".") != 0 && wcscmp(name, L"..") != 0) {
			std::wcout << L"\033[0;37m" << name << L"\n";
		}
	} while (FindNextFileW(hFind, &findFileData) != 0);

	FindClose(hFind);
}

void Main_Commands()
{
	if (x == "--version" || x == "-version" || x == "version" || x == "-v") // --version (+)
	{
		try
		{
			printf("\n\033[0;33mOxdan");
			Sleep(10);
			printf("\033[0;31m Dragon");
			Sleep(10);
			printf("\033[0;37m [ Version: 1.2025 [ENGLISH] (C/C++) [WINDOWS] ] \n");
			Sleep(10);
			printf("(c) Oxdan Praduction. \n");
			Sleep(10);

			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "go_to" || x == "cd") // go_to (+)
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter path to directory!)\n");
			printf("\033[0;37m");
		}

		else
		{
			try
			{
				char buf[256];
				std::string cd = tokens[1];

				// Check for non-ASCII characters (i.e., non-English folder names)
				bool has_non_ascii = false;
				for (char ch : cd) {
					if (static_cast<unsigned char>(ch) > 127) {
						has_non_ascii = true;
						break;
					}
				}

				if (has_non_ascii) {
					//std::cout << "\033[0;31m[ERROR]\033[0;37m Folder name not supported (non-English characters detected)\n";
					check_start_start();  // Go back to input loop or recovery
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!Folder name not supported!)\n");
					printf("\033[0;37m");

					check_start_start();
				}
				else {
					// Proceed with setting directory
					if (SetCurrentDirectoryA(cd.c_str())) {
						GetCurrentDirectoryA(255, buf);
						
						check_start_start();
					}
					else {
						
						printf("\033[0;31m");
						printf("\n");
						printf("(!ERROR!)");
						printf("\033[0;37m");
						printf(" = ");
						printf("\033[0;32m");
						printf("(!Failed to change directory!)\n");
						printf("\033[0;37m");

						check_start_start();
						
					}
				}



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
				printf("(!Enter path to directory!)\n");
				printf("\033[0;37m");

				check_start_start();
			}
		}

		check_start_start();
	}

	else if (x == "where") // where (+)
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter file name!)\n");
			printf("\033[0;37m");
		}

		else
		{
			try
			{
				char buf[256];
				string cd = tokens[1];
				
				auto results = where(cd);

				if (results.empty()) {
					
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!File doesnt exists!)\n");
					printf("\033[0;37m");
					check_start_start();
				}

				for (const auto& path : results)
					std::cout << path << '\n';
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
				printf("(!Enter file name!)\n");
				printf("\033[0;37m");

				check_start_start();
			}
		}

		check_start_start();
	}

	else if (x == "search") // search (+)
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!This command doesn't exists!)\n");
			printf("\033[0;37m");
		}

		else
		{
			try
			{
				char buf[256];
				string search = tokens[1];
				//SetCurrentDirectoryA((LPCSTR)cd.c_str());
				//GetCurrentDirectoryA(255, buf);

				std::vector<std::string> my_list = {
				  "search", "--help", "-help", "help", "-h", "--version", "-version", "version", "-v",
				  "pip", "git", "conda", "cmd", "cls", "clear", "go_to", "cd", "where", "dir", "ls", "mkdir", "create",
				  "del", "delete", "install", "update",
				  "dll_injector", "file_injector", "pas_gen", "my_wifi_pas", "cor_desk", "ascii_code",
				  "ip_search", "mimikatz", "john", "nmap", "sqlmap", "hydra", "metasploit", "aircrack-ng",
				  "con_wifi", "wifi_hack", "get_ip_website", "auto_clicker", "morse_code_cipher", "caesar_cipher",
				  "ukraine", "author", "matrix",
				  "login", "registration", "instructions", "del_account", "logout", "my_accounts",
				  "tim", "time", "stopwatch", "timer", "calculator", "calendar", "webcam_recorder", "screen_recorder",
				  "cur_conv", "notepad", "translator", "dictaphone", "files_convertor", "3d_price_calc",
				  "pacman", "2048", "arkanoid", "flappy_bird", "tetris", "hangman", "car_racing", "guess_number",
				  "math_game", "typing_tutor", "battle_city", "doom", "mario", "snake", "ping_pong", "tic_tac_toe",
				  "checkers", "chess", "space_shooter",
				  "title", "new", "start", "open", "shutdown", "restart", "date", "promo_code", "i_am_here", "&main",
				  "donate", "donators", "helpers", "color_back", "i?", "administrator", "admin", "superuser",
				  "chan_backg", "history", "cls_history", "memory", "rules", "commands", "tips", "links",
				  "my_volume_level", "set_volume_level", "set_mute", "ip", "size", "my_location",
				  "system_info", "energy", "power", "prank_button", "melt_screen", "gdi_virus",
				  "exit", "esc", "quit"
				}; //dragon_helper, color, ai_chat, phone_search,


				// Check if the input exists in the list
				if (std::find(my_list.begin(), my_list.end(), search) != my_list.end()) {
					printf("\033[0;32m");
					printf("\n");
					printf("(!SUCCESS!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;33m");
					printf("(!This command exists!)\n");
					printf("\033[0;37m");
				}
				else {
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!This command doesn't exists!)\n");
					printf("\033[0;37m");
				}

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
				printf("(!This command doesn't exists!)\n");
				printf("\033[0;37m");

				check_start_start();
			}
		}

		check_start_start();
	}

	else if (boost::starts_with(writex, "pip")) // pip (+)
	{
		try
		{
			cout << "\n";
			std::istringstream iss(writex);
			std::vector<std::string> args{ std::istream_iterator<std::string>{iss},
										  std::istream_iterator<std::string>{} };

			// Convert vector of strings to command string
			std::ostringstream oss;
			for (const auto& arg : args) {
				oss << arg << " ";
			}

			// Execute the command using popen
			std::string command_string = oss.str();
			FILE* pipe = _popen(command_string.c_str(), "r");
			if (!pipe) {
				perror("popen");
				//return 1;
			}

			// Read and print the output of the command
			char buffer[4096];
			while (fgets(buffer, 4096, pipe)) {
				std::cout << buffer;
			}

			// Close the pipe
			int status = _pclose(pipe);
			if (status == -1) {
				perror("pclose");
				//return 1;
			}

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
			printf("(!Install python!)\n");
			printf("\033[0;37m");

			check_start_start();
		}
	}

	else if (boost::starts_with(writex, "cmd")) // cmd (+)
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
				command.erase(remove(command.begin(), command.end(), "cmd"), command.end());

				string separator = " ";
				string right_command = "";
				for (const string& cmd : command) {
					right_command += separator + cmd;
				}

				if (right_command == "cmd") {
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!We're so sorry about that, only cmd --> cmd command can't be run!)\n");
				}
				else {
					system(right_command.c_str());
					//cout << " " << endl;
				}

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
			printf("(!Check your system. (should be Windows)!)\n");
			printf("\033[0;37m");

			check_start_start();
		}
	}

	else if (boost::starts_with(writex, "git")) // git (+)
	{
		try
		{
			cout << "\n";
			std::istringstream iss(writex);
			std::vector<std::string> args{ std::istream_iterator<std::string>{iss},
										  std::istream_iterator<std::string>{} };

			// Convert vector of strings to command string
			std::ostringstream oss;
			for (const auto& arg : args) {
				oss << arg << " ";
			}

			// Execute the command using popen
			std::string command_string = oss.str();
			FILE* pipe = _popen(command_string.c_str(), "r");
			if (!pipe) {
				perror("popen");
				//return 1;
			}

			// Read and print the output of the command
			char buffer[4096];
			while (fgets(buffer, 4096, pipe)) {
				std::cout << buffer;
			}

			// Close the pipe
			int status = _pclose(pipe);
			if (status == -1) {
				perror("pclose");
				//return 1;
			}

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
			printf("(!Install git!)\n");
			printf("\033[0;37m");

			check_start_start();
		}
	}

	/*else if (boost::starts_with(writex, "npm")) // npm (+)
	{
		try
		{
			cout << "\n";
			std::istringstream iss(writex);
			std::vector<std::string> args{ std::istream_iterator<std::string>{iss},
										  std::istream_iterator<std::string>{} };

			// Convert vector of strings to command string
			std::ostringstream oss;
			for (const auto& arg : args) {
				oss << arg << " ";
			}

			// Execute the command using popen
			std::string command_string = oss.str();
			FILE* pipe = _popen(command_string.c_str(), "r");
			if (!pipe) {
				perror("popen");
				//return 1;
			}

			// Read and print the output of the command
			char buffer[4096];
			while (fgets(buffer, 4096, pipe)) {
				std::cout << buffer;
			}

			// Close the pipe
			int status = _pclose(pipe);
			if (status == -1) {
				perror("pclose");
				//return 1;
			}

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
			printf("(!Install npm!)\n");
			printf("\033[0;37m");

			check_start_start();
		}
		}*/

	else if (boost::starts_with(writex, "conda")) // conda (+)
	{
		try
		{
			cout << "\n";
			std::istringstream iss(writex);
			std::vector<std::string> args{ std::istream_iterator<std::string>{iss},
										  std::istream_iterator<std::string>{} };

			// Convert vector of strings to command string
			std::ostringstream oss;
			for (const auto& arg : args) {
				oss << arg << " ";
			}

			// Execute the command using popen
			std::string command_string = oss.str();
			FILE* pipe = _popen(command_string.c_str(), "r");
			if (!pipe) {
				perror("popen");
				//return 1;
			}

			// Read and print the output of the command
			char buffer[4096];
			while (fgets(buffer, 4096, pipe)) {
				std::cout << buffer;
			}

			// Close the pipe
			int status = _pclose(pipe);
			if (status == -1) {
				perror("pclose");
				//return 1;
			}

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
			printf("(!Install miniconda!)\n");
			printf("\033[0;37m");

			check_start_start();
		}
	}

	else if (x == "cls" || x == "clear") // cls/clear (+)
	{
		try
		{
			#ifdef linux
			system("clear");
			#endif

			#ifdef _WIN32
			system("mode 148, 29"); // set size of console (+)
			SetWindow(141, 29); // set buffer size of console (+)
			system("cls");
			#endif

			check_start_start();

		}

		catch (...)
		{
			check_start_start();
		}
	}
	else if (x == "update") // update (+)
	{
		try
		{

				boost::asio::io_context io_context;
				boost::asio::ip::tcp::resolver resolver(io_context);
				boost::asio::ip::tcp::socket socket(io_context);

				std::string host = "raw.githubusercontent.com";
				std::string path = "/Mester-Oxdan/Oxdan-Dragon-C/main/version";

				boost::asio::ip::tcp::resolver::query query(host, "http");
				boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

				boost::asio::connect(socket, endpoint_iterator);

				// Form the HTTP request
				std::string request =
					"GET " + path + " HTTP/1.1\r\n"
					"Host: " + host + "\r\n"
					"Connection: close\r\n\r\n";

				// Send the HTTP request
				boost::asio::write(socket, boost::asio::buffer(request));

				// Read the HTTP response
				std::string response;
				boost::asio::streambuf response_buffer;
				boost::asio::read_until(socket, response_buffer, "\r\n");

				// Read and append the rest of the response
				std::istream response_stream(&response_buffer);
				while (!response_stream.eof()) {
					std::string line;
					std::getline(response_stream, line);
					response += line + "\n";
				}

				// Process the response (e.g., check for the version)
				if (response.find("2.2024") != std::string::npos) {
					std::cout << "\n\033[0;33mYou're right!\033[0;37m" << std::endl;
					std::cout << "We have a new version for you: 3.2025" << std::endl;
					std::cout << "If you want to \033[0;32mdownload\033[0;37m it, just go to our Website or GitHub." << std::endl;
				}
				else {
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!Program already updated to last version!)\n");
					printf("\033[0;37m");
				}


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
			printf("(!Program already updated to last version!)\n");
			printf("\033[0;37m");

			check_start_start();
		}
	}

	else if (x == "dir" || x == "ls") // dir/ls (+)
	{
		try
		{
			list_directory_w(buf1);
			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "install") // install (+) 
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter install option!)\n");
			printf("\033[0;37m");

			check_start_start();
		}

		else
		{
			try
			{
				char buf[256];
				string name = tokens[1];

				installs_start(name);
			}

			catch (...)
			{

				check_start_start();
			}
		}

		check_start_start();
	}

	else if (x == "del" || x == "delete") // del/delete (+)
	{
		try
		{
			if (tokens.size() < 2)
			{
				printf("\033[0;31m");
				printf("\n");
				printf("(!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				printf("(!Enter name for file or directory!)\n");
				printf("\033[0;37m");
			}

			else
			{
				try
				{
					char buf[256];
					string name = tokens[1];
					boost::filesystem::path path = boost::filesystem::current_path();
					std::string path_1 = path.string() + "\\" + name;
					handle_directory_or_file(path_1);
				}

				catch (...)
				{
					check_start_start();
				}
			}

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
			printf("(!Enter name for file or directory!)\n");
			printf("\033[0;37m");
		}
	}

	else if (x == "mkdir") // mkdir (+)
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter name for folder!)\n");
			printf("\033[0;37m");
		}

		else
		{
			try
			{
				char buf[256];
				string name = tokens[1];
				fs::path dir_path(name);

				if (fs::exists(dir_path)) {
					if (fs::is_directory(dir_path)) {
						//std::cout << ".\n";
						printf("\033[0;31m");
						printf("\n");
						printf("(!ERROR!)");
						printf("\033[0;37m");
						printf(" = ");
						printf("\033[0;32m");
						printf("(!Directory with that name already exists!)\n");
						printf("\033[0;37m");
					}
					else {
						//std::cout << "A .\n";
						printf("\033[0;31m");
						printf("\n");
						printf("(!ERROR!)");
						printf("\033[0;37m");
						printf(" = ");
						printf("\033[0;32m");
						printf("(!File with that name already exists!)\n");
						printf("\033[0;37m");
					}
				}
				else {
					// Directory does not exist, create it
					if (fs::create_directory(dir_path)) {
						//std::cout << ".\n";
						printf("\033[0;32m");
						printf("\n");
						printf("(!SUCCESS!)");
						printf("\033[0;37m");
						printf(" = ");
						printf("\033[0;33m");
						printf("(!Directory created successfully!)\n");
						printf("\033[0;37m");
					}
					else {
						//std::cout << ".\n";
						printf("\033[0;31m");
						printf("\n");
						printf("(!ERROR!)");
						printf("\033[0;37m");
						printf(" = ");
						printf("\033[0;32m");
						printf("(!Failed to create directory!)\n");
						printf("\033[0;37m");
					}
				}
			}

			catch (...)
			{
				check_start_start();
			}
		}

		check_start_start();
	}

	else if (x == "create") // create (+)
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter name for file!)\n");
			printf("\033[0;37m");
		}

		else
		{
			try
			{
				char buf[256];
				string name = tokens[1];

				fs::path file_path(name);

				if (fs::exists(file_path)) {
					if (fs::is_regular_file(file_path)) {
						//std::cout << "File already exists.\n";
						printf("\033[0;31m");
						printf("\n");
						printf("(!ERROR!)");
						printf("\033[0;37m");
						printf(" = ");
						printf("\033[0;32m");
						printf("(!File with that name already exists!)\n");
						printf("\033[0;37m");
					}
					else {
						//std::cout << "A directory with that name already exists.\n";
						printf("\033[0;31m");
						printf("\n");
						printf("(!ERROR!)");
						printf("\033[0;37m");
						printf(" = ");
						printf("\033[0;32m");
						printf("(!Directory with that name already exists!)\n");
						printf("\033[0;37m");
					}
				}
				else {
					// File does not exist, create it
					std::ofstream file(file_path.string());
					if (file) {
						//std::cout << "File created successfully.\n";
						file.close(); // Close the file stream

						printf("\033[0;32m");
						printf("\n");
						printf("(!SUCCESS!)");
						printf("\033[0;37m");
						printf(" = ");
						printf("\033[0;33m");
						printf("(!File created successfully!)\n");
						printf("\033[0;37m");
					}
					else {
						//std::cout << ".\n";
						printf("\033[0;31m");
						printf("\n");
						printf("(!ERROR!)");
						printf("\033[0;37m");
						printf(" = ");
						printf("\033[0;32m");
						printf("(!Failed to create file!)\n");
						printf("\033[0;37m");
					}
				}
			}

			catch (...)
			{
				check_start_start();
			}
		}

		check_start_start();
	}
}