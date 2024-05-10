#ifndef _IA_H
#define _IA_H 

#include "board.hpp"

#define inf 100000
#define ninf -100000


void remplace(List& list, Item *child_p ,Item * temp);
int getHeuristicAstar( Item *node, int id);
int Astar(Board* board,int id);

double geHeuristicnegamax(Board* board,int id);
Action* negamax(Board*item=NULL,int depth=2,double alpha=ninf ,double betha=inf,int id=1);

#endif 