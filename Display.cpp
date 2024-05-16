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
        sprite.setScale((double)epaisseur/size.x,(double)taille*2/size.y);
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

void Player::setCoord(int x,int y){
    coord.setCoord(x,y);
}

void Player::moveDir(int bit){
    coord.setCoord(coord.x+Bit[bit].x,coord.y+Bit[bit].y);
}

void Player::updatePosition() {
    if(!sp)cercle.setPosition(taille_tile * coord.x+taille_tile/6, taille_tile * coord.y+taille_tile/6);
    else sprite.setPosition(taille_tile * coord.x, taille_tile * coord.y);
}















void Game::Delete(){
    board.Delete();
    for(auto& wall:walls){
        delete wall;
    }
    
}

void Game::set(int largeur,int hauteur,int nbr_wall,int difi){
    //bit
    define_Bit();
    //init
    board.Set(largeur,hauteur);
    this->hauteur=hauteur;
    this->largeur=largeur;
    this->difi=difi;
    nbr_wall_ini=nbr_wall;

    largeur_px=largeur*taille_tile;
    hauteur_px=hauteur*taille_tile;
    //init window
    window.create(sf::VideoMode(largeur_px,hauteur_px),"Quoridor",sf::Style::Titlebar | sf::Style::Close);
    sf::VideoMode fenetre = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i((fenetre.width - largeur_px) / 2, (fenetre.height - hauteur_px) / 2-90));
    window.setFramerateLimit(60);
    grid.set(taille_tile,largeur,hauteur);

    //init player
    p1.init(taille_tile,0,"./image/p1.png");
    p1.setCoord(0,hauteur/2);
    p1.updatePosition();
    board.setPlayer(p1.getCoord(),0,nbr_wall_ini);
    
    robot.init(taille_tile,1,"./image/robot.png");
    robot.setCoord(largeur-1,hauteur/2);
    robot.updatePosition();
    board.setPlayer(robot.getCoord(),1,nbr_wall_ini);

    board.setDistance(0,largeur);
    board.setDistance(1,largeur);

    //init wall
    walls.resize(nbr_wall_ini*2,NULL);

}

void Game::verif(int id){
    if(evaluateBoardId(&board,id)){
        finish=true;
    }
}

int Game::calc_dir(int x,int y,double xx,double yy){
    double vectx=xx-x-1/2.0,vecty=yy-y-1/2.0;
    if(abs(vectx)>abs(vecty) && vectx>0) return 1;
    if(abs(vectx)>abs(vecty) && vectx<0) return 3;
    if(abs(vectx)<abs(vecty) && vecty>0) return 2;
    if(abs(vectx)<abs(vecty) && vecty<0) return 0;
    
    return -1;
}

void Game::actionIA(){
    if(tour){
        
        Action * tmp=negamax(&board,difi);
        if(tmp!=NULL){ 
            tour=false;
            if(tmp->move){
                board.moveDir(tmp->dir,1);
                robot.moveDir(tmp->dir);
                robot.updatePosition();
            }
            else{
                walls[nbr_wall_poser]=new Wall(taille_tile,tmp->coord.x,tmp->coord.y,tmp->dir,"./image/wall.png");
                board.addWall(tmp->coord.x,tmp->coord.y,tmp->dir);
                board.subWall(1);
                nbr_wall_poser++;
            }
            verif(1);
        }
        else cout<<"erreur"<<endl;
    }
}

