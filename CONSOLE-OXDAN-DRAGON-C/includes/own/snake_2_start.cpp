#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "all_diclarations.h"

#pragma warning(disable : 4996).

using namespace std;

#define sLen 1000
#define mWidth 80 //80
#define mHeight 25 //25

struct TMapsnk
{
	char map1[mHeight][mWidth + 1];
	void Clear();
	void Show();
};

enum TDirectionsnk { dirLeftsnk, dirRightsnk, dirUpsnk, dirDownsnk };
enum TResultsnk { reOksnk, reKillsnk };

class TSnakesnk {
	int x, y;
	TMapsnk* mp;
	TDirectionsnk dir;
	POINT tail[sLen];
	int len;
	int score;
	POINT OutTextPos;
public:
	void AddTailsnk(int _x, int _y);
	void MoveTailsnk(int _x, int _y);
	void AddTailCntsnk(int _x, int _y, int cnt);
	TSnakesnk(TMapsnk* _mp, int outX, int outY);
	void Initsnk(int _x, int _y, TDirectionsnk _dir);
	void PutOnMapsnk();
	TResultsnk UserControlsnk(char w, char s, char a, char d);
	void IncScoresnk();
};

void TSnakesnk::IncScoresnk()
{
	score++;
}

void TSnakesnk::AddTailCntsnk(int _x, int _y, int cnt)
{
	for (int i = 0; i < cnt; i++)
		AddTailsnk(_x, _y);
}

void TSnakesnk::MoveTailsnk(int _x, int _y)
{
	for (int i = len - 1; i >= 0; i--)
		tail[i + 1] = tail[i];
	tail[0].x = _x;
	tail[0].y = _y;
}

void TSnakesnk::AddTailsnk(int _x, int _y)
{
	MoveTailsnk(_x, _y);
	len++;
	if (len >= sLen) len = sLen - 1;
}

TResultsnk TSnakesnk::UserControlsnk(char w, char s, char a, char d)
{
	POINT old;
	old.x = x;
	old.y = y;

	if (GetKeyState(w) < 0) dir = dirUpsnk;
	if (GetKeyState(s) < 0) dir = dirDownsnk;
	if (GetKeyState(a) < 0) dir = dirLeftsnk;
	if (GetKeyState(d) < 0) dir = dirRightsnk;
	if (dir == dirLeftsnk) x--;
	if (dir == dirRightsnk) x++;
	if (dir == dirUpsnk) y--;
	if (dir == dirDownsnk) y++;

	if ((x < 0) || (x >= mWidth) ||
		(y < 0) || (y >= mHeight) ||
		(mp->map1[y][x] == '+'))
		return reKillsnk;

	if (mp->map1[y][x] == '*')
		AddTailCntsnk(old.x, old.y, 5);
	else
		MoveTailsnk(old.x, old.y);

	return reOksnk;
}

void TSnakesnk::Initsnk(int _x, int _y, TDirectionsnk _dir)
{
	x = _x;
	y = _y;
	dir = _dir;
	len = 0;
}

void TSnakesnk::PutOnMapsnk()
{
	char str[10];
	sprintf(str, "%d", score);
	for (int i = 0; i < strlen(str); i++)
		mp->map1[OutTextPos.y][OutTextPos.x + i] = str[i];

	mp->map1[y][x] = '@';
	for (int i = 0; i < len; i++)
		mp->map1[tail[i].y][tail[i].x] = '+';
}

TSnakesnk::TSnakesnk(TMapsnk* _mp, int outX, int outY)
{
	mp = _mp;
	Initsnk(0, 0, dirRightsnk);
	score = 0;
	OutTextPos.x = outX;
	OutTextPos.y = outY;
}

void MoveXYsnk(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void TMapsnk::Show()
{
	MoveXYsnk(0, 0);
	map1[mHeight - 1][mWidth - 1] = '\0';
	for (int j = 0; j < mHeight; j++)
		cout << map1[j];

	gotoxy(31, 0); cout << "\033[0;31mPress 'Esc' for exit\033[0;37m";
	gotoxy(38, 1); cout << "\033[0;33mSCORE:\033[0;37m";
	
}

void TMapsnk::Clear()
{
	for (int i = 0; i < mWidth; i++)
		map1[0][i] = ' ';
	map1[0][mWidth] = '\0';
	for (int j = 1; j < mHeight; j++)
		strncpy(map1[j], map1[0], mWidth + 1);

	map1[12][20] = '*'; //12, 20
	map1[12][60] = '*'; //12, 60
	map1[5][40] = '*'; //5, 40
	map1[20][40] = '*'; //20, 40

}

enum TDirection { dirLeft, dirRight, dirUp, dirDown };
enum TResult { reOk, reKill };

void snake_2_start()
{
	system("mode 80, 27"); // set size of console (+)
	//SetWindow(80, 27); // set buffer size of console (+)
	int userCnt = 2;
	TMapsnk map1;
	TSnakesnk snake1(&map1, 3, 1);
	TSnakesnk snake2(&map1, 77, 1);
	snake1.Initsnk(10, 5, dirRightsnk);
	snake2.Initsnk(70, 5, dirRightsnk);
	do
	{
		bool kill1 = snake1.UserControlsnk('W', 'S', 'A', 'D') == reKill;
		if ((kill1)
			|| ((userCnt >= 2)
				&& (snake2.UserControlsnk(VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT) == reKill))
			)
		{
			snake1.Initsnk(10, 5, dirRightsnk);
			snake2.Initsnk(70, 5, dirLeftsnk);
			if (kill1)
				snake2.IncScoresnk();
			else
				snake1.IncScoresnk();
		}
		map1.Clear();
		snake1.PutOnMapsnk();
		if (userCnt >= 2) snake2.PutOnMapsnk();
		map1.Show();
		Sleep(80);
	} 
	
	while (GetKeyState(VK_ESCAPE) >= 0);
	system("mode 141, 29"); // set size of console (+)
	SetWindow(141, 29); // set buffer size of console (+)
	check_start_start();
}