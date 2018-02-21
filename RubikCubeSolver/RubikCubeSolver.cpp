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
int locations[][6] = { { 20,0 },{ 0,12 },{ 20,12 },{ 40,12 },{ 60,12 },{ 20,24 } };
char symbols[] = { '0','1','2','3','4','5' };

void print_cube(int cube[][9]) {
	for (int i = 0; i < 54; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			game.draw_pixel(((i % 3) * 6) + j % 5 + locations[i / 9][0], (((i % 9) / 3) * 4) + j / 5 + locations[i / 9][1], symbols[(cube[i / 9][i % 9] - 1) / 9]);
		}
	}
	game.draw();
}

int main() {
	
	game.setup();
	game.blank_screen();
	srand(time(NULL));
	scramble(cube, 40);
	print_cube(cube);
	solve(cube);
	print_cube(cube);
	while (true){}
}