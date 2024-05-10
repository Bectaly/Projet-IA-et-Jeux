#include "display.hpp"
#include "struct.cpp"
#include "list.hpp"
#include "board.hpp"

std::vector<Item*> astar(int id) {
    std::vector<Item*> reachableNodes;
    Item *cur_node, *child_p, *temp;

    while (listCount(&openList_p) != 0) { 
        /* Get the first item on the open list */
        cur_node = openList_p.popBest();

  //recuperer les coordonnées x et y du perso dans board 

        /* Add current node to reachable nodes */
        reachableNodes.push_back(cur_node);

      

        if (onList(&closedList_p, cur_node->board) == NULL) {
            //addFirst(&closedList_p, cur_node);
            addLast(&closedList_p, cur_node);
            //vecteur moves
            //vector<int> moves= possibleMove(child_p->id);
            vector<int> moves= possibleMoves(child_p->board);
            for (int i = 0; i < moves.size(); i++) {
                // Generate child node
                child_p = getChildBoard(cur_node, x,y,moves[i],id);


                // Check if move is possible
                if (child_p != NULL) {
                    if (onList(&closedList_p, child_p->board) == NULL) {
                        if (onList(&openList_p, child_p->board) == NULL) {
                            child_p->h = getSimpleHeuristic(child_p);
                            child_p->g = child_p->depth;
                            child_p->f = child_p->g + child_p->h;
                            //addFirst(&openList_p, child_p);
                            addLast(&openList_p, child_p);
                        } else {
                            temp = onList(&openList_p, child_p->board);
                            if (temp->f > child_p->f) {
                                //addFirst(&openList_p, child_p);
                                addLast(&openList_p, child_p);
                            }
                        }
                    }
                }
            }
        }
    }

    return reachableNodes;
}

bool dfs(Board board, int id)
{
  Item *cur_node, *child_p, *temp;
  int i;
  List openList_p;
  List closedList_p;
  openList_p.initList; 
  closedList_p.initList;
  Item *initial_state = initGame();
  openList_p.addLast( initial_state );

  while ( openList_p.listCount != 0 ) { /* While items are on the open list */
   
    /* Get the first item on the open list */
    
    cur_node = openList_p.popFirst;

		
    // printf("%d  %f\n", listCount(&openList_p), evaluateBoard( cur_node ));

    /* Add it to the "visited" list */
    closedList_p.addFirst(cur_node);
    /* Do we have a solution? */
    if ( evaluateBoard(cur_node)) {
      return 1;
    } 
    else {

      /* Enumerate adjacent states */
      for (int i = 0; i < WIDTH*HEIGHT; i++) {
     
        child_p = getChildBoard( cur_node, bit, i);
   	
        if (child_p != NULL) { // it's a valid child!
					
                /* Ignore this child if already visited */
		if ((closedList_p.onList(child_p->board))==NULL && (openList_p.onList(child_p->board)==NULL))	
                /* Add child node to openList */
	  			 openList_p.addFirst( child_p );
        }
      }
    }
  }
	return 0;
 }




int main()
{ 
  Game g(7,3);
  g.Run();
  return 0;
}
