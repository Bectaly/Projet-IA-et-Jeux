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

void astar(){

// je pars d'une position et mon astar doit me donner toute les cases atteigables depuis cette postion 

    Item *cur_node, *child_p, *temp;



    while (listCount(&openList_p) != 0){ 
        /* Get the first item on the open list */
        cur_node = popBest(&openList_p) ;



		/* Do we have a solution? */
        if (evaluateBoard(cur_node) == 0 ){
            showSolution(cur_node);
            return;
        }

		if (onList(&closedList_p, cur_node->board) == NULL) {
			addFirst(&closedList_p, cur_node) ;
			for (int i = 0; i < MAX_BOARD; i++){
				child_p = getChildBoard(cur_node, i) ;
				// it's a valid child and not visited
				if (child_p != NULL && onList(&closedList_p,child_p->board)==NULL) { 
					if(onList(&openList_p,child_p->board)==NULL){
						// estimation optimiste (minorante) du coût de n à la solution
						child_p->h = getSimpleHeuristic(child_p) ;
						// coût pour aller de la racine jusqu’au nœud n
						child_p->g = child_p->depth ;
						// estimation du coût global 
						child_p->f = child_p->g+child_p->h ;
						
						/* Add child node to openList */
						addFirst(&openList_p, child_p) ;
					}
					else{
						temp = onList(&openList_p, child_p->board) ;
						// If the node already exists but with a higher cost
						if(temp->f > child_p->f){
							/* Add child node to openList */
							addFirst(&openList_p, child_p) ;
						}
					}
				}
			}
		}
	}

}

int main()
{ 
  
  Game g(10,5);
  while(g.event()){g.display();}
  return 0;
}
