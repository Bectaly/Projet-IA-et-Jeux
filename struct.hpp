#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <random>

using namespace std;


typedef struct _box {
  int Joueur=0;
  int wall=0;
} Box;

class Board{
  private:
    vector<Box*> board;
  public:
    int largeur,hauteur;
    Board(int largeur=5, int hauteur=5){
      this->largeur=largeur;
      this->hauteur=hauteur;
      board.resize(largeur*hauteur,new Box);
    }
    //copy(Board* b);
    void set(int x, int y,Box * b){board[y*hauteur+x]=b;}
    Box* get(int x, int y){return board[y*hauteur+x];}
};


struct Item_s;

typedef struct Item_s {
  Board *board;
  float f, g, h;
  int depth;
  struct Item_s *parent; 
} Item;


#endif 
