#include <windows.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

bool gameOver;
int const screenHeight = 20;
int const screenWidth = 30;
int maptre[screenHeight][screenWidth];
int scoreP1;
int scoreP2;

class Paddletre
{
public:
	int x;
	int y;
	int speed;
	char dir;
	int delay;
	int count_delay;

	void draw()
	{
		for (int i = 0; i < 6; i++)
			maptre[y][x + i] = 1;
	}

	void move()
	{
		if (count_delay == delay && dir != 'S')
		{
			if (dir == 'L' && x - speed > 0)
			{
				x -= speed;
			}
			else if (dir == 'R' && x + speed < screenWidth - 6)
			{
				x += speed;
			}
			count_delay = 0;
		}
		count_delay++;
	}
};

class Balltre
{
public:
	int x;
	int y;
	int speed;
	int dir;
	int delay;
	int count_delay;

	void draw()
	{
		maptre[y][x] = 5;
	}

	void move()
	{
		if (count_delay == delay && dir != 9)
		{
			delay = 5;
			if (dir == 0 && !collision(x - speed, y - speed))
			{
				x -= speed;
				y -= speed;
			}
			else if (dir == 1 && !collision(x + speed, y - speed))
			{
				x += speed;
				y -= speed;
			}
			else if (dir == 2 && !collision(x - speed, y + speed))
			{
				x -= speed;
				y += speed;
			}
			else if (dir == 3 && !collision(x + speed, y + speed))
			{
				x += speed;
				y += speed;
			}
			count_delay = 0;
		}
		count_delay++;
	}

	bool collision(int fx, int fy)
	{
		if (maptre[fy][fx] == 9 || maptre[fy][fx] == 1 || maptre[fy][fx] == 7 || maptre[fy][fx] == 8)
		{
			bounce(fx, fy);
			return true;
		}
		return false;
	}

	void bounce(int fx, int fy)
	{
		if (maptre[fy][fx] == 1)
		{
			if (dir == 0) dir = 2;
			else if (dir == 1) dir = 3;
			else if (dir == 2) dir = 0;
			else if (dir == 3) dir = 1;
		}
		else if (maptre[fy][fx] == 9)
		{
			if (dir == 0) dir = 1;
			else if (dir == 1) dir = 0;
			else if (dir == 2) dir = 3;
			else if (dir == 3) dir = 2;
		}
		else if (maptre[fy][fx] == 7 || maptre[fy][fx] == 8)
		{
			delay = 50;
			x = screenWidth / 2;
			y = screenHeight / 2;
			dir = rand() % 4;
			if (maptre[fy][fx] == 8) scoreP2++;
			else if (maptre[fy][fx] == 7) scoreP1++;
		}
	}
};

Paddletre player1tre;
Paddletre player2tre;
Balltre balltre;

void walltre()
{
	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			if (j == 0 || j == screenWidth - 1) maptre[i][j] = 9;
			else maptre[i][j] = 0;
		}
	}
}

void scoreWalltre()
{
	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			if (i == 0)
			{
				maptre[i][j] = 8;
			}
			if (i == screenHeight - 1)
			{
				maptre[i][j] = 7;
			}
		}
	}
}

void setuptre()
{
	srand(time(NULL));
	gameOver = false;
	scoreP1 = 0;
	scoreP2 = 0;
	balltre.x = screenWidth / 2;
	balltre.y = screenHeight / 2;
	balltre.speed = 1;
	balltre.dir = rand() % 4;
	balltre.delay = 5;
	player1tre.x = screenWidth / 2 - 3;
	player1tre.y = screenHeight / 7;
	player1tre.speed = 2;
	player1tre.delay = 3;
	player2tre.x = screenWidth / 2 - 3;
	player2tre.y = screenHeight - screenHeight / 7 - 1;
	player2tre.speed = 2;
	player2tre.delay = 3;
}

void displaytre()
{
	gotoxy(15, 0); cout << "\033[0;33mSCORE:\033[0;37m";
	gotoxy(2, 1); cout << "PLAYER 1";
	gotoxy(24, 1); cout << "PLAYER 2";
	gotoxy(5, 2); cout << scoreP1;
	gotoxy(28, 2); cout << scoreP2;

	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			gotoxy(j + 2, i + 3);
			if (maptre[i][j] == 9) cout << char(219);
			if (maptre[i][j] == 1) cout << char(219);
			if (maptre[i][j] == 7 || maptre[i][j] == 8) cout << char(240);
			if (maptre[i][j] == 5) cout << char(254);
			if (maptre[i][j] == 0) cout << ' ';
		}
	}
}

void layouttre()
{
	walltre();
	scoreWalltre();
	player1tre.draw();
	player2tre.draw();
	balltre.draw();
}

void inputtre()
{
	if (kbhit())
	{
		switch (getch())
		{
		case 'a':
			player1tre.dir = 'L';
			break;
		case 'd':
			player1tre.dir = 'R';
			break;
		case 75:
			player2tre.dir = 'L';
			break;
		case 77:
			player2tre.dir = 'R';
			break;
		}
	}
}

void movementstre23()
{
	player1tre.move();
	player2tre.move();
	balltre.move();
}

void setuptre65()
{
	srand(time(NULL));
	gameOver = false;
	scoreP1 = 0;
	scoreP2 = 0;
	balltre.x = screenWidth / 2;
	balltre.y = screenHeight / 2;
	balltre.speed = 1;
	balltre.dir = rand() % 4;
	balltre.delay = 5;
	player1tre.x = screenWidth / 2 - 3;
	player1tre.y = screenHeight / 7;
	player1tre.speed = 2;
	player1tre.delay = 3;
	player2tre.x = screenWidth / 2 - 3;
	player2tre.y = screenHeight - screenHeight / 7 - 1;
	player2tre.speed = 2;
	player2tre.delay = 3;
}

void ping_pong_2_start()
{
	system("cls");
	HWND s = GetConsoleWindow();
	MoveWindow(s, 300, 200, 300, 420, true);
	hideCursor();
	setuptre65();
	while (!gameOver)
	{
		displaytre();
		layouttre();
		inputtre();
		movementstre23();

		if (GetKeyState(VK_ESCAPE) < 0)
		{
			system("mode 141, 29"); // set size of console (+)
			SetWindow(600, 600); // set buffer size of console (+)
			check_start_start();
		}
	}

	if (GetKeyState(VK_ESCAPE) < 0)
	{
		system("mode 141, 29"); // set size of console (+)
		SetWindow(600, 600); // set buffer size of console (+)
		check_start_start();
	}
}