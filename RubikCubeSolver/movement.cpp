#include "stdafx.h"
#include "Movement.h"
#include "Utils.h"
#include "Validation.h"
#include <string>
#include <iostream>

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
std::string moves[14] = { "u","l","f","r","b","d","u'","l'","f'","r'","b'","d'" };
std::string Tperm[15] = { "r","u","r'","u'","r'","f","r","r","u'","r'","u'","r","u","r'","f'"};
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
char * edgeSetUp[54] = { 
"", 
"",
"",
"",
"",
"",
"",
"",
"",
"",
"", 
"",
"",
"",
"",
"",
"",
"",
"",
"",
"", 
"",
"",
"",
"",
"",
"",
"",
"",
"",
"", 
"",
"",
"",
"",
"",
"",
"",
"",
"",
"", 
"",
"",
"",
"",
"",
"",
"",
"",
"",
"", 
"",
"",
""};
void swapEdges(int cube[][9], const char *c) {
	string_to_move(cube, c);
	for (int i = 0; i < 15; i++)
	{
		text_to_move(cube,Tperm[i]);
	}
	reverse_string_to_move(cube, c);
}

void string_to_move(int cube[][9], const char* c) {
	for (int i = 0; i < sizeof(c) / sizeof(const char); i++)
	{
		text_to_move(cube, c[i]);
	}
}
void reverse_string_to_move(int cube[][9], const char* c) {
	for (int i = 0; i < sizeof(c) / sizeof(const char); i++)
	{
		text_to_move(cube, c[i]);
		text_to_move(cube, c[i]);
		text_to_move(cube, c[i]);
	}
}