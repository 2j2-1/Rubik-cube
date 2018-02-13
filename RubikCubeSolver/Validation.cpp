#include "stdafx.h"
#include "Utils.h"

int g0[][4] = { { 2,8,47,53 },{ 4,6,49,51 } };
int g1[][4] = { { 1,9,46,54 },{ 3,7,48,52 } };

bool checkEdges(int cube[][9]) {
	return (in(g0[0], cube[0][1]) && in(g0[0], cube[0][7]) && in(g0[0], cube[5][1]) && in(g0[0], cube[5][7]) &&
		in(g0[1], cube[0][3]) && in(g0[1], cube[0][5]) && in(g0[1], cube[5][3]) && in(g0[1], cube[5][5]));
}
bool checkCorners(int cube[][9]) {
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
bool stages(int cube[][9],int stage) {
	switch (stage)
	{
	case 0:

		return checkEdges(cube);
	case 1:
		return (checkCorners(cube) && checkEdges(cube));
	}
}