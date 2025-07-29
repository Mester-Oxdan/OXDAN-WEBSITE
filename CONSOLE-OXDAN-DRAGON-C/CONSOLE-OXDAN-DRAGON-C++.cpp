#include <windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
// #include <boost/filesystem.hpp>
#include <string.h>
#include <sstream>

#define OXIDAN_MAIN

#include "includes/own/all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;
std::queue<std::string> commandQueue;
bool autoRunQueuedCommands = false;
std::queue<std::string> auto_commands;
bool auto_command_mode = false;

char buf_87[256];
char buf2[256];

bool containsSpaces_2(const string& str) {
	return str.find(' ') != string::npos;
}

int main(int argc, char* argv[])  // 🆕 added argc/argv
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    wchar_t bufw[256];
    int nlen = GetCurrentDirectoryA(255, buf_87);
    int nlen_w = GetCurrentDirectoryW(255, bufw);
    SetEnvironmentVariableA("OXDAN-DRAGON-C", buf_87);
    SetEnvironmentVariableW(L"OXDAN-DRAGON-C_W", bufw);
    int nchar = GetEnvironmentVariableA("OXDAN-DRAGON-C", buf2, 256);
    oxdan_dragon_c = buf2;

    // 🆕 If CLI args were passed, queue them as commands
    if (argc > 1) {
        std::string combined;
        for (int i = 1; i < argc; ++i) {
            combined += argv[i];
            if (i != argc - 1) combined += " ";
        }

        std::stringstream ss(combined);
        std::string cmd;
        while (std::getline(ss, cmd, '|')) {
            cmd.erase(0, cmd.find_first_not_of(" \t\n\r"));
            cmd.erase(cmd.find_last_not_of(" \t\n\r") + 1);
            if (!cmd.empty()) auto_commands.push(cmd);
        }

        auto_command_mode = true;

        printf("\033[0;33mOxdan");
        printf("\033[0;31m Dragon");
        printf("\033[0;37m [ Version: 1.2025 [ENGLISH] (C/C++) [WINDOWS] ] \n");
        printf("(p) Oxdan Praduction. \n");
        start_start(true);
        return 0;
    }

    string update_message = "start " + oxdan_dragon_c + "\\includes\\own\\update_message.py";
    system(update_message.c_str());

    string filePath = oxdan_dragon_c;
    vector<string> directories;

    size_t start = 0, end;
    while ((end = filePath.find("\\", start)) != string::npos) {
        string dir = filePath.substr(start, end - start);
        directories.push_back(dir);
        start = end + 1;
    }
    string lastComponent = filePath.substr(start);
    directories.push_back(lastComponent);

    string firstSpaceWord;
    string lastSpaceWord;

    for (const string& dir : directories) {
        if (containsSpaces_2(dir)) {
            if (firstSpaceWord.empty()) {
                firstSpaceWord = dir;
            }
            lastSpaceWord = dir;
        }
    }

    if (!firstSpaceWord.empty()) {
        if (firstSpaceWord == lastSpaceWord) {
            size_t startPos = filePath.find(firstSpaceWord);
            size_t endPos = startPos + firstSpaceWord.length();
            string modifiedPath = filePath.substr(0, startPos) + "\"" + firstSpaceWord + filePath.substr(endPos);
            startPos = modifiedPath.find(lastSpaceWord);
            endPos = startPos + lastSpaceWord.length();
            modifiedPath = modifiedPath.substr(0, startPos) + lastSpaceWord + "\"" + modifiedPath.substr(endPos);

            string cmd_cmd = "start ";
            cmd_cmd += modifiedPath;
            system(cmd_cmd.c_str());
        }
        else {
            size_t startPos = filePath.find(firstSpaceWord);
            size_t endPos = startPos + firstSpaceWord.length();
            string modifiedPath = filePath.substr(0, startPos) + "\"" + firstSpaceWord + "\"" + filePath.substr(endPos);
            startPos = modifiedPath.find(lastSpaceWord);
            endPos = startPos + lastSpaceWord.length();
            modifiedPath = modifiedPath.substr(0, startPos) + "\"" + lastSpaceWord + "\"" + modifiedPath.substr(endPos);

            oxdan_dragon_c = modifiedPath;

            std::fstream txt_yes_no(modifiedPath + "\\includes\\own\\resuorces\\all_txt\\txt_yes_no.txt", ios::out | ios::trunc);
            std::string data("true");
            txt_yes_no << data << endl;

            first_start();
        }
    }

    oxdan_dragon_c = filePath;
    std::fstream txt_yes_no(filePath + "\\includes\\own\\resuorces\\all_txt\\txt_yes_no.txt", ios::out | ios::trunc);
    std::string data("true");
    txt_yes_no << data << endl;

    first_start();
}
