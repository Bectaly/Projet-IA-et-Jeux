#include "ia.hpp"

void remplace(List& list, Item *child_p ,Item * temp){
  if(temp==NULL){
    list.addLast(child_p);
  }
  else{
    if(temp->f>child_p->f){
      list.delList(temp);
      list.addLast(child_p);
    }
  }
}

int getHeuristicAstar( Item *node, int id) {//calculs la distance a une possible solution
  return abs(node->board->getFinishingLine(id)-node->board->getPlayerPosition(id).x);
}

int Astar(Board* board,int id){
  Item *cur_node=newItemBoard(board), *child_p;
  List open,closed;
  open.addLast(cur_node);
  while ( open.size()) {
    cur_node = open.popBest();
    if (evaluateBoardId(cur_node->board,id)) {
      open.clean();
      closed.clean();
        

      return cur_node->depth;
    } 
    else{
      closed.addLast(cur_node);
      for (int i =0; i < 4; i++) {
        child_p =nextItemBoard(cur_node,getChildBoardActionMoveDir( cur_node->board,id,i,true));
        if (child_p != NULL && closed.find(child_p->board)==NULL ) {
          child_p->g=child_p->depth;
          child_p->h=getHeuristicAstar(child_p,id);
          child_p->f=child_p->g+child_p->h;
          remplace(open,child_p,open.find(child_p->board));
        }
      }
    }
  }
  open.clean();
  closed.clean();
  return -1;
}

int countMovementOptions(Board* board, int playerId) {
    int score = 0;
    // Supposons que getPlayerPosition retourne la position actuelle du joueur sur le plateau
    for(int i=0;i<4;i++){if(board->isMovePossiblePlayerDir(i,playerId)){score++;}}
    return score;
}

int evaluateStrategicConfiguration(Board* board, int playerId) {
    int strategicValue = 0;
    int myDistance = board->getDistance(playerId);
    int oppDistance = board->getDistance(1 - playerId);
    strategicValue += (oppDistance - myDistance) * 2;
    strategicValue += board->getRemainingWall(playerId) * 3;
    return strategicValue;
}

double geHeuristicnegamax(Board* board, int id) {
    double score = 0;
    double opponentScore = 0;

    int myDistance = board->getDistance(id);
    int oppDistance = board->getDistance(1 - id);
    score += (myDistance == 0) ? 1000 : -myDistance * 10;
    opponentScore += (oppDistance == 0) ? 1000 : -oppDistance * 10;

    int myPaths = countMovementOptions(board, id);
    int oppPaths = countMovementOptions(board, 1 - id);
    score += myPaths * 3;
    opponentScore += oppPaths * 3;

    if (oppPaths < 2) {
        opponentScore += 50;
    }

    Coord myPos = board->getPlayerPosition(id);
    Coord oppPos = board->getPlayerPosition(1 - id);
    if (myPos.x == board->width / 2 && myPos.y == board->height / 2) {
        score += 5;
    }
    if (oppPos.x == board->width / 2 && oppPos.y == board->height / 2) {
        opponentScore += 5;
    }

    score += board->getRemainingWall(id) * 5;
    opponentScore += board->getRemainingWall(1 - id) * 5;

    int distanceBetweenPlayers = std::abs(myPos.x - oppPos.x) + std::abs(myPos.y - oppPos.y);
    score += (distanceBetweenPlayers < 3) ? 10 : 0;

    return score - opponentScore;
}

vector<Coord> getSurroundingCoords(Coord pos, int width, int height, int n) {
    vector<Coord> coords;
    for (int dx = -n; dx <= n; ++dx) {
        for (int dy = -n; dy <= n; ++dy) {
            int newX = pos.x + dx;
            int newY = pos.y + dy;
            if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                coords.push_back(Coord{newX, newY});
            }
        }
    }
    return coords;
}

Action* negamax(Board *board, int depth, double alpha, double beta, int id) {
    Board *child;
    Action* best = new Action;
    best->cout = ninf;

    if (evaluateBoardId(board, id) || depth == 0) {
        best->cout = geHeuristicnegamax(board, id);
        return best;
    }

    for (int i = 0; i < 4; i++) {
        child = getChildBoardActionMoveDir(board, id, i);
        if (child != NULL) {
            Action* trans = negamax(child, depth - 1, -beta, -alpha, 1 - id);
            double transCout = -trans->cout;
            if (transCout > best->cout) {
                best->cout = transCout;
                best->move = true;
                best->dir = i;
                best->DIA = child->getDistance(1);
                best->DPL = child->getDistance(0);
            }
            alpha = std::max(alpha, transCout);
            if (alpha >= beta) {
                delete trans;
                return best;
            }
            delete trans;
        }
    }

    if (board->getRemainingWall(id) > 0) {
        Coord oppPos = board->getPlayerPosition(1 - id);
        vector<Coord> surroundingCoords = getSurroundingCoords(oppPos, board->width, board->height, 1);
        for (const Coord& coord : surroundingCoords) {
            for (int j = 0; j < 2; j++) {
                child = getChildBoardActionWallDir(board, coord.x, coord.y, j, id);
                if (child != NULL) {
                    Action* trans = negamax(child, depth - 1, -beta, -alpha, 1 - id);
                    double transCout = -trans->cout;
                    if (transCout > best->cout) {
                        best->cout = transCout;
                        best->move = false;
                        best->dir = j;
                        best->DIA = child->getDistance(1);
                        best->DPL = child->getDistance(0);
                        best->coord.setCoord(coord.x, coord.y);
                    }
                    alpha = std::max(alpha, transCout);
                    if (alpha >= beta) {
                        delete trans;
                        return best;
                    }
                    delete trans;
                }
            }
        }
    }

    return best;
}
