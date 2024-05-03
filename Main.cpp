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

std::vector<Item*> astar(int x, int y, int id) {
    std::vector<Item*> reachableNodes;
    Item *cur_node, *child_p, *temp;

    while (listCount(&openList_p) != 0) { 
        /* Get the first item on the open list */
        cur_node = popBest(&openList_p);

        /* Add current node to reachable nodes */
        reachableNodes.push_back(cur_node);

        if (onList(&closedList_p, cur_node->board) == NULL) {
            addFirst(&closedList_p, cur_node);
            for (int i = 0; i < MAX_BOARD; i++) {
                child_p = getChildBoard(cur_node, i);
                if (child_p != NULL && onList(&closedList_p, child_p->board) == NULL) {
                    if (onList(&openList_p, child_p->board) == NULL) {
                        child_p->h = getSimpleHeuristic(child_p);
                        child_p->g = child_p->depth;
                        child_p->f = child_p->g + child_p->h;
                        addFirst(&openList_p, child_p);
                    }
                    else {
                        temp = onList(&openList_p, child_p->board);
                        if (temp->f > child_p->f) {
                            addFirst(&openList_p, child_p);
                        }
                    }
                }
            }
        }
    }

    return reachableNodes;
}


int main()
{ 
  
  Game g(9,9);
  while(g.event()){g.display();}
  return 0;
}
