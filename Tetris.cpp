#include "Tetris.h"
#include "Utility.h"
#define COLOR(A) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),A); // set color
using namespace std;
TetrinoDeclair Tetrino;
Util util;
int iState = 0;

void init()
{
	int i;
	util.cursor(0);
	COLOR(0xf);
	for (i = 0; i < 22; i++)
	{
		Tetrino.newinBoard[i][0] = -99;
		Tetrino.newinBoard[i][11] = -99;
	}
	for (i = 0; i < 11; i++)
	{
		Tetrino.newinBoard[21][i] = -99;
	}
}
void Tetris::Input()
{
	static int iKey, i, n;
	int curblock;
	if (_kbhit())
	{
		iChanging = 1;
		iKey = _getch();
		/*if (iKey == 224 && iKey != 'x')
		{
			iChanging = 0;
			return;
		}*/
		updated = 0;
		switch (iKey)
		{
			case LEFT:
				for (i = locX; i < locX + 4; i++)
				{
					for (n = locY + 3; n >= locY; n--)
					{
						if (Tetrino.newinBoard[n][i] > 0)
						{
							if (Tetrino.newinBoard[n][i - 1] < 0)
							{
								iChanging = 0;
								return;
							}
						}
					}
				}
				for (i = locX; i < locX + 4; i++)
				{
					for (n = locY + 3; n >= locY; n--)
					{
						if (Tetrino.newinBoard[n][i] <= 0)
							continue;
						Tetrino.newinBoard[n][i - 1] = Tetrino.newinBoard[n][i];
						Tetrino.newinBoard[n][i] = 0;
					}
				}
				locX--;
				break;
			case RIGHT:
				if (curTetrino == 0)
				{
					for (i = locX + 4; i >= locX; i--)
					{
						for (n = locY + 4; n >= locY; n--)
						{
							if (Tetrino.newinBoard[n][i] > 0)
							{
								if (Tetrino.newinBoard[n][i + 1] < 0)
								{
									iChanging = 0;
									return;
								}
							}
						}
					}
					for (i = locX + 4; i >= locX; i--)
					{
						for (n = locY + 4; n >= locY; n--)
						{
							if (Tetrino.newinBoard[n][i] <= 0)
								continue;
							Tetrino.newinBoard[n][i + 1] = Tetrino.newinBoard[n][i];
							Tetrino.newinBoard[n][i] = 0;
						}
					}
					locX++;
				}
				else
				{
					for (i = locX + 3; i >= locX; i--)
					{
						for (n = locY + 3; n >= locY; n--)
						{
							if (Tetrino.newinBoard[n][i] > 0)
							{
								if (Tetrino.newinBoard[n][i + 1] < 0)
								{
									iChanging = 0;
									return;
								}
							}
						}
					}
					for (i = locX + 3; i >= locX; i--)
					{
						for (n = locY + 3; n >= locY; n--)
						{
							if (Tetrino.newinBoard[n][i] <= 0)
								continue;
							Tetrino.newinBoard[n][i + 1] = Tetrino.newinBoard[n][i];
							Tetrino.newinBoard[n][i] = 0;
						}
					}
					locX++;
				}
				break;
			case 'x':
				if (iRotate == 3)
				{
					iRotate = 0;
				}
				else 
					iRotate++;
				Rotation();
				break;
		}
		updated = 1;
		iChanging = 0;
	}
}
void Tetris::Moving()
{
	int i, n;
	for (i = locX; i < locX + 4; i++)
	{
		for (n = locY + 3; n >= locY; n--)
		{
			if (Tetrino.newinBoard[n][i] > 0)
			{
				Tetrino.newinBoard[n + 1][i] = Tetrino.newinBoard[n][i];
				Tetrino.newinBoard[n][i] = 0;
			}
		}
	}
	updated = 1;
	locY++;
	iState = 1;
}
void Tetris::RandomTetrino()
{
	static vector<int> tetris(7);
	static int count = 0;
	int rands, i, n; // i for X, n for Y
	locX = 4;
	locY = 0;
	while (1)
	{
		rands = rand() % 7;
		if (tetris[rands] == 0)
		{
			tetris[rands] = -1;
			count++;
			break;
		}
		if (count == 7)
		{
			for (i = 0; i < 7; i++)
			{
				tetris[i] = 0;
			}
			count = 0;
			continue;
		}
	}
	for (i = 0; i < 4; i++)
	{
		for (n = 0; n < 4; n++)
		{
			Tetrino.newinBoard[n + locY][i + locX] = Tetrino.Tetris[rands][n][i];
		}
	}
	curTetrino = rands;
	iRotate = 0;
	iMoving = 1;
}
void Tetris::MakeStop(int cur)
{
	int i, n, iStartTick, m, l, keepgoing = 0;
	for (n = 20; n >= 1; n--)
	{
		for (i = 1; i < 11; i++)
		{
			if (Tetrino.newinBoard[n+1][i] < 0 && Tetrino.newinBoard[n][i] > 0)
			{
				if (locY <= 2)
					system("pause");
				iStartTick = (int)GetTickCount();
				while (true)
				{
					Input();
					for (m = locX; m < locX + 4; m++)
					{
						for (l = locY; l < locY + 4; l++)
						{
							if (l >= 21 && m >= 11)
								continue;
							if (Tetrino.newinBoard[l + 1][m] < 0 && Tetrino.newinBoard[l][m] > 0)
							{
								keepgoing = 1;
							}
						}
					}
					if (keepgoing == 0)
					{
						Moving();
					}
					keepgoing = 0;
					if (GetTickCount() - iStartTick > 500)
					{
						break;
					}
				}
				updated = 0;
				for (i = locX; i < locX + 4; i++)
				{
					for (n = locY + 3; n >= locY; n--)
					{
						if (n > 20)
							continue;
						if(Tetrino.newinBoard[n][i] > 0)
							Tetrino.newinBoard[n][i] = Tetrino.newinBoard[n][i] * (-1);
					}
				}
				updated = 1;
				iMoving = 0;
				return;
			}
		}
	}
}
void Tetris::frame()
{
	int i = 0, n, iStartTick;//
	iStartTick = (int)GetTickCount();
	while (true)
	{
		if(updated == 1)
		{
			for (n = 20; n >= 1; n--)
			{
				util.gotoxy(9, n +2);
				for (i = 1; i < 11; i++)
				{
					if (Tetrino.newinBoard[n][i] == 0)
						printf("  ");
					if (Tetrino.newinBoard[n][i] > 0)
					{
						COLOR(Tetrino.newinBoard[n][i]);
						printf("\u25A0");
					}
					else if (Tetrino.newinBoard[n][i] < 0 && Tetrino.newinBoard[n][i] != -99)
					{
						COLOR(Tetrino.newinBoard[n][i] * (-1));
						printf("\u25A0");
					}
				}
			}
			updated = 0;
		}
		if (GetTickCount() - iStartTick > 250)
		{
			iState = 0;
			iStartTick = (int)GetTickCount();
		}
		if(i == 100)
		{
			break;
		}
	}
}
[[noreturn]] void Tetris::G_Board()
{
	int i, n;//i for x, n for y
	for (n = 0; n < 30; n++)
	{
		for (i = 0; i < 20; i++)
		{
			if (Tetrino.TBoard[n][i] == 1)
				printf("\u25A0");
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	thread t1([&]() {frame(); });
	while (true)
	{
		Input();
		/*new tetrino*/
		if(iMoving == 0)
			RandomTetrino();
		//moving
		MakeStop(curTetrino);
		if (iMoving == 1 && iState == 0 && iChanging == 0)
			Moving();
		RemoveLine();
	}
}
void Tetris::Rotation()
{ 
	int i;
	switch (curTetrino)
	{
	case 0: // I
		if (iRotate % 2 == 0)
		{
			if (Tetrino.newinBoard[locY][locX + 1] < 0 || Tetrino.newinBoard[locY][locX + 2] < 0 || Tetrino.newinBoard[locY][locX + 3] < 0)
				break;
			Tetrino.newinBoard[locY][locX + 1] = 9;
			Tetrino.newinBoard[locY][locX + 2] = 9;
			Tetrino.newinBoard[locY][locX + 3] = 9;
			Tetrino.newinBoard[locY + 1][locX] = 0;
			Tetrino.newinBoard[locY + 2][locX] = 0;
			Tetrino.newinBoard[locY + 3][locX] = 0;
		}
		else if (iRotate % 2 == 1)
		{
			if (Tetrino.newinBoard[locY + 1][locX] < 0 || Tetrino.newinBoard[locY + 2][locX] < 0 || Tetrino.newinBoard[locY + 3][locX] < 0)
				break;
			Tetrino.newinBoard[locY][locX + 1] = 0;
			Tetrino.newinBoard[locY][locX + 2] = 0;
			Tetrino.newinBoard[locY][locX + 3] = 0;
			Tetrino.newinBoard[locY + 1][locX] = 9;
			Tetrino.newinBoard[locY + 2][locX] = 9;
			Tetrino.newinBoard[locY + 3][locX] = 9;
		}
		break;
	case 1: // o

		break;
	case 2: // t
		if (iRotate == 0)
		{
			if (Tetrino.newinBoard[locY + 1][locX + 2] < 0)
				break;
			Tetrino.newinBoard[locY + 2][locX + 1] = 0;
			Tetrino.newinBoard[locY + 1][locX + 2] = 5;
		}
		else if (iRotate == 1)
		{
			if (Tetrino.newinBoard[locY + 2][locX + 1] < 0)
				break;
			Tetrino.newinBoard[locY + 1][locX] = 0;
			Tetrino.newinBoard[locY + 2][locX + 1] = 5;
		}
		else if (iRotate == 2)
		{
			if (Tetrino.newinBoard[locY + 1][locX] < 0)
				break;
			Tetrino.newinBoard[locY][locX + 1] = 0;
			Tetrino.newinBoard[locY + 1][locX] = 5;
		}
		else if (iRotate == 3)
		{
			if (Tetrino.newinBoard[locY][locX + 1] < 0)
				break;
			Tetrino.newinBoard[locY + 1][locX + 2] = 0;
			Tetrino.newinBoard[locY][locX + 1] = 5;
		}
		break;
	case 3: // l
		if (iRotate == 0)
		{
			if (Tetrino.newinBoard[locY][locX] < 0 || Tetrino.newinBoard[locY + 1][locX] < 0 || Tetrino.newinBoard[locY + 1][locX + 2] < 0)				
				break;
			Tetrino.newinBoard[locY + 2][locX] = 0;
			Tetrino.newinBoard[locY + 2][locX + 1] = 0;
			Tetrino.newinBoard[locY][locX + 1] = 0;
			Tetrino.newinBoard[locY][locX] = 12;
			Tetrino.newinBoard[locY + 1][locX] = 12;
			Tetrino.newinBoard[locY + 1][locX + 2] = 12;
		}
		else if (iRotate == 1)
		{
			if (Tetrino.newinBoard[locY][locX + 1] < 0 || Tetrino.newinBoard[locY][locX + 2] < 0 || Tetrino.newinBoard[locY + 2][locX + 1] < 0)
				break;

			Tetrino.newinBoard[locY][locX] = 0;
			Tetrino.newinBoard[locY + 1][locX] = 0;
			Tetrino.newinBoard[locY + 1][locX + 2] = 0;
			Tetrino.newinBoard[locY][locX + 1] = 12;
			Tetrino.newinBoard[locY][locX + 2] = 12;
			Tetrino.newinBoard[locY + 2][locX + 1] = 12;
		}
		else if (iRotate == 2)
		{
			if (Tetrino.newinBoard[locY + 1][locX] < 0 || Tetrino.newinBoard[locY + 1][locX + 2] < 0 || Tetrino.newinBoard[locY + 2][locX + 2] < 0)
				break;

			Tetrino.newinBoard[locY][locX + 1] = 0;
			Tetrino.newinBoard[locY][locX + 2] = 0;
			Tetrino.newinBoard[locY + 2][locX + 1] = 0;
			Tetrino.newinBoard[locY + 1][locX] = 12;
			Tetrino.newinBoard[locY + 1][locX + 2] = 12;
			Tetrino.newinBoard[locY + 2][locX + 2] = 12;
		}
		else if (iRotate == 3)
		{
			if (Tetrino.newinBoard[locY + 2][locX] < 0 || Tetrino.newinBoard[locY + 2][locX + 1] < 0 || Tetrino.newinBoard[locY][locX + 1] < 0)
				break;

			Tetrino.newinBoard[locY + 1][locX] = 0;
			Tetrino.newinBoard[locY + 1][locX + 2] = 0;
			Tetrino.newinBoard[locY + 2][locX + 2] = 0;
			Tetrino.newinBoard[locY + 2][locX] = 12;
			Tetrino.newinBoard[locY + 2][locX + 1] = 12;
			Tetrino.newinBoard[locY][locX + 1] = 12;
		}
		break;
	case 4: // j
		if (iRotate == 0)
		{
			if (Tetrino.newinBoard[locY][locX] < 0 || Tetrino.newinBoard[locY + 1][locX] < 0 || Tetrino.newinBoard[locY + 1][locX + 2] < 0)
				break;

			Tetrino.newinBoard[locY + 2][locX] = 0;
			Tetrino.newinBoard[locY + 2][locX + 1] = 0;
			Tetrino.newinBoard[locY][locX + 1] = 0;
			Tetrino.newinBoard[locY][locX] = 1;
			Tetrino.newinBoard[locY + 1][locX] = 1;
			Tetrino.newinBoard[locY + 1][locX + 2] = 1;
		}
		else if (iRotate == 1)
		{
			if (Tetrino.newinBoard[locY][locX + 1] < 0 || Tetrino.newinBoard[locY][locX + 2] < 0 || Tetrino.newinBoard[locY + 2][locX + 1] < 0)
				break;

			Tetrino.newinBoard[locY][locX] = 0;
			Tetrino.newinBoard[locY +1][locX] = 0;
			Tetrino.newinBoard[locY + 1][locX + 2] = 0;
			Tetrino.newinBoard[locY][locX + 1] = 1;
			Tetrino.newinBoard[locY][locX + 2] = 1;
			Tetrino.newinBoard[locY + 2][locX + 1] = 1;
		}
		else if (iRotate == 2)
		{
			if (Tetrino.newinBoard[locY + 1][locX] < 0 || Tetrino.newinBoard[locY + 1][locX + 2] < 0 || Tetrino.newinBoard[locY + 2][locX + 2] < 0)
				break;

			Tetrino.newinBoard[locY][locX + 1] = 0;
			Tetrino.newinBoard[locY][locX + 2] = 0;
			Tetrino.newinBoard[locY + 2][locX + 1] = 0;
			Tetrino.newinBoard[locY + 1][locX] = 1;
			Tetrino.newinBoard[locY + 1][locX + 2] = 1;
			Tetrino.newinBoard[locY + 2][locX + 2] = 1;
		}
		else if (iRotate == 3)
		{
			if (Tetrino.newinBoard[locY + 2][locX] < 0 || Tetrino.newinBoard[locY + 2][locX + 1] < 0 || Tetrino.newinBoard[locY][locX + 1] < 0)
				break;

			Tetrino.newinBoard[locY + 1][locX] = 0;
			Tetrino.newinBoard[locY + 1][locX + 2] = 0;
			Tetrino.newinBoard[locY + 2][locX + 2] = 0;
			Tetrino.newinBoard[locY + 2][locX] = 1;
			Tetrino.newinBoard[locY + 2][locX + 1] = 1;
			Tetrino.newinBoard[locY][locX + 1] = 1;
		}
		break;
	case 5: // s
		if (iRotate % 2 == 0)
		{
			if (Tetrino.newinBoard[locY][locX + 1] < 0 || Tetrino.newinBoard[locY][locX + 2] < 0)
				break;

			Tetrino.newinBoard[locY][locX + 1] = 10;
			Tetrino.newinBoard[locY][locX + 2] = 10;
			Tetrino.newinBoard[locY][locX] = 0;
			Tetrino.newinBoard[locY + 2][locX + 1] = 0;
		}
		else if (iRotate % 2 == 1)
		{
			if (Tetrino.newinBoard[locY][locX] < 0 || Tetrino.newinBoard[locY + 2][locX + 1] < 0)
				break;

			Tetrino.newinBoard[locY][locX + 1] = 0;
			Tetrino.newinBoard[locY][locX + 2] = 0;
			Tetrino.newinBoard[locY][locX] = 10;
			Tetrino.newinBoard[locY + 2][locX + 1] = 10;
		}
		break;
	case 6: // z
		if (iRotate % 2 == 0)
		{
			if (Tetrino.newinBoard[locY][locX] < 0 || Tetrino.newinBoard[locY + 1][locX + 2] < 0)
				break;

			Tetrino.newinBoard[locY][locX] = 4;
			Tetrino.newinBoard[locY + 1][locX + 2] = 4;
			Tetrino.newinBoard[locY + 1][locX] = 0;
			Tetrino.newinBoard[locY + 2][locX] = 0;
		}
		else if (iRotate % 2 == 1)
		{
			if (Tetrino.newinBoard[locY + 1][locX] < 0 || Tetrino.newinBoard[locY + 2][locX] < 0)
				break;

			Tetrino.newinBoard[locY][locX] = 0;
			Tetrino.newinBoard[locY + 1][locX + 2] = 0;
			Tetrino.newinBoard[locY + 1][locX] = 4;
			Tetrino.newinBoard[locY + 2][locX] = 4;
		}
		break;
	}
}
void Tetris::RemoveLine()
{
	int i, n, count = 0, j, m;
	for (n = 20; n >= 1; n--)
	{
		for (i = 1; i < 11; i++)
		{
			if (Tetrino.newinBoard[n][i] < 0)
			{
				count++;
			}
		}
		if (count == 10)
		{
			for (j = 1; j < 11; j++)
			{
				Tetrino.newinBoard[n][j] = 0;
			}
			for(m = n - 1; m >= 1; m--)
			{
				for (j = 1; j < 11; j++)
				{
					Tetrino.newinBoard[m + 1][j] = Tetrino.newinBoard[m][j];
				}
			}
		}
		else
			count = 0;
	}

}
