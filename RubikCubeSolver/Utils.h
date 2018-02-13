#ifndef UTILS_H
#define UTILS_H
#include <string>
void print_cube(int cube[][9]);
int find(std::string c[], int length, char find); 
bool compare(int face[], int solved[]);
bool in(int values[], int find);
void to_file(std::string history[]);

#endif