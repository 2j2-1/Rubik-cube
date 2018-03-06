#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <stdio.h>
#include <Windows.h>
#include <string>

class cGame {
public:
	int screenWidth = 120;
	int screenHeight = 45;


	void draw_pixel(int, int, char);
	void blank_screen();
	void draw(int);
	void setup();
	void print(std::string, int, int);

	char *screen = new char[screenWidth*screenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	DWORD dwBytesWritten = 0;

};