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

#define WIDTH 5
#define HEIGHT 5

#define WALL_INIT (int)0.07*2*(2*WIDTH*HEIGHT - WIDTH - HEIGHT)

using namespace std;

typedef struct _tile {
	int player = -1;
	vector<bool> walls;
} Tile;

class Board{
  	private:
    vector<Tile *> board;

	public:
    int width, height;
	Board(int width = WIDTH, int height = HEIGHT) { // Initialise un board vide, de dimension WIDTH*HEIGHT
      	this->width = width;
    	this->height = height;
  		board.resize(width*height);
		for(int i=0; i<width*height; i++)
		{
			Tile * t = new Tile;
			t->walls.resize(4, false);
			board[i] = t;
		}
	}

	int getPlayerPosition(int id) { // Donne la position d'un joueur d'après son ID (0 ou 1)
		for(int i=0; i<width; i++) {
			for(int j=0; j<height; j++) {
				if (getTile(i,j)->player == id) return j*width+i;
			}
		}
	}

	int getBoardW() {return width;} // Renvoie la largeur du board

	int getBoardH() {return height;} // Renvoie la hauteur du board

	bool isMovePossible(int x, int y, int bit) { // Renvoie si le move dirigé par le bit est possible depuis (x,y)
		bool b = false;
		
		if(bit==0 && y==0) b=true;
		else if (bit==1 && x==width) b=true;
		else if (bit==2 && y==height) b=true;
		else if (bit==3 && x==0) b=true;
		
		if(b)
		{
			cout << "error in isMovePossible: target out of board" << endl;
			return false;
		}

		if(bit==0 && getTile(x, y-1)->player!=-1) return false;
		else if(bit==1 && getTile(x+1, y)->player!=-1) return false;
		else if(bit==2 && getTile(x, y+1)->player!=-1) return false;
		else if(bit==3 && getTile(x-1, y)->player!=-1) return false;

		return getTile(x, y)->walls[bit];
	}

	vector<int> possibleMoves(int x, int y) { // Renvoie un vecteur contenant les bits de direction possibles pour un mouvement depuis (x,y)
		vector<int> moves;
		int k=0;

		for(int bit=0; bit<4; bit++) {
			if(isMovePossible(x, y, bit)) {
				k++;
			}
		}

		moves.resize(k);

		int kk = 0;

		for(int bit=0; bit<4; bit++) {
			if(isMovePossible(x, y, bit)) {
				vector[kk] = bit;
				kk++;
			}
		}

		return moves;
	}

	int getTileId(int x, int y) { // Renvoie l'id du player positionné en (x,y), 0 ou 1, et -1 si la case est vide
		Tile * t = getTile(x, y);
		return t->player;
	}		

	/*
	void setTile(int x, int y, Tile * t) { // Change la tile (x,y) en la tile passée en argument
		board[y*width+x]=t;
	}
	*/	

	void addOneWall(int x, int y, int bit) { // Ajoute un mur sur UNE TILE
		getTile(x,y)->walls[bit]=true;
	}

	void addWall(int x, int y, int bit) { // Ajoute le mur sur les DEUX TILES mitoyennes concernées
		addOneWall(x, y, bit);

		if (bit==0) addOneWall(x, y-1, 2);
		else if (bit==1) addOneWall(x+1, y, 3);
		else if (bit==2) addOneWall(x, y+1, 0);
		else if (bit==3) addOneWall(x-1, y, 1);
	}

    Tile * getTile(int x, int y) {return board[y*width+x];} // Renvoie le pointeur de la tile placée en (x,y)
};

struct Item_s;

typedef struct Item_s {
	Board * board;
 	float f, g, h;
  	int depth;
  	struct Item_s * parent; 
} Item;

#endif