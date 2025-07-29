#include <iostream>
#include <string.h>
#include <string>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

// Morse code mappings
std::unordered_map<char, std::string> ENGLISH_TO_MORSE = {
    {'a', ".-"}, {'b', "-..."}, {'c', "-.-."}, {'d', "-.."}, {'e', "."}, {'f', "..-."}, {'g', "--."}, {'h', "...."},
    {'i', ".."}, {'j', ".---"}, {'k', "-.-"}, {'l', ".-.."}, {'m', "--"}, {'n', "-."}, {'o', "---"}, {'p', ".--."},
    {'q', "--.-"}, {'r', ".-."}, {'s', "..."}, {'t', "-"}, {'u', "..-"}, {'v', "...-"}, {'w', ".--"}, {'x', "-..-"},
    {'y', "-.--"}, {'z', "--.."}, {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
    {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."}, {'.', ".-.-.-"}, {',', "--..--"},
    {'?', "..--.."}, {'\'', ".----."}, {'!', "-.-.--"}, {'/', "-..-."}, {'(', "-.--."}, {')', "-.--.-"}, {'&', ".-..."},
    {':', "---..."}, {';', "-.-.-."}, {'=', "-...-"}, {'+', ".-.-."}, {'-', "-....-"}, {'_', "..--.-"}, {'"', ".-..-."},
    {'$', "...-..-"}, {'@', ".--.-."}, {' ', " "}
};

std::unordered_map<std::string, char> MORSE_TO_ENGLISH;

// Function to convert English to Morse code
std::string english_to_morse(const std::string& message) {
    std::stringstream morse;
    for (char c : message) {
        if (ENGLISH_TO_MORSE.find(c) != ENGLISH_TO_MORSE.end()) {
            morse << ENGLISH_TO_MORSE[c] << " ";
        }
    }
    return morse.str();
}

// Function to convert Morse code to English
std::string morse_to_english(const std::string& message) {
    std::stringstream english_message;
    std::istringstream words_stream(message);
    std::string word;

    while (std::getline(words_stream, word, ' ')) {
        if (MORSE_TO_ENGLISH.find(word) != MORSE_TO_ENGLISH.end()) {
            english_message << MORSE_TO_ENGLISH[word];
        }
        else if (word == "") {
            english_message << " ";
        }
    }

    return english_message.str();
}


// Function to initialize MORSE_TO_ENGLISH map
void initialize_morse_to_english() {
    for (const auto& pair : ENGLISH_TO_MORSE) {
        MORSE_TO_ENGLISH[pair.second] = pair.first;
    }
}

void morse_code_start()
{
    try
    {
        while (true)
        {
            system("cls");
            string op;

            cout << "\n\033[0;31mEnter 'esc' (for exit) \033[0;37m\n";
            cout << "\033[0;33m(1) Morse to English (2) English to Morse: \033[0;37m";

            cin >> op;
            boost::to_lower(op);
            boost::trim(op);
            if (op == "2")
            {
                string sentence;
                system("cls");
                cout << "\n\033[0;31mEnter 'esc' (for exit) \033[0;37m\n";
                cout << "\033[0;33mEnter text to cipher: \033[0;37m";
                cin.ignore();
                getline(cin, sentence);
                boost::to_lower(sentence);
                if (sentence == "esc" || sentence == "Esc" || sentence == "ESC") {
                    check_start_start();
                }
                else {
                    std::string morse = english_to_morse(sentence);
                    cout << "\n" << "\033[0;33m" << "Encrypted message: " << "\033[0;37m" << morse ;
                    
                }

                _getch();
            }

            else if (op == "esc")
            {
                check_start_start();
            }

            else if (op == "1")
            {
                string pattern = "";
                system("cls");
                cout << "\n\033[0;31mEnter 'esc' (for exit) \033[0;37m\n";
                cout << "\033[0;33mEnter text to decipher: \033[0;37m";
                cin.ignore();
                getline(cin, pattern);

                if (pattern == "esc" || pattern == "Esc" || pattern == "ESC") {
                    check_start_start();
                }
                else {

                    std::string english = morse_to_english(pattern);
                    //std::cout << "Decrypted message: " << english << std::endl;
                    cout << "\n" << "\033[0;33m" << "Decrypted message: " << "\033[0;37m" << english ;
                    _getch();
                }
                _getch();
            }

            else
            {
                morse_code_start();
            }
        }
    }

    catch (...)
    {
        morse_code_start();
    }
}
