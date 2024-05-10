#ifndef _BOARD_H
#define _BOARD_H 
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


// alterternative
extern int Astar(Board* board,int id);

Item* newItemBoard(Board* board);
Item* nextItemBoard(Item*i,Board*b);

bool evaluateBoard(Board* board,int id);
Board* getChildBoardActionMoveDir( Board *node,int id,int dir);
Board* getChildBoardActionWallDir( Board*node,int x,int y,int dir,int id);

#endif
