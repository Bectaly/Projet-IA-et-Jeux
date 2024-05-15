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


bool evaluateBoardId(Board* board,int id){
  return (board->getPlayerPosition(id)).x==board->getFinishingLine(id);
}

bool evaluateBoard(Board* board){
  bool b=(board->getPlayerPosition(0)).x==board->getFinishingLine(0);
  b=b || (board->getPlayerPosition(1)).x==board->getFinishingLine(1);
  return b;
}

Board* getChildBoardActionMoveDir( Board *board,int id,int dir){
  Board *child_p = NULL;
  if ( board->isMovePossiblePlayerDir(dir,id)) {
    child_p =new Board;
    child_p->Set(board->width,board->height);
    child_p->copy(board);
    child_p->moveDir(dir,id);
    //if(Bit[dir].x!=0) board->setDistance(id,board->getDistance(id)+Bit[dir].x);
    board->setDistance(id,board->getDistance(id)+Bit[dir].x);
  }
  return child_p;
}

Board* getChildBoardActionWallDir( Board *board,int x,int y,int dir,int id){
  Board *child_p = NULL;
  if ( board->isWallValid(x,y,dir)) {
    int da,db;
    child_p = new Board;
    child_p->Set(board->width,board->height);
    child_p->copy(board);
    child_p->subWall(id);
    child_p->addWall(x,y,dir);
    da=Astar(child_p,0);
    db=Astar(child_p,1);
    if(da>0 && db>0){
      child_p->setDistance(0,da);
      child_p->setDistance(1,db);
      return child_p;
    }
    else{
      child_p->Delete();
      delete child_p; 
    }
  }
  return NULL;
}