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

class Player: public sf::Drawable{
	private:
		int id;
		sf::Sprite sprite;
    sf::Texture texture;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {//pour faciliter le display 
            target.draw(sprite, states);
        }
	public:
		int x,y;//facile d'acces
		void set_coord(int x,int y){this->x=x;this->y=y;}
		void set_id(int id){this->id=id;}
		int get_id(){return id;}
		void set_sprite(string name){//pour le skin
			if (!texture.loadFromFile(name))cout<<"error de chargement du joueur"<<endl;
			else sprite.setTexture(texture);
		}
};


class Board{
  	private:
      vector<Tile *> board;
      Player p1,Robot;

	public:
    int width, height;
    Board(int width = WIDTH, int height = HEIGHT); // Initialise un board vide, de dimension WIDTH*HEIGHT
    int getPlayerPosition(int id); // Donne la position d'un joueur d'après son ID (0 ou 1)
    int getBoardW() {return width;} // Renvoie la largeur du board
    int getBoardH() {return height;} // Renvoie la hauteur du board
    bool isMovePossible(int x, int y, int bit);  // Renvoie si le move dirigé par le bit est possible depuis (x,y)
    bool isMovePossiblePlayer(int x, int y, Player* player);// Renvoie si le move dirigé par le bit est possible depuis (x,y)
    vector<int> possibleMoves(int x, int y);// Renvoie un vecteur contenant les bits de direction possibles pour un mouvement depuis (x,y)
    int getTileId(int x, int y) {return getTile(x, y)->player;}	 // Renvoie l'id du player positionné en (x,y), 0 ou 1, et -1 si la case est vide
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

#endif