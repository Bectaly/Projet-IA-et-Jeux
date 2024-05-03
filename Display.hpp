#ifndef _DISPLAY_H
#define _DISPLAY_H 

#include "struct.hpp"

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

class Game{
    private:
        sf::RenderWindow window;
        Grid grid;
        int taille_tile=100;
        int largeur,hauteur;

    public:
        Game(int largeur,int hauteur);
        int event();
        void display();
};

#endif 