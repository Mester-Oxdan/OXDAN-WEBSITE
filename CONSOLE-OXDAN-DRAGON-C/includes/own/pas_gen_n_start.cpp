#include <windows.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <string>
#include <cmath>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

using namespace std;

// Function to generate passwords recursively
void generatePasswords_1(const char* words, int size, int length, string currentPassword, ofstream& outFile) {
    if (length == 0) {
        outFile << currentPassword << endl;
        cout << currentPassword << endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        generatePasswords_1(words, size, length - 1, currentPassword + words[i], outFile);
    }
}

void pas_gen_n_start()
{
    srand(time(0));
    char words[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    string Char;
    int size = sizeof(words) / sizeof(words[0]);

    printf("\n\033[0;31mEnter 'esc' (for exit) \033[0;37m");
    cout << "\n\033[0;33mEnter Number of chars in passwords: \033[0;37m";
    cin >> Char;
    boost::to_lower(Char);
    boost::trim(Char);
    if (Char == "esc") {
        check_start_start();
    }

    if (stoi(Char) == 0) {
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        printf("(!Only integers!)\n");
        printf("\033[0;37m");
        cin.clear();
        cin.ignore();
        _getch();
        check_start_start();
    }

    int Char_pas = stoi(Char);
    ofstream outFile("Pass_Gen_N.txt");
    cout << "\n";

    generatePasswords_1(words, size, Char_pas, "", outFile);

    outFile.close();
    check_start_start();
}