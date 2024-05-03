#include <cstdio.h>
#include <iostream>
#include "board.h"

Board createBoard(int w, int h)
{
    assert
    int size = w*h;
    int * board = malloc(size*sizeof(int));

    int i;
    for(i=0; i<size; i++)
    {
        board[i] = 0;
    }
}

Board initGame(Board board)

void printBoard(Board board)

void printBoardHumanReadable(Board board)

void placeWall(int x, int y, int bit)

double evaluateBoard(Item * node) 
{
    int j;
    int id;
    for (id=0; id<2; id=id+1)
    {
        for (j=0; j<node->board->width; j=j+1)
        {
           if ((node->board).getPlayerPosition (id) == node->board[id*node->board->height][j])
           {
               cout << "Le joueur " << id << endl;
               return 1;
           }
        }
    }
        return 0;
}


void movePlayer(int id, int bit)

Item *getChildBoard( Item *node,int x,int y, int bit )
{
    Item *child_p = NULL;
    if ( isMovePossible(x,y, bit ) )
    {
         /* allocate and init child node */
        child_p=new_item();
        initiBoard(child_p,node->board);
        /* Make move */
        child_p->parent=node;
    	child_p->depth=node->depth+1;
    	child_p->f= child_p->depth;
    	child_p->board->set(x,y,child_p->depth);
    }
   return child_p;
}
