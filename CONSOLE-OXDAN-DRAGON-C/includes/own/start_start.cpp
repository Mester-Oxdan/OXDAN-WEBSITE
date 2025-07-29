#include <windows.h>
#include <conio.h>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <chrono>
#include <map>
#include <sstream>
#include <iomanip>
#include <boost/filesystem.hpp>
#include "all_diclarations.h"

using namespace std;

#pragma warning(disable : 4996).

vector<string> history;
string x;
string writex;
vector<string> tokens;
wchar_t buf1[256];

HANDLE hStdOuttgf32 = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
void ConsoleCursorVisibleytg32(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOuttgf32, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOuttgf32, &structCursorInfo);
}

// Function to get all matching files in the current directory
std::vector<std::string> get_matching_files(const std::string& prefix) {
	std::vector<std::string> matches;
	boost::filesystem::path current_dir = boost::filesystem::current_path();

	for (auto& entry : boost::filesystem::directory_iterator(current_dir)) {
		if (entry.path().filename().string().find(prefix) == 0) {
			matches.push_back(entry.path().filename().string());
		}
	}

	return matches;
}

// Function to handle auto-complete using TAB key
std::string autocomplete(const std::string& input) {
	std::vector<std::string> matches = get_matching_files(input);

	if (matches.size() == 1) {
		return matches[0];  // Auto-complete with the only match
	}

	return input;  // No matches found, return original input
}

std::string getCurrentTime() {
	std::time_t now = std::time(nullptr);  // get current time as time_t
	std::tm* now_tm = std::localtime(&now); // convert to local time

	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << now_tm->tm_hour << ":"
		<< std::setw(2) << std::setfill('0') << now_tm->tm_min << ":"
		<< std::setw(2) << std::setfill('0') << now_tm->tm_sec;
	return oss.str();
}

void start_start(bool willstart)
{
	ConsoleCursorVisibleytg32(true, 20);

	string text_yes_no;

	// Read from the text file
	ifstream txt_yes_no(oxdan_dragon_c + "\\includes\\own\\resuorces\\all_txt\\txt_yes_no.txt");

	while (txt_yes_no >> text_yes_no)
	{
		if (text_yes_no == "false")
		{
			willstart = false;
		}

		if (text_yes_no == "true")
		{
			willstart = true;
		}
	}

	clock_t timer = clock();
	
	while (true)
	{
		
		if (willstart == true)
		{

			printf("\n");
			GetCurrentDirectoryW(256, buf1);
			std::wcout << buf1 << L">> ";

			if (auto_command_mode && !auto_commands.empty()) {
				writex = auto_commands.front();
				auto_commands.pop();
				cout << writex << endl; // Echo command
				
			}
			else {
				//getline(cin, writex);
				std::getline(std::cin, writex);
			}

			//cout << "\n";
			//writex = _getch();
			//std::string input;
			/*bool tab_needed = true;
			while (tab_needed) {

				const char ch = _getch();  // Get the character from the user

				if (ch == '\t') {  // If TAB key is pressed
					writex = autocomplete(writex);
					cout << "\r" << buf1 << ">> " << writex;  // Reprint the current input
				}
				else if (ch == '\n' || ch == '\r') {  // If ENTER key is pressed
					tab_needed = false;
					//break;
				}
				else if (ch == '\b') {  // If BACKSPACE key is pressed
					if (!writex.empty()) {
						writex.pop_back();
						std::cout << "\b \b";  // Handle backspace in console
					}
				}
				else {
					if (tab_needed = true) {
						writex += ch;
						std::cout << ch;
					}
					else {
						break;
					}
					
				}
			}*/
			for (int i = 0; i < writex.length(); i++) // to lower keys (+)
				writex[i] = tolower(writex[i]);

			boost::trim(writex); // remove !spaces!
			boost::split(tokens, writex, boost::is_any_of(" "));
			x = tokens[0];
			history.push_back(x);

			// big -> class
			// midle -> class
			// small -> class

			Games(); // (+) big
			Serious(); // (+) big
			Hacker_Stuffs(); // (+) big
			Own(willstart, timer, history); // (+) big
			Main_Commands(); // (+) big
			Elses(); // (+) big
			Pictures(); // (+) middle
			Accounts(); // (+) middle
			Pranks(); // (+) middle
			Commands(); // (+) small

			if (x == "" || x == "tetris" || x == "tic_tac_toe" || x == "2048" || x == "del_account" || x == "go_to") // nothing (+)
			{
				start_start(true);
			}

			else
			{
				printf("\n");
				cout << "'" + x + "'" + " Is \033[0;31mbad\033[0;37m command" << endl; // else (+)

				start_start(true);
			}

		}

		if (willstart == false)
		{
			//getline(cin, writex);
			std::getline(std::cin, writex);
			for (int i = 0; i < writex.length(); i++) // to lower keys (+)
				writex[i] = tolower(writex[i]);

			boost::trim(writex); // remove !spaces!
			boost::split(tokens, writex, boost::is_any_of(" "));
			x = tokens[0];

			history.push_back(x);

			// big -> class
			// midle -> class
			// small -> class

			Games(); // (+) big
			Serious(); // (+) big
			Hacker_Stuffs(); // (+) big
			Own(willstart, timer, history); // (+) big
			Main_Commands(); // (+) big
			Elses(); // (+) big
			Pictures(); // (+) middle
			Accounts(); // (+) middle
			Pranks(); // (+) middle
			Commands(); // (+) small

			if (x == "" || x == "tetris" || x == "tic_tac_toe" || x == "2048" || x == "del_account" || x == "go_to") // nothing (+)
			{
				start_start(false);
			}

			else
			{
				printf("\n");
				cout << "'" + x + "'" + " Is \033[0;31mbad\033[0;37m command" << endl; // else (+)

				start_start(false);
			}

		}
	}
}