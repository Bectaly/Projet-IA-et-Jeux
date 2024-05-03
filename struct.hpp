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

typedef struct _tile {
	int Joueur = 0;
	bool up = false;
  	bool right = false;
  	bool down = false;
  	bool left = false;
} Tile;

class Board{
  	private:
    	vector<Tile *> board;

	public:
    	int largeur, hauteur;
	Board(int largeur = 5, int hauteur = 5)
	{
      		this->largeur = largeur;
      		this->hauteur = hauteur;
      		board.resize(largeur*hauteur, new Box);
	}
hugvuhfc
   	//Board copy(Board * b)

    	void setTile(int x, int y, Box * b){board[y*hauteur+x] = b;}
    	Box * getTile(int x, int y){return board[y*hauteur+x];}
};

struct Item_s;

typedef struct Item_s {
	Board * board;
 	float f, g, h;
  	int depth;
  	struct Item_s * parent; 
} Item;

#endif
