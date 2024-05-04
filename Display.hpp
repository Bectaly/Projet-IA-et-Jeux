#ifndef _DISPLAY_H
#define _DISPLAY_H 

#include "struct.hpp"

class Player: public sf::Drawable{
	private:
        int taille_tile;
		sf::CircleShape cercle;
		sf::Sprite sprite;
    	sf::Texture texture;
        Coord coord;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {//pour faciliter le display 
            target.draw(cercle, states);
        }
	public:
		void init(int taille_tile,int id,sf::Color color){
            coord.id=id;
            this->taille_tile=taille_tile;
            cercle.setFillColor(color);
            cercle.setRadius(taille_tile/3);
        }
        Coord getCoord(){return coord;}
        void set_coord(int x,int y){coord.set_coord(x,y);}
        void updatePosition() {cercle.setPosition(taille_tile * coord.x+taille_tile/6, taille_tile * coord.y+taille_tile/6);}
		void set_sprite(string name){//pour le skin
			if (!texture.loadFromFile(name))cout<<"error de chargement du joueur"<<endl;
			else sprite.setTexture(texture);
		}
};

class Grid: public sf::Drawable{
    private:
        sf::VertexArray hlines;
        sf::VertexArray vlines;
        int taille_tile;

    public:
        void set(int taille,int hauteur,int largeur);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(hlines, states);
            target.draw(vlines, states);
        }
};

class Wall: public sf::Drawable{
    private:
        sf::RectangleShape rectangle;
    public:
        Wall(int taille=0,int x=0,int y=0,int dir=0);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(rectangle, states);
        }
};

class Game{
    private:
        //window
        sf::RenderWindow window;
        sf::Vector2i position;
        Player p1,robot;
        Grid grid;
        int taille_tile=100;
        int largeur,hauteur;
        int largeur_px,hauteur_px;
        int x,y,nbr_wall=0,nbr_wall_max=10;
        Board board;
        vector<Wall*> walls;
        //function
        int calc_dir(int x,int y,double xx,double yy);
        int event();
        void display();

    public:
        Game(int largeur=5,int hauteur=10);
        void Run();
        
};

#endif 