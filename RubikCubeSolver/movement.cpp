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
std::string moves[][14] = { { "u","l","f","r","b","d","u'","l'","f'","r'","b'","d'","u2","d2" },
{ "l","f","r","b","l'","f'","r'","b'","u2","d2" } };

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
void text_to_move(int cube[][9], std::string c, int stage) {
	int found = find(moves[stage], 6, c[0]);
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
void scramble(int cube[][9], int amount) {
	int turnFace;
	for (int i = 0; i < amount; i++) {
		turnFace = rand() % sizeof(moves) / sizeof(std::string);
		text_to_move(cube, moves[0][turnFace], 0);
	}
}
bool backtrack(int cube[][9], int depth, int stage, std::string history[],int depthLimit) {
	depth++; 

	int temp;
	if (depth > depthLimit) {
		depth--;
		return false;
	}
	if (stages(cube,stage)) {
		std::cout << "found at depth: " << depth << std::endl;
		return true;
	}
	for (int i = 0; i < sizeof(moves[stage]) / sizeof(std::string); i++) {
		if (depth > 2) {
			if (history[depth - 3] == history[depth - 3] &&
				history[depth - 3] == history[depth - 1] && history[depth - 3] == moves[stage][i]) {
				return false;
			}
			/*else if (history[depth - 1] == moves[moveSet][(i + 6) % 12]) {
			continue;
			}*/
		}
		history[depth] = moves[stage][i];
		//to_file(history);
		text_to_move(cube, moves[stage][i], stage);
		if (backtrack(cube,depth, stage, history,depthLimit)) {
			return true;
		}
		text_to_move(cube, moves[stage][(i + 6) % 12], stage);
		history[depth] = "-1";
	}
	depth--;
	return false;

}
