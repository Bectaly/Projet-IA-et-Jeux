#include <cstdio.h>
#include <iostream>
#include "board.hpp"

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


void printBoard(Item * node)
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
 
bool exist_path(Item * node, int x, int y, int bit)
{
   if (dfs ( node->board,0) && dfs (node->board, 1))
       return 1;
  return 0;
}

#include "board.hpp"

Item* newItemBoard(Board*b){
  Item* tmp=new Item;
  tmp->board=new Board;
  tmp->board->Set(b->width,b->height);
  tmp->board->copy(b);
  tmp->depth=0;
  tmp->f=0;
  tmp->g=0;
  tmp->h=0;
  return tmp;
}

Item* nextItemBoard(Item*i,Board*b){
  if(b==NULL) return NULL;
  Item* tmp=new Item;
  tmp->board=b;
  tmp->depth=i->depth+1;
  return tmp;
}


bool evaluateBoard(Board* board,int id){
  return (board->getPlayerPosition(id)).x==board->getFinishingLine(id);
}

Board* getChildBoardActionMoveDir( Board *board,int id,int dir){
  Board *child_p = NULL;
  if ( board->isMovePossiblePlayerDir(dir,id)) {
    child_p =new Board;
    child_p->Set(board->width,board->height);
    child_p->copy(board);
    child_p->moveDir(dir,id);
  }
  return child_p;
}

Board* getChildBoardActionWallDir( Board *board,int x,int y,int dir,int id){
  Board *child_p = NULL;
  if ( board->isWallValid(x,y,dir)) {
    child_p = new Board;
    child_p->Set(board->width,board->height);
    child_p->copy(board);
    child_p->subWall(id);
    child_p->addWall(x,y,dir);
    if(Astar(child_p,0)>0 && Astar(child_p,1)>0){
      return child_p;
    }
    else{
      child_p->Delete();
      delete child_p; 
    }
  }
  return NULL;
}