#ifndef __HEADER_TETRIS_
#define __HEADER_TETRIS_

#include <iostream>
#include <cstdio>
#include <windows.h>
#include "Utility.h"
#include <conio.h>
#include <ctime>
#include <vector>
#include <thread>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define ENTER 13

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define L_BLUE 9
#define L_GREEN 10
#define L_AQUA 11
#define L_RED 12
#define L_PINK 13
#define L_YELLOW 14
#define B_WHITE 15


typedef struct _tetrino//0 for I, 1 for O, 2 for T, 3 for L, 4 for J, 5 for S, 6 for Z
{
	int Tetris[7][4][4] = {
			/*i block & L_blue 9*/
			9, 9, 9, 9,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			/*o block & yellow 14*/
			14,14, 0, 0,
			14,14, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			/*t block & purple 5*/
			0, 5, 0, 0,
			5, 5, 5, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			/*l block & orenge 12*/
			0, 0,12, 0,
			12,12,12, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			/*j block & blue 1*/
			1, 0, 0, 0,
			1, 1, 1, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			/*s block & L_green 10*/
			0,10,10, 0,
			10,10, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			/*z block & red 4*/
			4, 4, 0, 0,
			0, 4, 4, 0,
			0, 0, 0, 0,
			0, 0, 0, 0 };
	int TBoard[30][20] = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
			{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
			{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};

	int newinBoard[22][12] = { 0 }; //22*12
}TetrinoDeclair;

void init(); //Initializing game in Tetris_game.cpp
class Tetris //Define in in Tetris_game.cpp
{
private:
	int current{}, iKeepGoing = 0, iMoving = 0, iRotate = 0, curTetrino = -1, iRotating = 0, locX = 0, locY = 0, iChanging = 0, iStopping = 0, updated = 0;
	bool bGameIsEnded = false;
public:
	void frame(); // update game screen
	void MakeStop(int i); //Stop Tetrino
	void Input(); //Get user's input
	void Moving(); // move tetrino by y+1
	void RandomTetrino(); // Make 1 random tetrino
	void Rotation(); // Rotate tetrino
	void RemoveLine(); // RemoveLine

	[[noreturn]] void G_Board(); //Main GameBoard
};
#endif