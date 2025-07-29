#include <time.h>
//#include <windows.h>
#include "raylib.h"
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <string.h>
#include <iostream>
#include "show_messagebox778.h"
#include "all_diclarations.h"

using namespace std;

string enter_question_go, enter_response_yes;

void main_question_no(string enter_question, string enter_response_yes)
{
    system("cls");

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, enter_question.c_str());

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    string string_no_1 = oxdan_dragon_c + "\\my_dragon_ico_transformed.png";
    Image icon = LoadImage(string_no_1.c_str());  // Load an image for the icon
    SetWindowIcon(icon);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        Vector2 mousePosition = GetMousePosition();    // Get the position of the mouse

        srand(time(0));
        int location_no_x = (rand() % 150) + 50;
        int location_no_y = (rand() % 150) + 50;

        srand(time(0));
        int location_no_x_y_option = (rand() % 4) + 1;

        Rectangle buttonYes = { screenWidth / 2 - 100, screenHeight / 2 - 25, 50, 50 };
        Rectangle buttonNo = { screenWidth / 2 + 50, screenHeight / 2 - 25, 50, 50 };

        //if (CheckCollisionPointRec(mousePosition, buttonYes))
        //{
            //buttonYes.x += 100;
            //buttonNo.x -= 100;
        //}

        //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        //{
        if (CheckCollisionPointRec(mousePosition, buttonNo))
        {

            //int location_no_x_y = location_no_x, location_no_y;
            //Rectangle location_no_x_y = { location_no_x, location_no_y };

            if (location_no_x_y_option == 1)
            {

                buttonNo.x += location_no_x;
                buttonNo.y -= location_no_y;
            }

            if (location_no_x_y_option == 2)
            {

                buttonNo.x -= location_no_x;
                buttonNo.y += location_no_y;
            }

            if (location_no_x_y_option == 3)
            {

                buttonNo.x += location_no_x;
                buttonNo.y += location_no_y;
            }

            if (location_no_x_y_option == 4)
            {

                buttonNo.x -= location_no_x;
                buttonNo.y -= location_no_y;
            }

            //Rectangle buttonNo = location_no_x_y;

            //main_question(enter_question, buttom_1, run_away_buttom);

        //buttonNo.x += 56;
        //buttonNo.y += 36;

        }
        //}

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(enter_question.c_str(), screenWidth / 2 - MeasureText(enter_question.c_str(), 40) / 2, screenHeight / 2 - 80, 40, BLACK);

        DrawRectangleRec(buttonYes, WHITE);
        DrawText("Yes", buttonYes.x + buttonYes.width / 2 - MeasureText("Yes", 20) / 2, buttonYes.y + buttonYes.height / 2 - 10, 20, BLACK);

        DrawRectangleRec(buttonNo, WHITE);
        DrawText("No", buttonNo.x + buttonNo.width / 2 - MeasureText("No", 20) / 2, buttonNo.y + buttonNo.height / 2 - 10, 20, BLACK);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePosition, buttonYes))
            {
                CloseWindow();
                WindowShouldClose();
                show_messagebox(enter_response_yes);
               
            }
        }

        //----------------------------------------------------------------------------------
    }

    WindowShouldClose();

    //SetConfigFlags(FLAG_WINDOW_HIDDEN);

    //SetConfigFlags(FLAG_WINDOW_NO_CLOSE);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}

void prank_button_no()
{
    system("cls");

    cout << "\033[0;33mEnter main question (space = '_'): \033[0;37m";
    cin >> enter_question_go;

    cout << "\n\033[0;33mEnter response for button 'yes' (space = '_'): \033[0;37m";
    cin >> enter_response_yes;

    main_question_no(enter_question_go, enter_response_yes);

}

void main_question_yes(string enter_question, string enter_response_yes)
{
    system("cls");

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, enter_question_go.c_str());

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    string string_yes_1 = oxdan_dragon_c + "\\my_dragon_ico_transformed.png";
    Image icon = LoadImage(string_yes_1.c_str());  // Load an image for the icon
    SetWindowIcon(icon);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        // Update
        //----------------------------------------------------------------------------------
        Vector2 mousePosition = GetMousePosition();    // Get the position of the mouse

        srand(time(0));
        int location_no_x = (rand() % 150) + 50;
        int location_no_y = (rand() % 150) + 50;

        srand(time(0));
        int location_no_x_y_option = (rand() % 4) + 1;

        Rectangle buttonYes = { screenWidth / 2 - 100, screenHeight / 2 - 25, 50, 50 };
        Rectangle buttonNo = { screenWidth / 2 + 50, screenHeight / 2 - 25, 50, 50 };

        //if (CheckCollisionPointRec(mousePosition, buttonYes))
        //{
            //buttonYes.x += 100;
            //buttonNo.x -= 100;
        //}

        //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        //{
        if (CheckCollisionPointRec(mousePosition, buttonNo))
        {

            //int location_no_x_y = location_no_x, location_no_y;
            //Rectangle location_no_x_y = { location_no_x, location_no_y };

            if (location_no_x_y_option == 1)
            {

                buttonNo.x += location_no_x;
                buttonNo.y -= location_no_y;
            }

            if (location_no_x_y_option == 2)
            {

                buttonNo.x -= location_no_x;
                buttonNo.y += location_no_y;
            }

            if (location_no_x_y_option == 3)
            {

                buttonNo.x += location_no_x;
                buttonNo.y += location_no_y;
            }

            if (location_no_x_y_option == 4)
            {

                buttonNo.x -= location_no_x;
                buttonNo.y -= location_no_y;
            }

            //Rectangle buttonNo = location_no_x_y;

            //main_question(enter_question, buttom_1, run_away_buttom);

        //buttonNo.x += 56;
        //buttonNo.y += 36;

        }
        //}

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(enter_question.c_str(), screenWidth / 2 - MeasureText(enter_question.c_str(), 40) / 2, screenHeight / 2 - 80, 40, BLACK);

        DrawRectangleRec(buttonYes, WHITE);
        DrawText("No", buttonYes.x + buttonYes.width / 2 - MeasureText("No", 20) / 2, buttonYes.y + buttonYes.height / 2 - 10, 20, BLACK);

        DrawRectangleRec(buttonNo, WHITE);
        DrawText("Yes", buttonNo.x + buttonNo.width / 2 - MeasureText("Yes", 20) / 2, buttonNo.y + buttonNo.height / 2 - 10, 20, BLACK);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(mousePosition, buttonYes))
            {
                CloseWindow();
                WindowShouldClose();
                show_messagebox(enter_response_yes);

            }
        }

        //----------------------------------------------------------------------------------
    }

    WindowShouldClose();

    //SetConfigFlags(FLAG_WINDOW_HIDDEN);

    //SetConfigFlags(FLAG_WINDOW_NO_CLOSE);

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}

void prank_button_yes()
{
    system("cls");

    cout << "\033[0;33mEnter main question (space = '_'): \033[0;37m";
    cin >> enter_question_go;

    cout << "\n\033[0;33mEnter response for button 'no' (space = '_'): \033[0;37m";
    cin >> enter_response_yes;

    main_question_yes(enter_question_go, enter_response_yes);

}