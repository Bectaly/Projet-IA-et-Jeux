#include <cstdio.h>
#include <iostream>
#include "board.h"

Item * initBoard (Item * node, Board board) 
{
  assert( node );
  for(int i=0;i<(WIDTH * HEIGHT);i++)
  {
      node->board[i]=board[i];
  }
}

Item *new_item()
{
  Item *node;

  node = (Item *) malloc( sizeof(Item) );
  assert(node);
  Board board();
  node->board = board;
  node->parent = NULL;
  node->depth= 0;
  node->f = node->g = node->h = (double)0.0;

  return node;
}


Item * initGame()
{
  int x=WIDTH;
  int y=HEIGHT;
  int size= x*y;
  int i;
  Item *node;
//initialise le vecteur 
  Board initial ();
  for (int i=0; i<size; i++) 
  {
    initial[i] = 0;
  }
  x=w/2;
  for (id=0; id<2; id=id+1)
  {
    initial->set(x,y*id,id+1);
  }
  node = new_item();
  initBoard(node, initial);
  node->depth = 0;
  return node;
}


void printBoard(item * node)
{
  assert(node);
  printf("\n");
  for (int j=0; j<WIDTH; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
  for (int i = 0 ; i < WIDTH*HEIGHT ; i++) {
    if (i%WIDTH == 0) printf("|");
    if (node->board[i] == 0) printf("   |");
    else printf("%2d |", node->board[i]);
    if (((i+1)%WIDTH) == 0) {
      printf("\n");
      for (int j=0; j<WIDTH; j++) if (j==0) printf(" ___"); else printf("____"); printf("\n");
    }
  }
  printf("\n");
}


double evaluateBoard(Item * node) 
{
    int j;
    int id;
    for (id=0; id<2; id=id+1)
    {
        for (j=0; j<WIDTH; j=j+1)
        {
           if ((node->board).getPlayerPosition (id) == node->board[j][id*HEIGHT])
           {
               cout << "Le joueur " << id << "à gagné !!" << endl;
               return 1;
           }
        }
    }
    return 0;
}

bool isValid_Wall (Item *node, int x, int y, int bit)
{
  if (exist_path(node,x,y,bit))
  {
    return 1;
  }
  return 0;
}


Item *getChildBoard( Item *node,int bit, int id )
{
    Item *child_p = NULL;
    if ( isMovePossiblePlayerDir (bit,id) )
    {
         /* allocate and init child node */
      child_p=new_item();
      initBoard (child_p, node->board);
        /* Make move */
      child_p->parent=node;
      child_p->depth=node->depth+1;
      child_p->f= child_p->depth;
      moveDir (bit,id);
    }
   return child_p;
}

void placeWall(int x, int y, int bit)
{
  if (isValid_Wall(node, x,y,bit))
    Board::addWall(x,y,bit);
}
 
bool exist_path(item * node, int x, int y, int bit))
{
   if (dfs ( node->board,0) && dfs (node->board, 1))
       return 1;
  return 0;
}
