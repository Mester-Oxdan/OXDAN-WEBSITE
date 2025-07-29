#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <shlobj_core.h>
#include <atlstr.h>
#include <chrono>
#include <conio.h>
#include <mmsystem.h>
#include <SFML/Audio.hpp>
#include "all_diclarations.h"

#pragma warning(disable : 4996).
#pragma comment(lib, "winmm.lib") // Link with the Windows Multimedia library

using namespace std;

void changeVolumeoff()
{
	INPUT ip = { 0 };
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = VK_VOLUME_MUTE;   //or VOLUME_DOWN or MUTE
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void changeVolumeon()
{
	INPUT ip = { 0 };
	ip.type = INPUT_KEYBOARD;
	ip.ki.wVk = VK_VOLUME_MUTE;   //or VOLUME_DOWN or MUTE
	SendInput(1, &ip, sizeof(INPUT));
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void Own(bool willstart, clock_t timer, vector<string> &history)
{
	if (x == "shutdown") // shutdown (+)
	{
		try
		{
			system("shutdown /s");
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "restart") // restart (+)
	{
		try
		{
			system("shutdown /r");
		}

		catch (...)
		{
			check_start_start();
		}
	}

	/*else if (x == "send_ph_message") // send_ph_message (+)
	{
		try
		{
			send_ph_message_start();
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
	}*/

	/*if (x == "color") // color (+)
	{

		if (tokens.size() < 2)
		{
			check_start_start();
		}

		else
		{
			char buf[256];
			string name = tokens[1];

			try
			{
				color_start(name);
			}

			catch (...)
			{
				check_start_start();
			}
		}
	}*/

	else if (x == "color_back") // color_back (+)
	{

		if (tokens.size() < 2)
		{
			check_start_start();
		}

		else
		{

			char buf[256];
			string name = tokens[1];

			try
			{
				color_back_start(name);
			}

			catch (...)
			{
				printf("\033[0;31m");
				printf("\n");
				printf("(!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				printf("(!Enter color_back option!)\n");
				printf("\033[0;37m");
			}
		}
	}

	else if (x == "title") // title (+)
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter name for your title!)\n");
			printf("\033[0;37m");
		}

		else
		{
			try
			{
				string a = tokens[1];
				SetConsoleTitleA(a.c_str());
			}

			catch (...)
			{
				printf("\033[0;31m");
				printf("\n");
				printf("(!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				printf("(!Enter name for your title!)\n");
				printf("\033[0;37m");
			}
		}

		check_start_start();
	}

	else if (x == "date") // date (+)
	{
		try
		{
			time_t ttime = time(0);

			char* dt = ctime(&ttime);
			cout << "\n" << "\033[0;33m" << "Date: " << "\033[0;37m" << dt << endl;

			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "i_am_here") // i_am_here (+)
	{
		try
		{
			std::string start_time = getCurrentTime();
			std::cout << "\n\033[0;33mTime Start: \033[0;37m" << start_time << std::endl;
			Sleep(1);
			clock_t timer = clock();
			std::cout << "\033[0;33mTime Spent: \033[0;37m" << round((double(timer) / CLOCKS_PER_SEC)) << " seconds, " << round((double(timer) / CLOCKS_PER_SEC) / 60) << " minutes, " << round(((double(timer) / CLOCKS_PER_SEC) / 60) / 60) << " hours, " << round((((double(timer) / CLOCKS_PER_SEC) / 60) / 60) / 24) << " days, " << std::endl;

			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "rules") // rules (+)
	{
		try
		{
			instructions_rules();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "commands") // commands (+)
	{
		try
		{
			commands_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "tips") // tips (+)
	{
		try
		{
			tips_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "links") // links (+)
	{
		try
		{
			links_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "history") // history (+)
	{
		try
		{
			printf("\n");
			printf("\033[0;33mHISTORY: \033[0;37m");
			printf("\n");
			for (int i = 0; i < history.size(); i++) {
					cout << i << ") " << history[i] << endl;
			}
			//printf("\n");

			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "cls_history") // cls_history (+)
	{
		try
		{

			history.clear();

			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "&main") // &main (+)
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter &main option!)\n");
			printf("\033[0;37m");
		}

		else
		{
			string man = tokens[1];

			try
			{
				main_start_start(man, willstart);
			}

			catch (...)
			{
				printf("\033[0;31m");
				printf("\n");
				printf("(!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				printf("(!Enter &main option!)\n");
				printf("\033[0;37m");
				check_start_start();
			}
		}

	}

	else if (x == "helpers") // helpers (+)
	{
		try
		{

			helpers_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "donators") // donators (+)
	{
		try
		{

			donators_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "my_location") // my_location (+)
	{
		try
		{
			my_location_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "system_info") // system_info (+)
	{
		try
		{
			system_info_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "set_volume_level") // set_volume_level (+)
	{
		try
		{
			string ma90n = tokens[1];

			set_volume_level_start(ma90n);
		}

		catch (...)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter integers only!)\n");
			printf("\033[0;37m");
			check_start_start();
		}
	}

	else if (x == "ip") // ip (+)
	{
		try
		{
			ip_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "i?") // i? (+)
	{
		try
		{
			if (IsUserAnAdmin() == true)
			{
				printf("\n");
				printf("You are: 'Super User/Admin' \n");
			}

			else if (IsUserAnAdmin() == false)
			{
				printf("\n");
				printf("You are: 'User' \n");
			}
			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "donate") // donate (+)
	{
		try
		{
			system("cls");
			gotoxy(47, 4);
			printf("Thanks for your support! If you haven't changed your ");
			gotoxy(47, 5);
			printf("mind, here is author's Buy Me A Coffee and Cash App.");
			gotoxy(50, 6);
			printf("Please don't exceed limit amount ($1 - $100).");
			gotoxy(69, 7);
			printf("Thanks.");
			gotoxy(57, 9);
			printf("\033[0;33mCash App:\033[0;37m 4403 9352 3234 1307");
			gotoxy(48, 11);
			printf("\033[0;33mBuy Me A Coffee:\033[0;37m https://www.buymeacoffee.com/oxdan");
			gotoxy(59, 13);
			printf("Press any key to go back.");
			_getch();
			printf("\n");
			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "memory") // memory (+)
	{
		try
		{
			memory_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "promo_code") // promo_code (+)
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
				printf("(!Enter promo code name!)\n");
				printf("\033[0;37m");
				check_start_start();
			}

			else
			{
				try
				{
					string a = tokens[1];
					//SetConsoleTitleA(a.c_str());

					if (a == "sans-battle" || a == "sansbattle" || a == "sans_battle")
					{
						cout << "\n\033[0;33mSecret Link:\033[0;37m https://jcw87.github.io/c2-sans-fight/" << endl;
						check_start_start();
					}
					if (a == "toby-fox" || a == "tobyfox" || a == "toby_fox")
					{
						cout << "\nThanks a lot! You are the hero of my childhood. \n(Big a fan) Thanks for \033[0;31mUndertale\033[0;37m game :)" << endl;
						sf::SoundBuffer buffer_4;
						!buffer_4.loadFromFile(oxdan_dragon_c + "/includes/own/undertale.wav");
						sf::Sound sound_4;
						sound_4.setBuffer(buffer_4);
						sound_4.play();
						check_start_start();
					}
					if (a == "scott-cawthon" || a == "scottcawthon" || a == "scott_cawthon")
					{
						cout << "\nThanks a lot! You are the one more hero of my childhood. \n(Big a fan) Thanks for \033[0;33mFive Nights at Freddy's\033[0;37m game :)" << endl;
						sf::SoundBuffer buffer_3;
						!buffer_3.loadFromFile(oxdan_dragon_c + "/includes/own/freddy_nouse.wav");
						sf::Sound sound_3;
						sound_3.setBuffer(buffer_3);
						sound_3.play();

						sf::SoundBuffer buffer_2;
						!buffer_2.loadFromFile(oxdan_dragon_c + "/includes/own/fnaf_beatbox_1.wav");
						sf::Sound sound_2;
						sound_2.setBuffer(buffer_2);
						sound_2.play();
						check_start_start();
					}
					else
					{
						cout << "\n'" + a + "'" + " Is \033[0;31mwrong\033[0;37m promo-code\n";
						check_start_start();
					}
				}

				catch (...)
				{
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!Enter promo code name!)\n");
					printf("\033[0;37m");
					check_start_start();
				}
			}

			//check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "size") // size (+)
	{
		if (tokens.size() < 3)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter 2 parameters! (without ','))\n");
			printf("\033[0;37m");
		}

		else
		{
			try
			{
				string cmd;
				char buf[256];
				string path451 = tokens[1];
				string path452 = tokens[2];

				cmd = "mode ";
				cmd += path451 + "," + path452;
				system(cmd.c_str());
				SetWindow(141, 29); // set buffer size of console (+)
			}

			catch (...)
			{
				printf("\033[0;31m");
				printf("\n");
				printf("(!ERROR!)");
				printf("\033[0;37m");
				printf(" = ");
				printf("\033[0;32m");
				printf("(!Enter 2 parameters! (without ','))\n");
				printf("\033[0;37m");
			}

		}
		check_start_start();
	}

	else if (x == "administrator" || x == "admin" || x == "superuser") // administrator (+)
	{
		try
		{
			//char buf143[256];
			//SetCurrentDirectoryA("..");
			//GetCurrentDirectoryA(255, buf143);
			//printf(buf1);
			string cmd;
			//cmd += buf143;
			cmd += oxdan_dragon_c + "\\CONSOLE-OXDAN-DRAGON-C++.exe";
			
			//printf(cmd.c_str());

			const char* ref = cmd.c_str();

			ShellExecuteA(NULL, "runas", ref, NULL, NULL, SW_SHOW);

			exit(0);

		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "my_volume_level") // my_volume_level (+)
	{
		try
		{
			my_volume_level();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "set_mute") // set_mute (+)
	{
		try
		{
				string path451 = tokens[1];

				if (path451 == "on")
				{
					changeVolumeon();
					check_start_start();
				}

				if (path451 == "off")
				{
					changeVolumeoff();
					check_start_start();
				}

				else
				{
					printf("\033[0;31m");
					printf("\n");
					printf("(!ERROR!)");
					printf("\033[0;37m");
					printf(" = ");
					printf("\033[0;32m");
					printf("(!Enter set_mute option)\n");
					printf("\033[0;37m");
					check_start_start();
				}

		}

		catch (...)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter set_mute option)\n");
			printf("\033[0;37m");
			check_start_start();
		}
	}

	else if (x == "energy" || x == "power") // energy (+)
	{
		try
		{
			energy_start();
		}

		catch (...)
		{
			check_start_start();
		}
	}

	else if (x == "new" || x == "start") // new (+)
	{
		try
		{
			// C:\Users\bogda\source\repos\CONSOLE-OXDAN-DRAGON-C++\x64\Debug\CONSOLE-OXDAN-DRAGON-C++.exe
			//ShellExecute(NULL, NULL, L"C:\\Users\\bogda\\source\\repos\CONSOLE-OXDAN-DRAGON-C++\\x64\\Debug\\CONSOLE-OXDAN-DRAGON-C++.exe", NULL, NULL, SW_SHOW);
			//system("start C:\\Users\\bogda\\source\\repos\\CONSOLE-OXDAN-DRAGON-C++\\x64\\Debug\\CONSOLE-OXDAN-DRAGON-C++.exe");
			//char buf143[256];
			//SetCurrentDirectoryA("..");
			//GetCurrentDirectoryA(255, buf143);
			//printf(buf1);
			string cmd = "start ";
			cmd += oxdan_dragon_c;
			cmd += "\\CONSOLE-OXDAN-DRAGON-C++.exe";

			system(cmd.c_str());
			SetCurrentDirectoryA("CONSOLE-OXDAN-DRAGON-C++");
			//exit(0);

			check_start_start();
		}

		catch (...)
		{
			check_start_start();
		}

	}

	else if (x == "open") // open (+)
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter path to your program!)\n");
			printf("\033[0;37m");
		}

		else
		{
			char buf[256];
			string path45 = tokens[1];

			try
			{
				open_start(path45);
				check_start_start();
			}

			catch (...)
			{
				check_start_start();
			}
		}

		

	}

	else if (x == "chan_backg") // chan_backg (+)
	{

		if (tokens.size() < 2)
		{
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			printf("(!Enter path to photo!)\n");
			printf("\033[0;37m");
		}
		else
		{
			try
			{
				string path = tokens[1];

				SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)path.c_str(), SPIF_UPDATEINIFILE);
			}

			catch (...)
			{
				check_start_start();
			}
		}

		check_start_start();
	}

}