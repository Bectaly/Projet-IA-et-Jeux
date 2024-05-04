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

Wall::Wall(int taille,int x,int y,int dir){
    rectangle.setFillColor(sf::Color::Red);
    if(Bit[dir].x!=0)rectangle.setSize(sf::Vector2f(10,taille));
    if(Bit[dir].y!=0)rectangle.setSize(sf::Vector2f(taille,10));
    int decal_x=0,decal_y=0;
    if(Bit[dir].x!=0){
        decal_x=Bit[dir].x*taille/2-5;
        decal_y=-taille/2;
    }
    if(Bit[dir].y!=0){
        decal_y=Bit[dir].y*taille/2-5;
        decal_x=-taille/2;
    }
    rectangle.setPosition(taille*x+decal_x+taille/2,taille*y+decal_y+taille/2 );
}

Game::Game(int largeur,int hauteur){
    //bit
    define_Bit();

    //init
    board =Board(largeur,hauteur);
    this->hauteur=hauteur;
    this->largeur=largeur;
    largeur_px=largeur*taille_tile;
    hauteur_px=hauteur*taille_tile;
    //init window
    window.create(sf::VideoMode(largeur_px,hauteur_px),"JEUX",sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    grid.set(taille_tile,largeur,hauteur);

    //init player
    p1.init(taille_tile,0,sf::Color::Red);
    p1.set_coord(0,hauteur/2);
    p1.updatePosition();
    board.setcoordplayers(p1.getCoord());

    robot.init(taille_tile,1,sf::Color::Green);
    robot.set_coord(largeur-,hauteur/2);
    robot.updatePosition();
    board.setcoordrobot(robot.getCoord());

    //init wall
    cout<<"la nbr barriere:"<<nbr_wall_max<<endl;
    walls.resize(nbr_wall_max,NULL);

}

int Game::calc_dir(int x,int y,double xx,double yy){
    double vectx=xx-x-1/2.0,vecty=yy-y-1/2.0;
    //cout<<" "<<x<<" "<<y<<" "<<xx<<" "<<yy<<" "<<vectx<<" "<<vecty<<endl;
    if(abs(vectx)>abs(vecty) && vectx>0) return 1;
    if(abs(vectx)>abs(vecty) && vectx<0) return 3;
    if(abs(vectx)<abs(vecty) && vecty>0) return 2;
    if(abs(vectx)<abs(vecty) && vecty<0) return 0;
    return -1;
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
       window.setSize(sf::Vector2u(largeur_px,hauteur_px));
    }
    if(event.type == sf::Event::MouseButtonPressed){
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            position=sf::Mouse::getPosition(window);
            x=position.x/taille_tile;
            y=position.y/taille_tile;
            if(board.getTileId(x,y)==-1 && board.isMovePossiblePlayer(x,y)){
                board.moveTo(x,y);
                p1.set_coord(x,y);
                p1.updatePosition();
            }
        }
        if (nbr_wall<nbr_wall_max && sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            position=sf::Mouse::getPosition(window);
            x=position.x/taille_tile;
            y=position.y/taille_tile;
            int dir=calc_dir(x,y,position.x/(double)taille_tile,position.y/(double)taille_tile);
            if(dir !=-1 && board.isWallValid(x,y,dir)){
                cout<<nbr_wall<<endl;
                walls[nbr_wall]=new Wall(taille_tile,x,y,dir);
                board.addWall(x,y,dir);
                nbr_wall++;
            }
        }
    }
    return 1;
}

void Game::display(){
    window.clear();
    window.draw(p1);
    window.draw(robot);
    window.draw(grid);
    for(int i=0;i<nbr_wall;i++){
        window.draw(*walls[i]);
    }
    

    window.display();

}

void Game::Run(){
    while(event()){display();}
}