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
	Board(int width = BOARD_WIDTH, int height = BOARD_HEIGHT) { // Initialise un board vide, de dimension width*height
      		this->width = width;
      		this->height = height;
      		board.resize(width*height);
		for(int i=0; i<width*height; i++)
			{
				Tile * t = new Tile;
				t->player = -1;
				for(int j=0; j<4; j++) t->walls[j]=false;
				board[i] = t;
			}
	}

	int getPlayerPosition(int id) { // Donne la position d'un joueur d'après son ID (0 ou 1)
		for(int i=0; i<width; i++)
			{
				for(int j=0; j<height; j++)
					{
						if (getTile(i,j)->player == id) return j*width+i;
					}
			}
	}

	int getBoardW() {return width;} // Renvoie la largeur du board
	int getBoardH() {return height;} // Renvoie la hauteur du board

	bool isMovePossible(int x, int y, int bit) { // Renvoie si la move dirigé par le bit est possible depuis (x,y)
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

		return getTile(x, y)->walls[bit];
	}

	int getTileId(int x, int y) { // Renvoie le bit du player positionné en (x,y), 0 ou 1, et -1 si la case est vide
		Tile * t = getTile(x, y);
		return t->player;
	}
		
		

	void setTile(int x, int y, Tile * t) { // Change la tile (x,y) en la tile passée en argument
		board[y*width+x]=t;
	}		

	void addOneWall(int x, int y, int bit) { // Ajoute un mur sur UNE TILE
		Tile * t = getTile(x, y);

		if (bit==0) t.up=true;
		else if (bit==1) t.right=true;
		else if (bit==2) t.down=true;
		else if (bit==3) t.left=true;

		setTile(x, y, t);
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
