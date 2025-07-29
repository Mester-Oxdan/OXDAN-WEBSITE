#include <iostream>
#include <fstream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "all_diclarations.h"

using namespace std;

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Window title
const string TITLE = "Notepad";

void drawFlashingCursor(sf::Text& text, sf::RenderWindow& window)
{
    static sf::Clock cursorClock;
    static bool cursorVisible = true;
    int lastCharPos = text.getString().getSize();

    // Draw the cursor only if half a second has elapsed
    if (cursorClock.getElapsedTime().asSeconds() >= 0.5f)
    {
        cursorVisible = !cursorVisible;
        cursorClock.restart();
    }

    if (cursorVisible)
    {
        // Get the position of the last character entered
        sf::Vector2f lastCharPosition = text.findCharacterPos(lastCharPos);

        // Draw the cursor as a small horizontal line under the last character
        sf::RectangleShape cursor(sf::Vector2f(text.getCharacterSize() / 2, text.getCharacterSize() / 8));
        cursor.setPosition(lastCharPosition.x, lastCharPosition.y + text.getLocalBounds().height + 7);
        cursor.setFillColor(sf::Color::Black);
        window.draw(cursor);
    }
}


void notepad_start() 
{
    cout << "\n";
    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE);

    // Create a font for the text
    sf::Font font;

    // Check if the font was loaded successfully
    string text_font_file = (oxdan_dragon_c + "\\includes\\own\\resuorces\\fonts\\arial.ttf");
    if (!font.loadFromFile(text_font_file)) {
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        printf("(!Failed to load Font!)\n");
        printf("\033[0;37m");
        //cout << oxdan_dragon_c << "\\includes\\own\\resuorces\\fonts\\arial.ttf";
        check_start_start();
    }

    // Create a text object for displaying the user's input
    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(24);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(sf::Vector2f(10, 10));

    sf::Image icon;
    if (!icon.loadFromFile(oxdan_dragon_c + "\\includes\\own\\my_dragon_ico.jpg")) {
        // Handle error loading icon file
        printf("\033[0;31m");
        printf("\n");
        printf("(!ERROR!)");
        printf("\033[0;37m");
        printf(" = ");
        printf("\033[0;32m");
        printf("(!Failed to load Files!)\n");
        printf("\033[0;37m");
        check_start_start();
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Create a string to hold the user's input
    string inputString = "";

    // Loop until the window is closed
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                check_start_start();
            }
            else if (event.text.unicode == 8 && !inputString.empty()) { // Check if the pressed key is backspace
                // Remove the last character from the input string
                inputString.pop_back();

                // Update the input text
                inputText.setString(inputString);
            }
            else if (event.type == sf::Event::TextEntered) {
                // Check if the user pressed the enter key
                if (event.text.unicode == '\r' || event.text.unicode == '\n') {

                    inputString += "\n";

                    // Save the user's input to a file
                    ofstream file("notepad.txt", ios::app);
                    file << inputString;
                    file.close();
                    //cout << "Text \033[0;32msaved\033[0;37m to file notepad.txt" << endl;
                    printf("\033[0;32m");
                    printf("\n");
                    printf("(!SUCCESS!)");
                    printf("\033[0;37m");
                    printf(" = ");
                    printf("\033[0;33m");
                    printf("(!Text saved to file notepad.txt!)\n");
                    printf("\033[0;37m");
                    // Clear the input string
                    inputString = "";
                }
                else {
                    // Append the user's input to the input string
                    inputString += static_cast<char>(event.text.unicode);
                }

                // Update the input text
                inputText.setString(inputString);
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the input text
        window.draw(inputText);

        drawFlashingCursor(inputText, window);

        // Display the window
        window.display();
    }
}
