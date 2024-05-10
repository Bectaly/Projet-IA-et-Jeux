#include "ia.hpp"
//dfs a disparu


void remplace(List& list, Item *child_p ,Item * temp){}

int getHeuristicAstar( Item *node, int id) {}

int Astar(Board* board,int id){// a voir ()
  return -1;
}

double geHeuristicnegamax(Board* board,int id){// a revoir marche pas bien veut pas gagner
 int myDistance = Astar(board,id);
    int oppDistance = Astar(board,1-id);
    int myWallsLeft = board->getRemainingWall(id);

    if (myDistance == 0) return std::numeric_limits<double>::infinity(); // Score maximal pour atteindre la ligne d'arrivée
    if (oppDistance == 0) return -std::numeric_limits<double>::infinity(); // Score minimal si l'adversaire atteint la ligne d'arrivée

    double myScore = -myDistance * 2 + myWallsLeft * 10; // Encourage à se rapprocher de la ligne d'arrivée et à utiliser les murs de manière stratégique
    double opponentScore = oppDistance * 2; // Plus l'adversaire est loin, mieux c'est

    return myScore - opponentScore;
}

Action* negamax(Board *board,int depth,double alpha ,double betha,int id){
  Board *child;
  Action*best=new Action,*trans=new Action;
  best->cout=ninf;
  bool s=false;
  if(evaluateBoard(board,id)){
    best->cout=inf;
    return best;
  }
  if ( depth==0) {
    best->cout=geHeuristicnegamax(board,id);
    return best;
  }
  for(int i=0;i<4;i++){//pour les deplacement  
    child=getChildBoardActionMoveDir(board,id,i);
    if(child!=NULL){
      trans=negamax(child,depth-1,-betha,-alpha,id);
      if(-(trans->cout)>best->cout){
        best=trans;
        best->move=true;
        best->dir=i;
      }
      alpha=max(alpha,best->cout);
      if(alpha>=betha){
        s=true;
        break;
      }
    }
  }
  if(board->getRemainingWall(id)>0){
    int x=-1,y,j;
    while(x<board->width-1 && !s){ //pour les murs
      x++;
      y=-1;
      while(y<(board->height-1) && !s){
        y++; 
        j=0;
        while(j<2 && !s){
          j++;          
          child=getChildBoardActionWallDir(board,x,y,j,id);
          if(child!=NULL){
            
            trans=negamax(child,depth-1,-betha,-alpha,id);
            
            if(-(trans->cout)>best->cout){
              best=trans;
              best->move=false;
              best->dir=j;
              best->coord.setCoord(x,y);
            }
          alpha=max(alpha,best->cout);
          if(alpha>=betha)s=true;
          }
        }
      }
    }
    
  }
  return best;
}