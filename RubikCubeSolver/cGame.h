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
	int screenHeight = 40;


	void draw_pixel(int, int, char);
	void blank_screen();
	void rect(float *, char);
	void draw();
	void setup();
	void line(float *, char);
	void print(std::string, int, int);
	int random(int, int);

	bool collide(float *, float *);

	wchar_t *screen = new wchar_t[screenWidth*screenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	DWORD dwBytesWritten = 0;

};