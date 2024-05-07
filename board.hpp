#ifndef BOARD_HPP
#define BOARD_HPP
#include "struct.hpp"

Item * initBoard (Item * node, Board board);
Item *new_item();
Item * initGame();
Board initGame(Board board);
void printBoard(Item * node);
double evaluateBoard(Item * node);
bool isValid_Wall (Item *node, int x, int y, int bit);
Item *getChildBoard( Item *node,int bit, int id );
void placeWall(int x, int y, int bit);
 bool exist_path(Item * node, int x, int y, int bit);

#endif
