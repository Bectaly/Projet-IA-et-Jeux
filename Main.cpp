#include "Display.hpp"

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
            addFirst(&closedList_p, cur_node);
            //vecteur moves
            vector<int> moves= possibleMove(child_p->id);
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
                            addFirst(&openList_p, child_p);
                        } else {
                            temp = onList(&openList_p, child_p->board);
                            if (temp->f > child_p->f) {
                                addFirst(&openList_p, child_p);
                            }
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
  int n=10;
  Game g(n,n);
  g.Run();
  return 0;
}
