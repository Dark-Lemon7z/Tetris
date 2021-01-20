#pragma once
#ifndef __HEADER_UTILITY_
#define __HEADER_UTILITY_

#include <iostream>
#include <windows.h>

class Util
{
public:
	void gotoxy(short x, short y)
	{
		COORD Pos = { static_cast<SHORT>(x - 1), static_cast<SHORT>(y - 1) };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	void cursor(int n)
	{
		HANDLE hConsole;
		CONSOLE_CURSOR_INFO ConsoleCursor;

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		ConsoleCursor.bVisible = n;
		ConsoleCursor.dwSize = 1;

		SetConsoleCursorInfo(hConsole, &ConsoleCursor);

		system("mode con:cols=70 lines=40");
	}
};

#endif //__HEADER_UTILITY_