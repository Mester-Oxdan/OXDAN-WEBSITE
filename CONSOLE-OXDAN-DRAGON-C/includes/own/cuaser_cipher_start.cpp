#include <stdio.h>//необходимо для printf
#include <conio.h>//необходимо для getch
#include <string.h>//необходимо для puts
#include <windows.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include "all_diclarations.h"

using namespace std;

#pragma warning(disable : 4996).

/*инициализируем переменные*/
int i87 = 0, n87 = 0, k98;
int d87;
char alf[] = "abcedfghijklmnopqrstuvwxyz0123456789#!@$%^&*-+=";//словарь
char buf[100];//массив для ввода сообщения
char decod[100];//массив для ввода сообщения

void cuaser_cipher_start()
{
	try
	{

		while (true)
		{
			system("cls");
			string op;

			cout << "\n\033[0;31mEnter 'esc' (for exit) \033[0;37m\n";
			cout << "\033[0;33m(1) Encryption (2) Decryption: \033[0;37m";

			cin >> op;
			boost::to_lower(op);
			boost::trim(op);
			cin.ignore();

			if (op == "1")
			{
				system("cls");
				cout << "\n\033[0;31mEnter 'esc' (for exit) \033[0;37m";
				printf("\n\033[0;33mEnter text: \033[0;37m");
				Sleep(1);
				cin.getline(buf, 100);
				cout << "\n\033[0;31mEnter 'esc' (for exit) \033[0;37m";
				printf("\n\033[0;33mEnter key: \033[0;37m");
				Sleep(1);
				cin >> k98;
				if (strcmp(buf, "esc") == 0 || strcmp(buf, "Esc") == 0 || strcmp(buf, "ESC") == 0 || to_string(k98) == "esc" || to_string(k98) == "Esc" || to_string(k98) == "ESC") {
					check_start_start();
				}
				else {
					for (n87 = 0; buf[n87] != '\0'; n87++)
					{
						for (i87 = 0; i87 < 47; i87++)
						{
							if (buf[n87] == alf[i87])
							{
								if (i87 + k98 >= 47)
									buf[n87] = alf[(i87 + k98) % 47];
								else
									buf[n87] = alf[i87 + k98];//сдвигаем вправо на показания шага ключа
								break;//принудительно выходим из цикла
							}
						}
					}
					cout << "\n" << "\033[0;33m" << "Encrypted message: " << "\033[0;37m" << buf << endl;
				}
				_getch();
				cuaser_cipher_start();
			}

			else if (op == "esc")
			{
				check_start_start();
			}

			else if (op == "2")
			{
				system("cls");
				/*Процедура дешифрования ввод*/
				cout << "\n\033[0;31mEnter 'esc' (for exit) \033[0;37m";
				printf("\n\033[0;33mEnter text: \033[0;37m");
				Sleep(1);
				cin.getline(decod, 100);
				cout << "\n\033[0;31mEnter 'esc' (for exit) \033[0;37m";
				printf("\n\033[0;33mEnter key: \033[0;37m");
				Sleep(1);
				cin >> d87;
				if (strcmp(decod, "esc") == 0 || strcmp(decod, "Esc") == 0 || strcmp(decod, "ESC") == 0 || to_string(d87) == "esc" || to_string(d87) == "Esc" || to_string(d87) == "ESC") {
					check_start_start();
				}
				else {
					for (n87 = 0; decod[n87] != '\0'; n87++)
					{
						for (i87 = 0; i87 < 47; i87++)
						{
							if (decod[n87] == alf[i87])
							{
								if (i87 - d87 < 0)
									decod[n87] = alf[47 + (i87 - d87)];
								else
									decod[n87] = alf[i87 - d87];//сдвигаем влево на показания шага ключа
								break;//принудительно выходим из цикла
							}
						}
					}

					cout << "\n" << "\033[0;33m" << "Decrypted message: " << "\033[0;37m" << decod << endl;
				}
				_getch();//задержка программы
				cuaser_cipher_start();
			}
		}
	}

	catch (...)
	{
		cuaser_cipher_start();
	}
}