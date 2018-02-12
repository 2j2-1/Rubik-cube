#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <array>
#include <string>
#include <time.h>
#include <iterator>
#include <algorithm>
#include <fstream>

int cube[][9] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
{ 10,11,12,13,14,15,16,17,18 },
{ 19,20,21,22,23,24,25,26,27 },
{ 28,29,30,31,32,33,34,35,36 },
{ 37,38,39,40,41,42,43,44,45 },
{ 46,47,48,49,50,51,52,53,54 } };
int solvedCube[][9] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
{ 10,11,12,13,14,15,16,17,18 },
{ 19,20,21,22,23,24,25,26,27 },
{ 28,29,30,31,32,33,34,35,36 },
{ 37,38,39,40,41,42,43,44,45 },
{ 46,47,48,49,50,51,52,53,54 } };
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

std::string moves[][12] = { {"u","l","f","r","b","d","u'","l'","f'","r'","b'","d'"},
							{ "u2","l","f","r","b","d2","l'","f'","r'","b'"} };
std::string face;
int depthLimit = 6;

int g0[][4] = { { 2,8,47,53 },{ 4,6,49,51 } };
int g1[][4] = { { 1,9,46,54 },{ 3,7,48,52 } };

// utils
void print_cube() {
	for (int j = 0; j < 3; j++) {
		std::cout << "         ";
		for (int i = 0; i < 3; i++) {
			if (cube[0][j * 3 + i] < 10)
				std::cout << " ";
			std::cout << cube[0][j * 3 + i] << " ";
		}
		std::cout << std::endl;
	}

	for (int j = 1; j < 4; j++) {
		for (int i = 0; i < 12; i++) {
			if (cube[(i / 3) + 1][(i % 3) + ((j - 1) * 3)] < 10)
				std::cout << " ";
			std::cout << cube[(i / 3) + 1][(i % 3) + ((j - 1) * 3)] << " ";
		}
		std::cout << std::endl;
	}

	for (int j = 0; j < 3; j++) {
		std::cout << "         ";
		for (int i = 0; i < 3; i++) {
			if (cube[5][j * 3 + i] < 10)
				std::cout << " ";
			std::cout << cube[5][j * 3 + i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
int find(std::string c[], int length, char find) {
	for (int i = 0; i < length; i++)
		if (find == c[i][0])
			return i;
	return -1;
}
bool compare(int face[], int solved[]) {
	for (int i = 0; i < sizeof(face) / sizeof(int); i++)
		if (face[i] != solved[i])
			return false;
	return true;
}
bool in(int values[], int find) {
	for (int i = 0; i < sizeof(values); i++)
		if (values[i] == find)
			return true;
	return false;
}

void to_file(std::string history[]) {
	std::ofstream myfile;
	myfile.open("example.txt", std::ios_base::app);
	for (int i = 0; i < 20; i++)
	{
		if (history[i]!="-1")
			myfile << history[i]<< ",";
	}
	myfile << std::endl;
	myfile.close();
}
//Movement
void front_face(int face,int direction) {
	int temp[9];
	for (int i = 0; i < 9; i++) {
		temp[i] = cube[face][i];
	}
	for (int i = 0; i < 9; i++) {
		cube[face][i] = temp[frontFace[direction-1][i]];
	}
}
void move(int face,int direction) {
	front_face(face,direction/3);
	int temp[12];

	for (int i = 0; i < 12; i++) {
		temp[i] = cube[cubeFace[face][i / 3]][cubeEdges[face][i]];
	}
	for (int i = 0; i < 12; i++) {
		cube[cubeFace[face][i / 3]][cubeEdges[face][i]] = temp[(i + direction) % 12];
	}
}
void text_to_move(std::string c,int stage) {
	int found = find(moves[stage], 6, c[0]);
	if (found != -1) {
		if (c.length() == 1)
			move(found,9);
		else if (c.length() == 2 && c[1] == '2') {
			move(found,6);
		}
		else if (c.length() == 2 && c[1] == '\'') {
			move(found,3);
		}
	}
}
void scramble(int amount) {
	int turnFace;
	for (int i = 0; i < amount; i++) {
		turnFace = rand() % sizeof(moves) / sizeof(std::string);
		text_to_move(moves[0][turnFace],0);
	}
}

//int countEdge() {
//	for (int i = 0; i < 8; i++)
//	{
//		// count good edges
//	}
//}
//Cube Checking

bool checkEdges() {
	return (in(g0[0], cube[0][1]) && in(g0[0], cube[0][7]) && in(g0[0], cube[5][1]) && in(g0[0], cube[5][7]) &&
		in(g0[1], cube[0][3]) && in(g0[1], cube[0][5]) && in(g0[1], cube[5][3]) && in(g0[1], cube[5][5]));
}
bool checkCorners() {
	return (
		in(g1[0], cube[0][0]) &&
		in(g1[0], cube[0][8]) &&
		in(g1[0], cube[5][0]) &&
		in(g1[0], cube[5][8]) &&

		in(g1[1], cube[0][2]) &&
		in(g1[1], cube[0][6]) &&
		in(g1[1], cube[5][2]) &&
		in(g1[1], cube[5][6])
		);
}
bool stages(int stage) {
	switch (stage)
	{
	case 0:

		return checkEdges();
	case 1:
		return (checkEdges() && checkCorners());
	}
}
//add history function 
bool backtrack(int depth, int stage, std::string history[]) {
	depth++;

	int temp;
	if (depth > depthLimit) {
		depth--;
		return false;
	}
	if (stages(stage)) {
		std::cout << "found at depth: " << depth << std::endl;
		return true;
	}
	for (int i = 0; i < sizeof(moves) / sizeof(std::string); i++) {
		history[depth] = moves[stage][i];
		to_file(history);
		text_to_move(moves[stage][i],stage);
		if (backtrack(depth, stage, history)) {
			return true;
		}
		text_to_move(moves[stage][(i + 6) % 12],stage);
		history[depth] = "-1";
	}
	depth--;
	return false;

}

int main() {
	int stage = 0;
	int stageLength = 1;
	std::string history[20] = { "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1" };
	srand(1);
	print_cube();

	/*while (true)
	{
		std::cin >> face;
		text_to_move(face,stage);
		std::cout << stages(0) << std::endl;
		print_cube();
	}*/

	scramble(40);
	print_cube();
	depthLimit--;
	do
	{
		do {
			std::cout << "Depth Limit: " << ++depthLimit << std::endl;
		} while (!backtrack(0, stage, history));

		depthLimit--;
		std::cout << "Stage: " << ++stage << std::endl;
		print_cube();
	} while (stage < stageLength);
	std::cout << "Finished" << std::endl;
	std::cin.get();
}

