#include "Display.hpp"

void printBoard(Item * i){
  Board* b=i->board;
  for(int x=0;x<b->hauteur;x++){
    cout<<"[ "<<b->get(x,0)->wall<<" "<<ends;
    for(int y=1;y<b->largeur;y++){
      cout<<b->get(x,y)->wall<<" "<<ends;
    }
    cout<<"]"<<endl;
  }
}


Item * new_item(int largeur, int hauteur){
  Item * i=new Item;
  i->depth=0;
  i->f=i->g=i->h=0;
  i->parent=NULL;
  i->board=new Board(largeur,hauteur);
  Box *b =new Box;
  b->wall=14;
  i->board->set(0,2,b);
  b=i->board->get(3,4);
  b->wall=3;

  return i;
}

int main()
{ 
  
  Game g(10,5);
  while(g.event()){g.display();}
  return 0;
}
