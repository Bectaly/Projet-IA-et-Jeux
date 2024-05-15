#ifndef _BOARD_H
#define _BOARD_H 

#include "struct.hpp"
#include "List.hpp"

extern int Astar(Board* board,int id);

Item* newItemBoard(Board* board);
Item* nextItemBoard(Item*i,Board*b);

bool evaluateBoardId(Board* board,int id);
bool evaluateBoard(Board* board);
Board* getChildBoardActionMoveDir( Board *node,int id,int dir);
Board* getChildBoardActionWallDir( Board*node,int x,int y,int dir,int id);

#endif 