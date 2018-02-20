#ifndef UTILS_H
#define UTILS_H
#include <string>

void print_cube(int cube[][9]);
int find(std::string c[], int length, char find); 
bool in(int values[], int find);
void to_file(int cube[][9], std::string history[]);

#endif