int Game::event(){
    sf::Event event;
    while (window.pollEvent(event))
    {
        if ( event.type == sf::Event::Closed || finish){
            window.close();

            return 0;
        }
    }
    if (event.type == sf::Event::Resized) {
       window.setSize(sf::Vector2u(largeur_px,hauteur_px));
    }
    
    actionIA();
    if(event.type == sf::Event::MouseButtonPressed){
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            position=sf::Mouse::getPosition(window);
            Coord c=p1.getCoord();
            x=position.x/taille_tile;
            y=position.y/taille_tile;
            if(!(c.x==x && c.y==y)){
                int dir=calc_dir(c.x,c.y,position.x/(double)taille_tile,position.y/(double)taille_tile);
                if(board.isMovePossiblePlayerDir(dir,p1.id)){
                    board.moveDir(dir,p1.id);
                    p1.moveDir(dir);
                    p1.updatePosition();
                    verif(0);
                    tour=true;
                }
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && board.getRemainingWall(0)>0){
            position=sf::Mouse::getPosition(window);
            x=position.x/taille_tile;
            y=position.y/taille_tile;
            int dir=calc_dir(x,y,position.x/(double)taille_tile,position.y/(double)taille_tile);
            if(dir !=-1 && board.isWallValid(x,y,dir)){
                Board* test;
                test=getChildBoardActionWallDir(&board,x,y,dir,0);
                if(test!=NULL){
                    test->Delete();
                    delete test;
                    walls[nbr_wall_poser]=new Wall(taille_tile,x,y,dir,"./image/wall.png");
                    board.subWall(0);
                    board.addWall(x,y,dir);
                    nbr_wall_poser++;
                    tour=true;
                }
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
    for(int i=0;i<nbr_wall_poser;i++){
        window.draw(*walls[i]);
    }
    window.display();
}

void Game::Run(){
    while(event()){display();}
}

























void Fond::set(string name,int largeur,int hauteur){
    if(back.loadFromFile(name)){
        background.setTexture(back);
        background.setScale(largeur / background.getLocalBounds().width,hauteur / background.getLocalBounds().height);
    }
}




void Texte::set(string str, sf::Font& font,int z,int x,int y){
    text.setString(str);
    text.setFont(font);
    text.setCharacterSize(z);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(z/15);
    text.setStyle(sf::Text::Bold);
    xx=x;yy=y;
    text.setPosition(x - text.getLocalBounds().width/2, y - text.getLocalBounds().height/2 - 10);
}

void Texte::set_text(string tex){
    text.setString(tex);
    text.setPosition(xx - text.getLocalBounds().width/2, yy - text.getLocalBounds().height/2 - 10);
}









int Bouton::cocher = -1;

Bouton::Bouton(){
    cool=sf::Color(200,200,200);
    surcool=sf::Color(100,200,200);
    select=sf::Color(100,200,100);
    id=-2;
}

void Bouton::setId(int id){
    this->id=id;
}

int Bouton::getCocher(){
    return int(cocher);
}

void Bouton::set_bouton(const std::string& str, sf::Font& font, int largeur, int hauteur, float x, float y) {
    rec.setPosition(x-largeur/2, y-hauteur/2);
    rec.setSize(sf::Vector2f(largeur, hauteur));
    rec.setOutlineColor(sf::Color::Blue);
    rec.setOutlineThickness(2);
    rec.setFillColor(cool);
    
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(hauteur / 1.5);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x - text.getLocalBounds().width/2, y - text.getLocalBounds().height/2 - 10);
}

void Bouton::set_fleche(const std::string& str, sf::Font& font, int size, float x, float y) {
    rec.setPosition(x-size/2, y-size/2);  
    rec.setSize(sf::Vector2f(size, size));
    rec.setOutlineColor(sf::Color::Blue);
    rec.setOutlineThickness(2);
    rec.setFillColor(cool);
    
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size*1.75);
    text.setFillColor(sf::Color::Red);
    text.setPosition(x -int(size/1.6)-size/2 , y+size/2);
    text.rotate(-90);
}

bool Bouton::isHover(const sf::RenderWindow& window) {
    sf::Vector2i pos = sf::Mouse::getPosition(window);
    return rec.getGlobalBounds().contains(static_cast<float>(pos.x), static_cast<float>(pos.y));
}

bool Bouton::isClick(const sf::RenderWindow& window,bool o) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isHover(window)){
        while(sf::Mouse::isButtonPressed(sf::Mouse::Left) && isHover(window));
        if(o && cocher != id)cocher=id;
        else if(o && cocher == id)cocher=-1;
        return true;
    }
    return false;
}

void Bouton::update(const sf::RenderWindow& window) {
    if(cocher==id) rec.setFillColor(select);
    else if (isHover(window)) rec.setFillColor(surcool);
    else rec.setFillColor(cool);
}





Menu::Menu() {
    fenetre = sf::VideoMode::getDesktopMode();
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Erreur de chargement" << std::endl;
    } else {

        //ajout des fond
        FondMenu.set("./image/menu.jpg",largeurmenu,hauteurmenu);
        FondOption.set("./image/option.jpg",largeurmenu,hauteurmenu);

        //placement du Menu
        T_Titre_Jeu.set("QUORIDOR",font,70,largeurmenu/2,60);
        playButton.set_bouton("Jouer", font, largeur_bouton, hauteur_bouton, largeurmenu/2, hauteurmenu/2-2*hauteur_bouton);
        optionsButton.set_bouton("Options", font, largeur_bouton, hauteur_bouton, largeurmenu/2, hauteurmenu/2);
        quitButton.set_bouton("Quitter", font, largeur_bouton, hauteur_bouton, largeurmenu/2, hauteurmenu/2+2*hauteur_bouton);

        //placement des fleches
        T_Titre_Params.set("OPTIONS",font,70,largeurmenu/2,60);
        retourButton.set_bouton("Retour", font, largeur_bouton, hauteur_bouton, 110, hauteurmenu-35);
        B_Largeur.set_bouton("Largeur",font,largeur_bouton,hauteur_bouton,largeurmenu/5,hauteurmenu/4);
        B_Hauteur.set_bouton("Hauteur",font,largeur_bouton,hauteur_bouton,largeurmenu/5,int(hauteurmenu/4*2.5));
        B_nbrMur.set_bouton("Nb de murs",font,largeur_bouton,hauteur_bouton,largeurmenu/5*4,hauteurmenu/4);
        B_dific.set_bouton("Difficulte",font,largeur_bouton,hauteur_bouton,largeurmenu/5*4,int(hauteurmenu/4*2.5));

        T_Largeur.set(to_string(largeur),font,hauteur_bouton-5,largeurmenu/5,hauteurmenu/4+hauteur_bouton);
        T_Hauteur.set(to_string(hauteur),font,hauteur_bouton-5,largeurmenu/5,int(hauteurmenu/4*2.5)+hauteur_bouton);
        T_nbrMur.set(to_string(nbrMur),font,hauteur_bouton-5,largeurmenu/5*4,hauteurmenu/4+hauteur_bouton);
        T_dific.set(to_string(dific),font,hauteur_bouton-5,largeurmenu/5*4,int(hauteurmenu/4*2.5+hauteur_bouton));

        B_Largeur.setId(0);
        B_Hauteur.setId(1);
        B_nbrMur.setId(2);
        B_dific.setId(3);
        
        flecheup.set_fleche(">",font,taille_fleche,largeurmenu/2,hauteurmenu/2-taille_fleche);
        flechedown.set_fleche("<",font,taille_fleche,largeurmenu/2,hauteurmenu/2+taille_fleche);

    }
}

