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

#include "list.hpp"
#include "display.hpp"

#define WIDTH 5
#define HEIGHT 5

#define WALL_INIT (int)(10/144*2*(2*WIDTH*HEIGHT - WIDTH - HEIGHT))

using namespace std;

extern vector<sf::Vector2i> Bit;
void define_Bit();

typedef struct _tile {
	int player = -1;
	vector<bool> walls;
} Tile;

class Coord{
	public:
		int x,y;//facile d'acces
		void set_coord(int x,int y){this->x=x;this->y=y;}

};

class Board{
  	private:
      vector<Tile *> board;
	  vector<Coord> player;

	public:
		int width, height;
		Board(int width = WIDTH, int height = HEIGHT); // Initialise un board vide, de dimension WIDTH*HEIGHT
		void setcoord(Coord p1,int id){
			player[id]=p1;
			getTile(p1.x,p1.y)->player=id;
		}
		//void copy(Board&board);
		int getPlayerPosition(int id); // Donne la position d'un joueur d'après son ID (0 ou 1)
		bool isMovePossible(int x, int y, int bit);  // Renvoie si le move dirigé par le bit est possible depuis (x,y)
		bool isMovePossiblePlayer(int x, int y,int id);// Renvoie si le move dirigé par le bit est possible depuis (x,y)
		bool isMovePossiblePlayerDir(int bit,int id);
		void moveTo(int x,int y,int id);
		void moveDir(int dir,int id);
		vector<int> possibleMoves(int x, int y);// Renvoie un vecteur contenant les bits de direction possibles pour un mouvement depuis (x,y)
		int getTileId(int x, int y){return getTile(x, y)->player;} // Renvoie l'id du player positionné en (x,y), 0 ou 1, et -1 si la case est vide
		int getTileId(Coord c){return getTile(c)->player;} // Renvoie l'id du player positionné en (x,y), 0 ou 1, et -1 si la case est vide
		bool getTileWall(int x, int y,int bit); // Renvoie l'id du player positionné en (x,y), 0 ou 1, et -1 si la case est vide
		bool isWallValid(int x, int y,int bit); // Renvoie l'id du player positionné en (x,y), 0 ou 1, et -1 si la case est vide
		void addOneWall(int x, int y, int bit) { getTile(x,y)->walls[bit]=true;}// Ajoute un mur sur UNE TILE
		void addWall(int x, int y, int bit); // Ajoute le mur sur les DEUX TILES mitoyennes concernées
		Tile * getTile(Coord c) {return board[c.y*width+c.x];} // Renvoie le pointeur de la tile placée en (x,y)
		Tile * getTile(int x, int y) {return board[y*width+x];} // Renvoie le pointeur de la tile placée en (x,y)
};

struct Item_s;

typedef struct Item_s {
	Board * board;
 	float f, g, h;
  	int depth;
  	struct Item_s * parent; 
} Item;

void printBoard(Board& b);
void printBoardWall(Board& b,int bit);
#endif