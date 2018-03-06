#include "stdafx.h"
#include "cGame.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <stdio.h>
#include <Windows.h>
#include <string>

WORD faceColors[] = { 238,153 ,204,170,187,255 };

void cGame::draw_pixel(int x, int y, char c) {
	if (y >= 0 && y <= screenHeight && x >= 0 && x < screenWidth) {
		//Translate from 2d coordinates to 1d
		screen[y*screenWidth + x] = c;
	}
}

void cGame::blank_screen() {
	//Fill screen with blank pixels
	for (int y = 0; y < this->screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			draw_pixel(x, y, 32);
		}
	}
}

void cGame::draw(int cubeSize) {
	//draws each char in the array to the screen
	DWORD written;
	for (int i = 0; i < screenHeight*screenWidth-1; i++)
	{
		//If one of the predefined symbols are to be drawn repalce it instead with a row of pixels of set length and color
		if (screen[i] > 32 && screen[i] < 39) {
			WORD attribute = faceColors[(screen[i] + 3) % 6];
			FillConsoleOutputAttribute(hConsole, attribute, cubeSize, {i % (short)screenWidth, (short)(i / screenWidth)}, &written);
			i += cubeSize;
		}
	}
	WriteConsoleOutputCharacterA(hConsole, screen, screenHeight*screenWidth, {0,0}, &written);
}

void cGame::setup() {
	SetConsoleActiveScreenBuffer(hConsole);
	srand(time(NULL));
}

void cGame::print(std::string s, int x, int y) {
	//Draws a string to the screen
	for (int i = 0; i < s.length(); i++)
	{
		draw_pixel(x + i, y, s[i]);
	}
}