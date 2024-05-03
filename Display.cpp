#include "Display.hpp"

void Grid::set(int taille,int largeur,int hauteur){
    taille_tile=taille;
    hlines =sf::VertexArray(sf::Lines, hauteur*2);
    vlines =sf::VertexArray(sf::Lines, largeur*2);
    int p=0;
    for(int i=0;i<largeur;i++){
        vlines[p].position = sf::Vector2f(i*taille_tile,0);
        vlines[p+1].position = sf::Vector2f(i*taille_tile, hauteur*taille_tile);
        p+=2;
    }
    p=0;
    for(int i=0;i<hauteur;i++){
        hlines[p].position = sf::Vector2f(0,i*taille_tile);
        hlines[p+1].position = sf::Vector2f(largeur*taille_tile, i*taille_tile);
        p+=2;
    }
}

Game::Game(int largeur,int hauteur){
    this->hauteur=hauteur;
    this->largeur=largeur;
    window.create(sf::VideoMode(largeur*taille_tile,hauteur*taille_tile),"JEUX",sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    grid.set(taille_tile,largeur,hauteur);
}

int Game::event(){
    sf::Event event;
    
    while (window.pollEvent(event))
    {
        if ( event.type == sf::Event::Closed){
            window.close();
            return 0;
        }
    }
    if (event.type == sf::Event::Resized) {
       window.setSize(sf::Vector2u(largeur*taille_tile,hauteur*taille_tile));
    }
    return 1;
}

void Game::display(){
    window.clear();
    window.draw(grid);

    window.display();

}