#ifndef _DISPLAY_H
#define _DISPLAY_H 

#include "ia.hpp"

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
        void setCoord(int x,int y);
        void moveDir(int bit,int saute=1);
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

class Fond: public sf::Drawable{
    private:
        sf::Texture back;
        sf::Sprite background;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(background, states);
        }

    public:
        void set(string name,int largeur,int hauteur);

};

class Texte: public sf::Drawable{
    private:
        sf::Text text;
        sf::Color color;
        int xx,yy;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(text, states);
        }

    public:
        void set(string str, sf::Font& font,int z,int x,int y);
        void set_text(string tex);
};

class Game{
    private:
        //window
        sf::RenderWindow window;
        sf::Vector2i position;
        Fond F_jeu;
        //texte
        int T_size=30;
        Texte T_IA,T_Pl,T_fini;

        //player 
        Player p1,robot;
        int p1_id=0,robot_id=1,difi;
        bool tour=false,finish=false;
        //grille
        Grid grid;
        int taille_tile=100;
        int largeur,hauteur;
        int largeur_px,hauteur_px;
        int x,y,nbr_wall_poser=0,nbr_wall_ini;
        Board board;
        vector<Wall*> walls;
        //function
        void verif(int id);
        void actionIA();
        int calc_dir(int x,int y,double xx,double yy);
        int event();
        void display();
        void displayFini(int id);

    public:
        void set(sf::Font& font,int largeur=5,int hauteur=10,int nbr_wall=5,int difi=3);
        void Run();
        void Delete();
};

class Bouton : public sf::Drawable {
    private:
        sf::Text text;
        sf::RectangleShape rec;
        sf::Color cool;
        sf::Color surcool;
        sf::Color select;
        static int cocher;
        int id;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(rec, states);
            target.draw(text, states);
        }

    public:
        Bouton();
        void setId(int id=-2);
        int getCocher();
        void set_bouton(const std::string& str, sf::Font& font, int largeur, int hauteur, float x, float y);
        void set_fleche(const std::string& str, sf::Font& font, int size, float x, float y);
        bool isHover(const sf::RenderWindow& window);
        bool isClick(const sf::RenderWindow& window,bool o=false);
        void update(const sf::RenderWindow& window);
};



class Menu {
    private:
        sf::RenderWindow window;
        sf::VideoMode fenetre;

        Fond FondMenu,FondOption;

        Game* g;
        int largeurmenu;
        int hauteurmenu;
        int taille_fleche=40;
        int hauteur_bouton=50;
        int largeur_bouton=200;
        bool option=false;
        sf::Font font;

        //pour le menu
        Texte T_Titre_Jeu;
        Bouton playButton,optionsButton,quitButton;

        //pour les param
        Bouton flecheup,flechedown,retourButton;
        Bouton B_Largeur,B_Hauteur,B_nbrMur,B_dific;
        Texte T_Titre_Params,T_Largeur,T_Hauteur,T_nbrMur,T_dific;
        

        int largeur=5,hauteur=5,nbrMur=int(0.07*(2*largeur*hauteur-hauteur-largeur)),dific=3;
        void updateOption();
        void isClickiOption();
        void updateMenu();
        void isClickiMenu();
        void creerwindow();
        void displayMenu();
        void displayOption();
    public:
        Menu(int largeurmenu=800, int hauteurmenu=600);
        int start();
};

#endif 