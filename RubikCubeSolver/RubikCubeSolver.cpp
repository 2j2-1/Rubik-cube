#include "stdafx.h"
#include <iostream>
#include <time.h>
#include "Movement.h"
#include "cGame.h"
#include <string>
#include <fstream>

//CONFIG
int boxSize = 20;
int cubeX = 9;
int cubeY = 4;

int cube[][9] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
				{ 10,11,12,13,14,15,16,17,18 },
				{ 19,20,21,22,23,24,25,26,27 },
				{ 28,29,30,31,32,33,34,35,36 },
				{ 37,38,39,40,41,42,43,44,45 },
				{ 46,47,48,49,50,51,52,53,54 } };
cGame game;
int locations[][6] = { { 3,0 },{ 0,3 },{ 3,3 },{ 6,3 },{ 9,3 },{ 3,6 } };
char symbols[] = { '!','"','#','$','%','&' };
int amountOfMoves = 1;


int colors_to_cube(std::string cubeColors) {
	int pairs[][3] = {
		{ 1,10,39 },{ 2,38 },{ 3,37,30 },{ 4,11 },{},{ 6,29 },{ 7,19,12 },{ 8,20 },{ 9,28,21 },
		{ 10,39,1 },{ 11,4 },{ 12,7,19 },{ 13,42 },{},{ 15,22 },{ 16,52,45 },{ 17,49 },{ 18,25,46 },
		{ 19,12,7 },{ 20,8 },{ 21,9,28 },{ 22,15 },{},{ 24,31 },{ 25,46,18 },{ 26,47 },{ 27,34,48 },
		{ 28,21,9 },{ 29,6 },{ 30,3,37 },{ 31,24 },{},{ 33,40 },{ 34,48,27 },{ 35,51 },{ 36,43,54 },
		{ 37,30,3 },{ 38,2 },{ 39,1,10 },{ 40,33 },{},{ 42,13 },{ 43,54,36 },{ 44,53 },{ 45,16,52 },
		{ 46,18,25 },{ 47,26 },{ 48,27,34 },{ 49,17 },{},{ 51,35 },{ 52,45,16 },{ 53,44 },{ 54,36,43 },
	};
	int realtions[][6] = { 
	{ 0,   4,  8,  6,  2,  0 },
	{ 11,  0, 15,  0, 13, 17 },
	{ 20, 22,  8, 24,  8, 26 },
	{ 29,  0, 31, 35, 33, 35 },
	{ 38, 42,  0, 40,  0, 44 },
	{ 51, 49, 47, 51, 53,  0 } };
	int tripleRealtions[][6] = {
		{ 0,1,7,9,3,0 },
		{12,0,18,0,10,16},
		{21,19,0,27,0,25},
		{30,0,28,0,36,34},
		{39,45,0,37,0,43},
		{0,46,48,54,52,0},
	};
	char * aColors = "ybrgow";
	int colors[54];

	for (int i = 0; i < 54; i++)
		for (int j = 0; j < 6; j++)
			if (cubeColors[i] == aColors[j])
				colors[i] = j;


	for (int i = 0; i < 54; i++) {
		if (i % 9 == 4)
			cube[i / 9][i % 9] = i + 1;
		else if ((i % 9) % 2 == 1)
			cube[i / 9][i % 9] = realtions[colors[pairs[i][0] - 1]][colors[pairs[i][1] - 1]];
		else
			cube[i / 9][i % 9] = tripleRealtions[colors[pairs[i][0] - 1]][colors[pairs[i][1] - 1]];
	}

	return 0;
}

void updateScreen() {
	game.print("Stats", game.screenWidth - boxSize, 0);
	game.print("Moves:", game.screenWidth - boxSize, 2);
	std::string moveString = std::to_string(amountOfMoves);
	game.draw_pixel(game.screenWidth - 2, 2, '0');
	game.print(moveString, game.screenWidth - moveString.length(), 2);

}

void print_cube() {
	for (int i = 0; i < 54; i++)
		for (int j = 0; j < cubeX*cubeY; j++)
			if (cube[i / 9][i % 9] != 0)
				game.draw_pixel(((i % 3) * (cubeX + 1)) + j % cubeX + locations[i / 9][0] * (cubeX + 1),
				(((i % 9) / 3) * (cubeY + 1)) + j / cubeX + locations[i / 9][1] * (cubeY + 1),
					symbols[(cube[i / 9][i % 9] - 1) / 9]);
	
	updateScreen();
	amountOfMoves++;
	game.draw(cubeX);
}

int main() {
	int choice;
	std::cout << "1.Video input\n2.Scramble\n3.Exsiting file\n";
	std::cin >> choice;
	if (choice == 1)
		system("python video_to_colors.py");
	game.setup();
	game.blank_screen();
	if (choice != 2) {
		std::string line;
		std::ifstream myfile("Colors.txt");
		char * faces = new char[55];
		myfile >> line;
		myfile.close();
		colors_to_cube(line);
	}
	
	srand(1);
	amountOfMoves = 0;
	if (choice == 2)
		scramble(cube, 40);
	print_cube();
	Sleep(5000);
	solve(cube);
	Sleep(1000);
	while (true) {}
}