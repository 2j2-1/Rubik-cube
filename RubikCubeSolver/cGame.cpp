﻿#include "stdafx.h"
#include "cGame.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <stdio.h>
#include <Windows.h>
#include <string>

void cGame::draw_pixel(int x, int y, char c) {
	if (y >= 0 && y <= screenHeight && x >= 0 && x < screenWidth) {
		screen[y*screenWidth + x] = c;
	}
}

void cGame::blank_screen() {
	for (int y = 0; y < this->screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			draw_pixel(x, y, 32);
		}
	}
}

int cGame::random(int lower, int upper) {
	return rand() % (upper - lower) + lower;
}

void cGame::rect(float * rectangle, char c) {
	for (int _x = rectangle[0]; _x < rectangle[0] + rectangle[2]; _x++) {
		for (int _y = rectangle[1]; _y < rectangle[1] + rectangle[3]; _y++) {
			draw_pixel(_x, _y, c);
		}
	}
}
WORD faceColors[] = { 238,153 ,204,170,187,255 };
int count = 0;
void write_symbol_in_color(HANDLE h, SHORT x, SHORT y, char* symbol,int cubeSize){
	COORD here;
	here.X = x;
	here.Y = y;
	//fix this
	WORD attribute = faceColors[(*symbol + 3) % 6];
	DWORD written;
	FillConsoleOutputAttribute(h, attribute, cubeSize, here, &written);

		
}
void cGame::draw(int cubeSize) {
	DWORD written;
	screen[screenWidth * screenHeight - 1] = '\0';
	for (int i = 0; i < screenHeight*screenWidth-1; i++)
	{
		if (screen[i] > 32 && screen[i] < 39) {
			write_symbol_in_color(hConsole, i % (short)screenWidth, (short)(i / screenWidth), &screen[i],cubeSize);
			i += cubeSize;
		}

	}
	WriteConsoleOutputCharacterA(hConsole, screen, screenHeight*screenWidth, {0,0}, &written);
}

void cGame::setup() {
	SetConsoleActiveScreenBuffer(hConsole);
	srand(time(NULL));
}

void cGame::line(float* points, char c) {
	if (points[0] == points[2]) {
		for (int i = points[1]; i < points[3]; i++) { draw_pixel(points[0], i, c); }
	}
	else if (points[1] == points[3]) {
		for (int i = points[0]; i < points[2]; i++) { draw_pixel(i, points[1], c); }
	}

}

bool cGame::collide(float* rectA, float* rectB) {
	if (rectA[0] < rectB[0] + rectB[2] && rectA[0] + rectA[2] > rectB[0] &&
		rectA[1] < rectB[1] + rectB[3] && rectA[1] + rectA[3] > rectB[1]) {
		return true;
	}
	return false;
}

void cGame::print(std::string s, int x, int y) {
	for (int i = 0; i < s.length(); i++)
	{
		draw_pixel(x + i, y, s[i]);
	}
}