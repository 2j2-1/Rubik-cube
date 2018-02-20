#include "stdafx.h"
#include "Movement.h"
#include "Utils.h"
#include "Validation.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include <windows.h>
const int cubeFace[][4] = { { 1,4,3,2 },
{ 0,2,5,4 },
{ 0,3,5,1 },
{ 0,4,5,2 },
{ 0,1,5,3 },
{ 1,2,3,4 } };
const int cubeEdges[][12] = { { 0,1,2,0,1,2,0,1,2,0,1,2 },
{ 0,3,6,0,3,6,0,3,6,8,5,2 },
{ 6,7,8,0,3,6,2,1,0,8,5,2 },
{ 2,5,8,6,3,0,2,5,8,2,5,8 },
{ 0,1,2,6,3,0,8,7,6,2,5,8 },
{ 6,7,8,6,7,8,6,7,8,6,7,8 } };
const int frontFace[][9] = { { 2,5,8,1,4,7,0,3,6 },
{ 8,7,6,5,4,3,2,1,0 },
{ 6,3,0,7,4,1,8,5,2 } };
std::string moves[14] = { "u","l","f","r","b","d","U","L","F","R","B","D" };
std::string Tperm[15] = { "r","u","r'","u'","r'","f","r","r","u'","r'","u'","r","u","r'","f'"};
std::string Yperm[17] = {"f","r","u'","r'","u'","r","u","r'","f'","r","u","r'","u'","r'","f","r","f'"};
int sleep = 25;

void front_face(int cube[][9],int face, int direction) {
	int temp[9];
	for (int i = 0; i < 9; i++) {
		temp[i] = cube[face][i];
	}
	for (int i = 0; i < 9; i++) {
		cube[face][i] = temp[frontFace[direction - 1][i]];
	}
}
void move(int cube[][9], int face, int direction) {
	front_face(cube, face, direction / 3);
	int temp[12];

	for (int i = 0; i < 12; i++) {
		temp[i] = cube[cubeFace[face][i / 3]][cubeEdges[face][i]];
	}
	for (int i = 0; i < 12; i++) {
		cube[cubeFace[face][i / 3]][cubeEdges[face][i]] = temp[(i + direction) % 12];
	}
	print_cube(cube);
	Sleep(sleep);
}
void text_to_move(int cube[][9], std::string c) {
	int found = find(moves, 6, c[0]);
	if (found != -1) {
		if (c.length() == 1)
			move(cube, found, 9);
		else if (c.length() == 2 && c[1] == '2') {
			move(cube, found, 6);
		}
		else if (c.length() == 2 && c[1] == '\'') {
			move(cube, found, 3);
		}
	}
}
void text_to_move(int cube[][9], char c) {
	int found = find(moves, 6, c);
	if (found != -1) {
		move(cube, found, 9);
	}
}
void scramble(int cube[][9], int amount) {
	int turnFace;
	for (int i = 0; i < amount; i++) {
		turnFace = rand() % sizeof(moves) / sizeof(std::string);
		text_to_move(cube, moves[turnFace]);
	}
}
char * setUp[54] = { "", "bbdll","rrdrr","", "","","ffdrr","ffdddll","","","lfffdddll","f","llfffdddll","","fffdddll","dfffr","lllfffdddll","fffdrr","ffr","ffflll","fr","lll","","fflll","fffr","flll","r","ffdr","","rdddr","fdddll","","bbbdll","rrrdddr","dddflll","dddr","rrr","bl","","bbl","","l","ddfffr","bbbl","dfffdrr","ddrr","dddll","drr","ll","","ddll","dddrr","dll","rr" };

void swapEdges(int cube[][9]) {
	char * c = setUp[cube[0][5] - 1];
	string_to_move(cube, c);
	for (int i = 0; i < 15; i++)
	{
		text_to_move(cube, Tperm[i]);
	}
	reverse_string_to_move(cube, c);
}
void swapEdges(int cube[][9],int set) {
	char * c = setUp[set];
	string_to_move(cube, c);
	for (int i = 0; i < 15; i++)
	{
		text_to_move(cube, Tperm[i]);
	}
	reverse_string_to_move(cube, c);
}
void string_to_move(int cube[][9], const char* c) {
	for (int i = 0; i < strlen(c); i++)
	{
		text_to_move(cube, c[i]);
	}
}
void reverse_string_to_move(int cube[][9], const char* c) {
	for (int i = strlen(c) -1; i >= 0; i--)
	{
		text_to_move(cube, c[i]);
		text_to_move(cube, c[i]);
		text_to_move(cube, c[i]);
	}
}
void out_of_place(int cube[][9]) {
	for (int i = 1; i < 54; i++)
	{
		if (cube[i / 9][i % 9] != i + 1 && (i % 9) % 2 == 1 && cube[i / 9][i % 9] != 29 && cube[i / 9][i % 9] != 4 && cube[i / 9][i % 9] != 6) {
			//std::cout << cube[i / 9][i % 9] << "," << i + 1 << std::endl;
			swapEdges(cube, i);
			break;
		}
	}
}
void out_of_place_corners(int cube[][9]) {
	for (int i = 1; i < 54; i++)
	{
		if (cube[i / 9][i % 9] != i + 1 && (i % 9) % 2 == 0 && cube[i / 9][i % 9] != 1 && cube[i / 9][i % 9] != 9 && cube[i / 9][i % 9] != 10 && cube[i / 9][i % 9] != 28 && cube[i / 9][i % 9] != 21 && cube[i / 9][i % 9] != 39) {
			//std::cout << cube[i / 9][i % 9] << "," << i + 1 << std::endl;
			swapCorners(cube, i);
			break;
		}
	}
}
void swapCorners(int cube[][9]) {
	char * c = setUp[cube[0][0] - 1];
	string_to_move(cube, c);
	for (int i = 0; i < 17; i++)
	{
		text_to_move(cube, Yperm[i]);
	}
	reverse_string_to_move(cube, c);
}
void swapCorners(int cube[][9],int set) {
	char * c = setUp[set];
	string_to_move(cube, c);
	for (int i = 0; i < 17; i++)
	{
		text_to_move(cube, Yperm[i]);
	}
	reverse_string_to_move(cube, c);
}
void solve(cGame game, int cube[][9]) {
	do {
		do {
			if (cube[0][5] != 29) {
				swapEdges(cube);
			}
			else {
				out_of_place(cube);
			}
		} while (cube[0][5] != 6);
		out_of_place(cube);
		
	} while (!solvedEdges(cube));
	do {
		do {
			if (cube[0][0] == 10 && cube[0][8] == 21) {
				string_to_move(cube, "urrrfrbbbrrrfffrburrrfrrrbbrfffrrrbbrruu");
			}
			else if ((cube[0][0] == 39 && cube[0][8] == 28)) {
				string_to_move(cube, "uuurrrfrbbbrrrfffrburbbbrffrrrbrffrr");
			}
			else if (cube[0][0] != 10 && cube[0][0] != 39) {
				swapCorners(cube);
			}
			else {
				out_of_place_corners(cube);
			}

		} while (cube[0][0] != 1);
		out_of_place_corners(cube);

	} while (!solvedCorners(cube));
}