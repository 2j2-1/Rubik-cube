#include "stdafx.h"
#include "Movement.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include <windows.h>
#include <cctype>
#include <clocale>
//Cube face stores all the edges around the faced being moved and to where they are going
const int cubeFace[][4] = { { 1,4,3,2 },
{ 0,2,5,4 },
{ 0,3,5,1 },
{ 0,4,5,2 },
{ 0,1,5,3 },
{ 1,2,3,4 } };
//cube edges stores which pieces will be saved and where they will be moved to 
const int cubeEdges[][12] = { { 0,1,2,0,1,2,0,1,2,0,1,2 },
{ 0,3,6,0,3,6,0,3,6,8,5,2 },
{ 6,7,8,0,3,6,2,1,0,8,5,2 },
{ 2,5,8,6,3,0,2,5,8,2,5,8 },
{ 0,1,2,6,3,0,8,7,6,2,5,8 },
{ 6,7,8,6,7,8,6,7,8,6,7,8 } };
//Stores the front face and where it will be placed after the move
const int frontFace[][9] = { { 2,5,8,1,4,7,0,3,6 },
{ 8,7,6,5,4,3,2,1,0 },
{ 6,3,0,7,4,1,8,5,2 } };
//Setup move is used by the blind algorithm this uses a set of moves to put the piece desired in the correct place to be transtioned
char * setUp[54] = { "", "bbdll","rrdrr","", "","","ffdrr","ffDll","","","lFDll","f","llFDll","","FDll","dFr","LFDll","Fdrr","ffr","FL","fr","L","","ffL","Fr","fL","r","ffdr","","rDr","fDll","","Bdll","RDr","DfL","Dr","R","bl","","bbl","","l","ddFr","Bl","dFdrr","ddrr","Dll","drr","ll","","ddll","Drr","dll","rr" };
//This is all possible moves avalible uppercase denotes a inverse move
char * moves = { "ulfrbdULFRBD" };
//Tperm is a algorithm that swaps two edges
char * Tperm = { "ruRURfrrURUruRF"};
//Yperm swaps two corners
char * Yperm = {"frURUruRFruRURfrF"};
int sleep = 0;


bool solved(int cube[][9], int stage) {
	//checks whole cube if anypiece is out of piece return false
	for (int i = 1; i < 54; i++)
		if (cube[i / 9][i % 9] != i + 1 && (i % 9) % 2 == stage)
			return false;
	return true;
}

void front_face(int cube[][9],int face, int direction) {
	//Front face takes the face to be moved and the direction indexs frontFace for which direction to be moved this can be an normal,inverse,or double
	int temp[9];
	for (int i = 0; i < 9; i++) {
		temp[i] = cube[face][i];
	}
	for (int i = 0; i < 9; i++) {
		cube[face][i] = temp[frontFace[direction - 1][i]];
	}
}

void move(int cube[][9], int face, int direction) {
	//Cube edges moves all the adjacent faces around in  the direction needed
	front_face(cube, face, direction / 3);
	int temp[12];
	
	for (int i = 0; i < 12; i++) {
		temp[i] = cube[cubeFace[face][i / 3]][cubeEdges[face][i]];
	}
	for (int i = 0; i < 12; i++) {
		cube[cubeFace[face][i / 3]][cubeEdges[face][i]] = temp[(i + direction) % 12];
	}
	print_cube();
	Sleep(sleep);
}

void text_to_move(int cube[][9], char c) {
	//Text to moves searches an array of moves to turn a char input to a instuction the program can use
	int found;
	for (int i = 0; i < 12; i++)
		if (c == moves[i])
			found = i%6;
	if (found != -1) {
		if ((int)c>96)
			move(cube, found, 9);
		else
			move(cube, found, 3);
	}
}

void scramble(int cube[][9], int amount) {
	for (int i = 0; i < amount; i++) {
		text_to_move(cube, moves[rand() % 12]);
	}
}

void swapEdges(int cube[][9],int set) {
	//swap edges can either recieve an index to a set up or uses the blind aglorthims technique by find the piece currently in location [0][5]
	//this setup move is performed followed by a Tperm followed by a reverse of the setup moves
	if (set==-1)
		set = cube[0][5] - 1;
	char * c = setUp[set];
	string_to_move(cube, c);
	string_to_move(cube, Tperm);
	reverse_string_to_move(cube, c);
}
void swapCorners(int cube[][9], int set) {
	//this is the same as swap edges but works for corners
	if (set == -1)
		set = cube[0][0] - 1;
	char * c = setUp[set];
	string_to_move(cube, c);
	string_to_move(cube, Yperm);
	reverse_string_to_move(cube, c);
}
void string_to_move(int cube[][9], const char* c) {
	for (int i = 0; i < strlen(c); i++)
	{
		text_to_move(cube, c[i]);
	}
}
void reverse_string_to_move(int cube[][9], const char* c) {
	//This run the text to move using a one line if stament that turns it to uppercase if it was lower or vice versa
	for (int i = strlen(c) -1; i >= 0; i--)
		text_to_move(cube, (c[i] > 96)? c[i] - 32 : c[i] + 32);
}
void out_of_place(int cube[][9]) {
	//Out of place is used a sometime the program can get stuck in a loop this will get the proram out the loop by finding a piece and putting that 
	//in the desired placed that will not cause the loop
	for (int i = 1; i < 54; i++)
		if (cube[i / 9][i % 9] != i + 1 && (i % 9) % 2 == 1 && cube[i / 9][i % 9] != 29 && cube[i / 9][i % 9] != 4 && cube[i / 9][i % 9] != 6) {
			swapEdges(cube, i);
			break;
	}
}
void out_of_place_corners(int cube[][9]) {
	//this does the same as out of place but for corners
	for (int i = 1; i < 54; i++)
	{
		if (cube[i / 9][i % 9] != i + 1 && (i % 9) % 2 == 0 && cube[i / 9][i % 9] != 1 && cube[i / 9][i % 9] != 9 && cube[i / 9][i % 9] != 10 && cube[i / 9][i % 9] != 28 && cube[i / 9][i % 9] != 21 && cube[i / 9][i % 9] != 39) {
			swapCorners(cube, i);
			break;
		}
	}
}

void solve(int cube[][9]) {
	//Runs until the edges are solved
	while (!solved(cube,1)){
		if (cube[0][5] != 29 && cube[0][5] != 6)
			swapEdges(cube,-1);
		else 
			//this is run when the program is stuck in a loop by 29 or 6
			out_of_place(cube);
	} 
	while (!solved(cube,0)) {
		//Runs while corners have not been solved
		if (cube[0][0] == 10 && cube[0][8] == 21) 
			string_to_move(cube, "uRfrBRFrbuRfRbbrFRbbrruu");
		else if ((cube[0][0] == 39 && cube[0][8] == 28)) 
			string_to_move(cube, "URfrBRFrburBrffRbrffrr");
		else if (cube[0][0] != 10 && cube[0][0] != 39 && cube[0][0] != 1)
			swapCorners(cube,-1);
		else
			out_of_place_corners(cube);
			
	}
}
