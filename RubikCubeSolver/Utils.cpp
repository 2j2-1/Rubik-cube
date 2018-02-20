#include "stdafx.h"
#include "Utils.h"
#include <string>
#include <iostream>
#include <fstream>
#include "cGame.h"


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