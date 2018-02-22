#include "stdafx.h"
#include "Utils.h"


int find(char c[], int length, char find) {
	for (int i = 0; i < length; i++)
		if (find == c[i])
			return i;
	return -1;
}


