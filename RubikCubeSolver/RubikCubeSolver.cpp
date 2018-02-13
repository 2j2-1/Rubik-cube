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
int depthLimit[] = {7,13,15,17};

int main() {
	int stage = 0;
	int stageLength = 1;
	std::string history[20] = { "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1","-1" };
	srand(1);
	print_cube(cube);

	/*while (true)
	{
	std::cin >> face;
	text_to_move(face,stage);
	std::cout << stages(0) << std::endl;
	print_cube();
	}*/

	scramble(cube,6);
	print_cube(cube);
	depthLimit[stage]++;
	do
	{
		backtrack(cube,0, stage, history,depthLimit[stage]);
		std::cout << "Stage: " << ++stage << std::endl;
		print_cube(cube);
	} while (stage < stageLength);
	std::cout << "Finished" << std::endl;
	std::cin.get();
}