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

Wall::Wall(int taille,int x,int y,int dir,sf::Color color){
    rectangle.setFillColor(color);
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

Wall::Wall(int taille,int x,int y,int dir,string name){
    if (texture.loadFromFile(name)){    
        sprite.setTexture(texture);
        size=texture.getSize();
        sprite.setScale((double)epaisseur/size.x,(double)taille/size.y);
        sp=true;
        if(Bit[dir].y!=0)sprite.setRotation(-90);
        int decal_x=0,decal_y=0;
        if(Bit[dir].x!=0){
            decal_x=Bit[dir].x*taille/2-epaisseur/2;
            decal_y=-taille/2;
        }
        if(Bit[dir].y!=0){
            decal_y=Bit[dir].y*taille/2+epaisseur/2;
            decal_x=-taille/2;
        }
        sprite.setPosition(taille*x+decal_x+taille/2,taille*y+decal_y+taille/2);
    }
}


void Player::init(int taille_tile,int id,sf::Color color){
    this->id=id;
    this->taille_tile=taille_tile;
    cercle.setFillColor(color);
    cercle.setRadius(taille_tile/3);
}

void Player::init(int taille_tile,int id,string name){
    this->id=id;
    this->taille_tile=taille_tile;
    if (texture.loadFromFile(name)){    
        sprite.setTexture(texture);
        size=texture.getSize();
        sprite.setScale((double)taille_tile/size.x,(double)taille_tile/size.y);
        sp=true;
    }
}

void Player::set_coord(int x,int y){
    coord.set_coord(x,y);
}

void Player::moveDir(int bit){
    coord.set_coord(coord.x+Bit[bit].x,coord.y+Bit[bit].y);
}

void Player::updatePosition() {
    if(!sp)cercle.setPosition(taille_tile * coord.x+taille_tile/6, taille_tile * coord.y+taille_tile/6);
    else sprite.setPosition(taille_tile * coord.x, taille_tile * coord.y);
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
    p1.init(taille_tile,0,"p1.png");
    p1.set_coord(0,hauteur/2);
    p1.updatePosition();
    board.setcoord(p1.getCoord(),0);

    robot.init(taille_tile,1,"robot.png");
    robot.set_coord(largeur-1,hauteur/2);
    robot.updatePosition();
    board.setcoord(robot.getCoord(),1);

    //init wall
    walls.resize(nbr_wall_max,NULL);

}

int Game::calc_dir(int x,int y,double xx,double yy){
    double vectx=xx-x-1/2.0,vecty=yy-y-1/2.0;
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
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            position=sf::Mouse::getPosition(window);
            Coord c=p1.getCoord();
            int dir=calc_dir(c.x,c.y,position.x/(double)taille_tile,position.y/(double)taille_tile);
            if(board.isMovePossiblePlayerDir(dir,p1.id)){
                board.moveDir(dir,p1.id);
                p1.moveDir(dir);
                p1.updatePosition();
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            position=sf::Mouse::getPosition(window);
            x=position.x/taille_tile;
            y=position.y/taille_tile;
            int dir=calc_dir(x,y,position.x/(double)taille_tile,position.y/(double)taille_tile);
            if(dir !=-1 && p1.nbr_wall<nbr_wall_max && board.isWallValid(x,y,dir)){
                walls[nbr_wall]=new Wall(taille_tile,x,y,dir,"wall.png");
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