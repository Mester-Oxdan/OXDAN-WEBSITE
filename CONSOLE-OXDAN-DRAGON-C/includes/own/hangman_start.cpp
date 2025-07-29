#include <windows.h>
#include <time.h>
#include <string>
#include <iostream>
#include <conio.h>
#include <set>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

#define WRONGTRIES 5

using namespace std;

void DrawMan(int tries) {
    cout << endl << endl;
    cout << "  -----" << endl;
    cout << "  |   |" << endl;
    cout << "  |"; if (tries >= 1) cout << "   \033[0;33mO\033[0;37m    "; cout << endl;
    cout << "  |"; if (tries >= 3) cout << "  \033[0;33m/|\\\033[0;37m   "; cout << endl;
    cout << "  |"; if (tries >= 5) cout << "  \033[0;33m/ \\\033[0;37m    "; cout << endl;
    cout << "  |" << endl;
    cout << "__|__" << endl;
}

void hangman_start() {
    system("cls");
    srand(time(NULL));
    string wordList[31] = { "monkey","oxdan","praduction", "africa", "apple", "banana", "power", "sad", "life", "death", "true", "lie", "false", "you", "racism", "???", "friend", "sky", "command", "slave", "neighbor", "fnaf", "undertale", "bendy", "fun", "dumb", "mistake", "wrong", "correct", "free", "freedom"};
    string word;
    string guessed;

    word = wordList[rand() % 9];

    int wordLength = word.length();
    string dispWord(wordLength, '_');

    int found = 0;
    char guess;
    int tries = 5; //No of wrong tries
    int flagFound = 0;
    std::set<char> guessedLetters;

    while (tries >= 0) {
        system("cls");
        cout << "Guess Name of Thing: " << endl << endl;

        for (int i = 0; i < wordLength; i++)
            cout << " " << dispWord[i] << " ";
        cout << endl << endl << endl;

        cout << "\033[0;33mAttempts: \033[0;37m" << tries << " / " << WRONGTRIES << endl;
        cout << "Guessed Letters: " << "'" << guessed << "'" << endl;

        DrawMan(tries);

        if (found == wordLength) {
            cout << endl;
            cout << endl << "Word is: \033[0;33m" << word << "\033[0;37m" << endl;
            cout << "\n\033[0;32m*****************" << endl;
            cout << "*    You Win    *" << endl;
            cout << "*****************\033[0;37m" << endl;
            break;
        }

        if (tries == 0) break;

        cout << "\n\033[0;31mPress 'esc' (for exit) \n\033[0;37m";
        cout << "\033[0;33mPick a Letter: \033[0;37m";
        guess = getche();

        if (guess == 27) {
            printf("\n");
            check_start_start();
        }

        while (!std::isalpha(guess)) {
            std::cout << "\nEnter only letters: ";
            guess = getche();
            //_getch();
            //continue;
        }

        if (guessedLetters.find(guess) != guessedLetters.end()) {
            cout << "\n\nYou already guessed this letter: " << "'" << guess << "'" << endl;
            getche();
            continue;
        }

        guessedLetters.insert(guess);
        guessed += " ";
        guessed += guess;

        if (dispWord.find(guess) != string::npos) tries++;

        flagFound = 0;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guess && dispWord[i] == '_') {
                dispWord[i] = guess;
                found++;
                flagFound = 1;
            }
        }

        if (!flagFound)
            tries--;
    }

    if (found != wordLength) {
        cout << endl;
        cout << endl << "Word is: \033[0;33m" << word << "\033[0;37m" << endl;
        cout << "\n\033[0;31m******************" << endl;
        cout << "*    You Lose    *" << endl;
        cout << "******************\033[0;37m" << endl;
    }

    getch();

    printf("\033[0;37m");
    check_start_start();
}
