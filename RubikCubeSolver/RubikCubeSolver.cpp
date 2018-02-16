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
	while (true)
	{
		scramble(cube, 40);
		print_cube(cube);

		do
		{
			
			do
			{
				//print_cube(cube);
				if (cube[0][5] != 29) {
					swapEdges(cube);
				}
				else {
					out_of_place(cube);
				}
			} while (cube[0][5] != 6);
			out_of_place(cube);
		} while (!solved(cube));

		print_cube(cube);
		std::cout << "Finished" << std::endl;
		//std::cin.get();
	}
}