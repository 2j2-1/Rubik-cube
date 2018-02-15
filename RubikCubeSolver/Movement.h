#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <string>
void scramble(int cube[][9], int amount); 
void text_to_move(int cube[][9], std::string c, int stage);
void move(int cube[][9], int face, int direction);
void front_face(int cube[][9], int face, int direction);
bool backtrack(int cube[][9], int depth, int stage, std::string history[], int depthLimit);

#endif