void Menu::creerwindow() {
    window.create(sf::VideoMode(largeurmenu, hauteurmenu), "Menu Quoridor",sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(sf::Vector2i((fenetre.width - largeurmenu) / 2, (fenetre.height - hauteurmenu) / 2));
    window.setFramerateLimit(60);
    sf::Mouse::setPosition(sf::Vector2i(0,0));
}

void Menu::displayMenu() {
    window.clear();

    //affiche style
    window.draw(FondMenu);
    window.draw(T_Titre_Jeu);
    //affiche bouton
    window.draw(playButton);
    window.draw(optionsButton);
    window.draw(quitButton);

    window.display();
}

void Menu::displayOption() {
    window.clear();

    //affiche style
    window.draw(FondOption);
    window.draw(T_Titre_Params);
    //affiche bouton
    window.draw(B_Largeur);
    window.draw(B_Hauteur);
    window.draw(B_nbrMur);
    window.draw(B_dific);
    //affiche texte
    window.draw(T_Hauteur);
    window.draw(T_Largeur);
    window.draw(T_nbrMur);
    window.draw(T_dific);
    //affiche fleche
    window.draw(flecheup);
    window.draw(flechedown);
    window.draw(retourButton);

    window.display();
}

void Menu::isClickiMenu(){
    if (playButton.isClick(window)) {
        window.close();
        g=new Game();
        g->set(largeur, hauteur, nbrMur, dific);
        g->Run();
        g->Delete();
        delete g;
        creerwindow();
    } else if (optionsButton.isClick(window)) {
        option = true;
    } else if (quitButton.isClick(window)) {
        window.close();
    }
}

void Menu::updateMenu(){
    playButton.update(window);
    optionsButton.update(window);
    quitButton.update(window);
}

void Menu::isClickiOption(){
    if (retourButton.isClick(window)) {
        option = false;
    }else if (B_Largeur.isClick(window,true)){}
    else if (B_Hauteur.isClick(window,true)){}
    else if (B_nbrMur.isClick(window,true)){}
    else if (B_dific.isClick(window,true)){}
    else if (flecheup.isClick(window)){
        int val=B_dific.getCocher();
        if(val==0){largeur+=2;T_Largeur.set_text(to_string(largeur));}
        if(val==1){hauteur+=2;T_Hauteur.set_text(to_string(hauteur));}
        if(val==2){nbrMur++;T_nbrMur.set_text(to_string(nbrMur));}
        if(val==3){dific++;T_dific.set_text(to_string(dific));}

    }
    else if (flechedown.isClick(window)){
        int val=B_dific.getCocher();
        if(val==0 && largeur>3){largeur-=2;T_Largeur.set_text(to_string(largeur));}
        if(val==1 && hauteur>3){hauteur-=2;T_Hauteur.set_text(to_string(hauteur));}
        if(val==2 && nbrMur>0){nbrMur--;T_nbrMur.set_text(to_string(nbrMur));}
        if(val==3 && dific>1){dific--;T_dific.set_text(to_string(dific));}
    }
}

void Menu::updateOption(){
    B_Largeur.update(window);
    B_Hauteur.update(window);
    B_nbrMur.update(window);
    B_dific.update(window);
    retourButton.update(window);
}

int Menu::start() {
    creerwindow();
    option=false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        if (event.type == sf::Event::Resized) {
        window.setSize(sf::Vector2u(largeurmenu,hauteurmenu));
        }
        if (!option) {
            updateMenu();
            isClickiMenu();
            displayMenu();
        } else {
            isClickiOption();
            updateOption();
            displayOption();
        }
    }
    return 0;
}