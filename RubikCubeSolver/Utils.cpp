#include "stdafx.h"
#include "Utils.h"
#include <string>
#include <iostream>
#include <fstream>
void print_cube(int cube[][9]) {
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
bool in(int values[], int find) {
	for (int i = 0; i < sizeof(values); i++)
		if (values[i] == find)
			return true;
	return false;
}
void to_file(int cube[][9],std::string history[]) {
	std::ofstream myfile;
	myfile.open("example.txt", std::ios_base::app);
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			myfile << cube[x][y] << ":";
		}
	}
	myfile << ";";
	for (int i = 0; i < 20; i++)
	{
		if (history[i] != "-1")
			myfile << history[i] << ",";
	}
	myfile << std::endl;
	myfile.close();
}