#ifndef _DISPLAY_H
#define _DISPLAY_H 

#include "struct.hpp"

class Player: public sf::Drawable{
	private:
        int taille_tile;
        sf::Vector2u size;
        bool sp=false;
		sf::CircleShape cercle;
		sf::Sprite sprite;
    	sf::Texture texture;
        Coord coord;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {//pour faciliter le display 
            if(!sp)target.draw(cercle, states);
            else target.draw(sprite, states);
        }
	public:
        int id,nbr_wall;
		void init(int taille_tile,int id,string name);
		void init(int taille_tile,int id,sf::Color color);
        Coord getCoord(){return coord;}
        void set_coord(int x,int y);
        void moveDir(int bit);
        void updatePosition();
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
        int epaisseur=15;
        sf::RectangleShape rectangle;
        sf::Vector2u size;
        bool sp=false;
        sf::Sprite sprite;
    	sf::Texture texture;
    public:
        Wall(int taille=0,int x=0,int y=0,int dir=0,string name="");
        Wall(int taille=0,int x=0,int y=0,int dir=0,sf::Color color=sf::Color::Red);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            if(!sp)target.draw(rectangle, states);
            else target.draw(sprite, states);
        }
};

class Game{
    private:
        //window
        sf::RenderWindow window;
        sf::Vector2i position;
        //player 
        Player p1,robot;
        int p1_id=0,robot_id=1;
        //grille
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