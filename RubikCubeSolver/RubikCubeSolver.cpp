#include "stdafx.h"
#include <iostream>
#include <time.h>
#include "Movement.h"
#include "Utils.h"
#include "Validation.h"
#include "cGame.h"

int cube[][9] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
{ 10,11,12,13,14,15,16,17,18 },
{ 19,20,21,22,23,24,25,26,27 },
{ 28,29,30,31,32,33,34,35,36 },
{ 37,38,39,40,41,42,43,44,45 },
{ 46,47,48,49,50,51,52,53,54 } };
cGame game;
int locations[][6] = { { 3,0 },{ 0,3 },{ 3,3 },{ 6,3 },{ 9,3 },{ 3,6 } };
char symbols[] = { '0','1','2','3','4','5' };
// fix this to display at any size
int cubeX = 9;
int cubeY = 4;
void print_cube(int cube[][9]) {
	for (int i = 0; i < 54; i++)
	{
		for (int j = 0; j < cubeX*cubeY; j++)
		{
			game.draw_pixel(((i % 3) * (cubeX+1)) + j % cubeX + locations[i / 9][0]*(cubeX+1),
						   (((i % 9) / 3) * (cubeY+1)) + j / cubeX + locations[i / 9][1]*(cubeY+1),
						   symbols[(cube[i / 9][i % 9] - 1) / 9]);
		}
	}
	game.draw();
}

int main() {
	
	game.setup();
	game.blank_screen();
	srand(time(NULL));
	scramble(cube, 40);
	Sleep(1000);
	print_cube(cube);
	solve(cube);
	print_cube(cube);
	while (true){}
}