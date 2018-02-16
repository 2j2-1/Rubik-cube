#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <string>
void scramble(int cube[][9], int amount);
void text_to_move(int cube[][9], std::string c);
void move(int cube[][9], int face, int direction);
void front_face(int cube[][9], int face, int direction);
void swapEdges(int cube[][9]);
void swapEdges(int cube[][9], int set);
void text_to_move(int cube[][9], char c);
void string_to_move(int cube[][9], const char* c);
void reverse_string_to_move(int cube[][9], const char* c);
void out_of_place(int cube[][9]);
#endif
