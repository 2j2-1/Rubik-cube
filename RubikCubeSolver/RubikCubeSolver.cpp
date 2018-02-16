#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include "Movement.h"
#include "Utils.h"
#include "Validation.h"

int cube[][9] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
{ 10,11,12,13,14,15,16,17,18 },
{ 19,20,21,22,23,24,25,26,27 },
{ 28,29,30,31,32,33,34,35,36 },
{ 37,38,39,40,41,42,43,44,45 },
{ 46,47,48,49,50,51,52,53,54 } };

int main() {
	srand(time(NULL));
	do
	{

	
	scramble(cube, 40);
	//print_cube(cube);

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
	//std::cout << "Finished edges\n";
	
	do {
		do {
			if (cube[0][0] == 10 && cube[0][8] == 21) {
				print_cube(cube);
				std::cout << "case 1\n";
				std::cin.get();
				string_to_move(cube, "");
			}
			else if ((cube[0][0] == 39 && cube[0][8] == 28)) {
				print_cube(cube);
				std::cout << "case 2\n";
				std::cin.get();
				string_to_move(cube, "");
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

	/*print_cube(cube);
	std::cout << "Finished" << std::endl;*/
	//std::cin.get();
	} while (true);
	
}