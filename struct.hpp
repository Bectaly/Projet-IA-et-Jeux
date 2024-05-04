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

typedef struct _couple {
	int x,y;
} Couple;

extern vector<Couple> Bit;
void define_Bit();// pour simplifier beaucoup les calculs de direction

typedef struct _tile {
	int player = -1;
	vector<bool> walls;
} Tile;

class Coord{
	public:
		int x,y,id;//facile d'acces
		void set_coord(int x,int y){this->x=x;this->y=y;}

};

class Board{
  	private:
      vector<Tile *> board;
      Coord p1,robot;

	public:
		int width, height;
		Board(int width = WIDTH, int height = HEIGHT); // Initialise un board vide, de dimension WIDTH*HEIGHT
		void setcoordplayers(Coord p1){
			this->p1=p1;
			getTile(p1.x,p1.y)->player=p1.id;
		}
		void setcoordrobot(Coord robot){
			this->robot=robot;
			getTile(robot.x,robot.y)->player=robot.id;
		}
		//void copy(Board&board);
		int getPlayerPosition(int id); // Donne la position d'un joueur d'après son ID (0 ou 1)
		bool isMovePossible(int x, int y, int bit);  // Renvoie si le move dirigé par le bit est possible depuis (x,y)
		bool isMovePossiblePlayer(int x, int y);// Renvoie si le move dirigé par le bit est possible depuis (x,y)
		void moveTo(int x,int y);
		//void moveDir(int x,int y,int dir);
		vector<int> possibleMoves(int x, int y);// Renvoie un vecteur contenant les bits de direction possibles pour un mouvement depuis (x,y)
		int getTileId(int x, int y){return getTile(x, y)->player;} // Renvoie l'id du player positionné en (x,y), 0 ou 1, et -1 si la case est vide
		bool getTileWall(int x, int y,int bit); // Renvoie l'id du player positionné en (x,y), 0 ou 1, et -1 si la case est vide
		bool isWallValid(int x, int y,int bit); // Renvoie l'id du player positionné en (x,y), 0 ou 1, et -1 si la case est vide
		void addOneWall(int x, int y, int bit) { getTile(x,y)->walls[bit]=true;}// Ajoute un mur sur UNE TILE
		void addWall(int x, int y, int bit); // Ajoute le mur sur les DEUX TILES mitoyennes concernées
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

#endif