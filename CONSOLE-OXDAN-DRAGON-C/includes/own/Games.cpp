#include <windows.h>
#include <vector>
#include <iostream>
#include <conio.h>
#include "all_diclarations.h"

using namespace std;

void Games()
{
	if (x == "pacman") // pacman (+)
	{
		try
		{
			pacman_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	if (x == "doom") // doom (+)
	{

			
			try
			{
				printf("\n");
				string filePath = "start " + oxdan_dragon_c + "/includes/own/test_python_py_doom.py";
				system(filePath.c_str());
				//printf(cmd_io.c_str());
				check_start_start();
			}

			catch (...)
			{
				check_start_start();
			}
	}

	if (x == "2048") // 2048 (+)
	{
		try
		{
			start_2048_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	if (x == "car_racing") // car_racing (+)
	{
		try
		{
			car_racing_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	if (x == "tic_tac_toe") // tic_tac_toe (+)
	{
		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter tic_tac_toe option!)\n");
			printf("\033[0;37m");

			check_start_start();
		}

		else
		{
			char buf[256];
			string name56 = tokens[1];

			if (name56 == "ai") // (+)
			{
				try
				{
					tic_tac_toe_ai_start();
				}

				catch (...)
				{
					check_start_start();
				}
			}

			if (name56 == "2") // (+)
			{
				try
				{
					// add icon

					tic_tac_toe_2_start();
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
				printf("(!Enter tic_tac_toe option!)\n");
				printf("\033[0;37m");

				check_start_start();
			}
		}
	}

	if (x == "ping_pong") // ping_pong (+)
	{
		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter ping_pong option!)\n");
			printf("\033[0;37m");

			check_start_start();
		}

		else
		{
			char buf[256];
			string name = tokens[1];

			if (name == "1") // (+)
			{
				try
				{
					ping_pong_1_start();
				}

				catch (...)
				{
					check_start_start();
				}

			}

			if (name == "2") // (+)
			{
				try
				{
					ping_pong_2_start();
				}

				catch (...)
				{
					check_start_start();
				}
			}
			if (name == "ai") // (+)
			{
				try
				{
					ping_pong_ai_start();
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
				printf("(!Enter ping_pong option!)\n");
				printf("\033[0;37m");

				check_start_start();
			}

		}

	}

	if (x == "arkanoid") // arkanoid (-)
	{
		try
		{
			// add icon
			// add not close window

			arkanoid_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "tetris") // tetris (-)
	{
		try
		{

			tetris_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "chess") // chess (+)
	{
		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter chess option!)\n");
			printf("\033[0;37m");

			check_start_start();
		}

		else
		{
			char buf[256];
			string name = tokens[1];

			if (name == "ai")
			{
				try
				{
					chess_ai_start();
					check_start_start();
				}

				catch (...)
				{
					check_start_start();
				}
			}

			if (name == "2")
			{
				try
				{
					chess_2_start();
					check_start_start();
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
				printf("(!Enter chess option!)\n");
				printf("\033[0;37m");

				check_start_start();
			}

		}
		system("cls");
		printf(" \033[0;37m");
		check_start_start(); // (+)
	}

	else if (x == "checkers") // checkers (+)
	{
		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter checkers option!)\n");
			printf("\033[0;37m");

			check_start_start();
		}

		else
		{
			char buf[256];
			string name_90y = tokens[1];

			if (name_90y == "2")
			{
				try
				{
					checkers_2_start();
					check_start_start();
				}

				catch (...)
				{
					check_start_start();
				}
			}

			else if (name_90y == "ai")
			{
				try
				{
					checkers_ai_start();
					check_start_start();
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
				printf("(!Enter checkers option!)\n");
				printf("\033[0;37m");

				check_start_start();
			}

		}
		system("cls");
		printf(" \033[0;37m");
		check_start_start(); // (+)
	}

	else if (x == "snake") // snake (+)
	{
		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter snake option!)\n");
			printf("\033[0;37m");

			check_start_start();
		}

		else
		{
			char buf[256];
			string name = tokens[1];

			if (name == "ai")
			{
				try
				{
					snake_ai_start();
				}

				catch (...)
				{
					check_start_start();
				}
			}

			if (name == "1")
			{
				try
				{
					snake_1_start();
				}

				catch (...)
				{
					check_start_start();
				}
			}

			if (name == "2")
			{
				try
				{
					snake_2_start();
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
				printf("(!Enter snake option!)\n");
				printf("\033[0;37m");

				check_start_start();
			}

		}
		system("cls");
		printf(" \033[0;37m");
		system("mode 148, 29"); // set size of console (+)
		SetWindow(143, 33); // set buffer size of console (+)
		check_start_start(); // (+)
	}

	else if (x == "guess_number") // guess_number (+)
	{
		try
		{
			guess_number_start();
		}

		catch (...)
		{
			check_start_start();
		}

	}

	else if (x == "battle_city") // battle_city (+)
	{
		try
		{
			battle_city_start();
		}

		catch (...)
		{
			check_start_start();
		}

	}

	else if (x == "mario") // mario (+)
	{
		try
		{
			mario_start();
			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}

	}

	else if (x == "space_shooter") // space_shooter (+)
	{
		try
		{
			space_shooter_start();
		}

		catch (...)
		{
			check_start_start();
		}

	}

	else if (x == "typing_tutor") // typing_tutor (+)
	{
		try
		{
			system("mode 95, 29"); // set size of console (+)
			//SetWindow(141, 29); // set buffer size of console (+)
			typing_tutor_start();
			SetWindow(147, 29); // set buffer size of console (+)
		}

		catch (...)
		{
			check_start_start();
		}

	}

	else if (x == "hangman") // hangman (+)
	{
		try
		{
			hangman_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "flappy_bird") // flappy bird (+)
	{
		try
		{
			flappybird_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}
}