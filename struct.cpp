#include "struct.hpp"

vector<sf::Vector2i> Bit(4);

void define_Bit(){
	Bit[0].x=0;
	Bit[0].y=-1;
	Bit[1].x=1;
	Bit[1].y=0;
	Bit[2].x=0;
	Bit[2].y=1;
	Bit[3].x=-1;
	Bit[3].y=0;	
}

void Board::setPlayer(Coord p1,int id,int nbr_wall){
	player[id]=p1;
	getTile(p1.x,p1.y)->player=id;
	finishingline[1-id]=p1.x;
	remainingwall[id]=nbr_wall;
}

void Board::Set(int width, int height) { // Initialise un board vide, de dimension WIDTH*HEIGHT
	this->width = width;
	this->height = height;
	board.resize(width*height);
	player.resize(2);
	
	
	for(int i=0; i<width*height; i++){
		Tile * t = new Tile;
		t->walls.resize(4, false);
		board[i] = t;
	}
}

Coord Board::getPlayerPosition(int id){ return player[id];}

void Board::copy(Board *b){
	Tile* t1,*t2;
	player[0]=b->getPlayerPosition(0);
	player[1]=b->getPlayerPosition(1);
	finishingline[0]=b->getFinishingLine(0);
	finishingline[1]=b->getFinishingLine(1);
	remainingwall[0]=b->getRemainingWall(0);
	remainingwall[1]=b->getRemainingWall(1);
	setDistance(2,b->getDistance(0));
	setDistance(3,b->getDistance(1));

	for(int x=0;x<width;x++){
		for(int y=0;y<height;y++){
			t1=getTile(x,y);
			t2=b->getTile(x,y);
			t1->player=t2->player;
			t1->walls=t2->walls;
		}
	}
}

bool Board::isMovePossible(int x, int y, int bit) { // Renvoie si le move dirigé par le bit est possible depuis (x,y)
	bool b = false;
	
	if(bit==0 && y==0) b=true; // La case ciblée est-elle en dehors du board ?
	else if (bit==1 && x==width) b=true;
	else if (bit==2 && y==height) b=true;
	else if (bit==3 && x==0) b=true;
	
	if(b)
	{
		cout << "error in isMovePossible: target out of board" << endl;
		return false;
	}

	if(bit==0 && getTile(x, y-1)->player!=-1) return false; // La case ciblée est-elle occupée ?
	else if(bit==1 && getTile(x+1, y)->player!=-1) return false;
	else if(bit==2 && getTile(x, y+1)->player!=-1) return false;
	else if(bit==3 && getTile(x-1, y)->player!=-1) return false;

	return !(getTile(x, y)->walls[bit]);
}

bool Board::isMovePossiblePlayer(int x, int y,int id) { // Renvoie si pos (x,y) a porter de player
	if(!(x>=0 && x<width && y>=0 && y<height)) return false;
	if(getTileId(x,y)!=-1)return false;
	Tile * t=getTile(x,y);
	for(int i=0;i<4;i++){
		int bx=Bit[i].x,by=Bit[i].y;
		if(x+bx>=0 && x+bx<width && y+by>=0  && y+by<height && getTileId(x+bx, y+by)==id && !t->walls[i]) return true;
	}
	return false;
}

bool Board::isMovePossiblePlayerDir(int bit,int id) {
	int x=player[id].x+Bit[bit].x, y=player[id].y+Bit[bit].y;
	if(!(x>=0 && x<width && y>=0 && y<height)) return false;
	//cout<<x<<" "<<y<<endl;
	if(getTileId(x,y)!=-1 && !getTile(x,y)->walls[bit]){
		//cout<<x<<" "<<y<<endl;
		x=x+Bit[bit].x;
		y=y+Bit[bit].y;
		if((x>=0 && x<width && y>=0 && y<height) && getTileId(x,y)==-1)return true;
		return false;
	}

	return !(getTile(player[id].x, player[id].y)->walls[bit]);
}

void Board::moveTo(int x,int y,int id){
	getTile(player[id].x,player[id].y)->player=-1;
	getTile(x,y)->player=id;
	player[id].setCoord(x,y);
}	

int Board::moveDir(int bit,int id){
	int x=player[id].x,y=player[id].y,valx=Bit[bit].x,valy=Bit[bit].y;
	if(getTileId(x+valx,y+valy)!=-1){
		moveTo(x+valx+valx,y+valy+valy,id);
		return 2;
	}
	else{
		moveTo(x+valx,y+valy,id);
		return 1;
	}
	
}	

vector<int> Board::possibleMoves(int x, int y) { // Renvoie un vecteur contenant les bits de direction possibles pour un mouvement depuis (x,y)
	vector<int> moves;
	int k = 1;
	for(int bit=0; bit<4; bit++) {
		if(isMovePossible(x, y, bit)) {
			moves.resize(k);
			moves[k-1] = bit;
			k++;
			
		}
	}
	return moves;
}

bool Board::getTileWall(int x, int y,int bit) {
	return getTile(x, y)->walls[bit];
}

bool Board::isWallValid(int x, int y,int bit){
	if(!(x+Bit[bit].x>=0 && x+Bit[bit].x<width && y+Bit[bit].y>=0 && y+Bit[bit].y<height)) return false;
	if(!(x+Bit[(bit%2)+1].x>=0 && x+Bit[(bit%2)+1].x<width && y+Bit[(bit%2)+1].y>=0 && y+Bit[(bit%2)+1].y<height)) return false;
	if(!(x+Bit[bit].x+Bit[(bit%2)+1].x>=0 && x+Bit[bit].x+Bit[(bit%2)+1].x<width && y+Bit[bit].y+Bit[(bit%2)+1].y>=0 && y+Bit[bit].y+Bit[(bit%2)+1].y<height)) return false;
	return !(getTileWall(x,y,bit) || getTileWall(x+Bit[(bit%2)+1].x,y+Bit[(bit%2)+1].y,bit));
}

void Board::addWall(int x, int y, int bit) { // Ajoute le mur sur les TILES mitoyennes concernées
	addOneWall(x, y, bit);
	addOneWall(x+Bit[bit].x,y+Bit[bit].y,(bit+2)%4);
	addOneWall(x+Bit[(bit%2)+1].x, y+Bit[(bit%2)+1].y, bit);
	addOneWall(x+Bit[bit].x+Bit[(bit%2)+1].x,y+Bit[bit].y+Bit[(bit%2)+1].y,(bit+2)%4);
}

string conv(int val){
    if(val==-1)return " 0";
    if(val==0)return "P1";
    if(val==1)return "IA";
    return "  ";
}

void printBoard(Board& b){
    for(int y=0;y<b.height;y++){
        cout<<"[ "<<conv(b.getTile(0,y)->player)<<" "<<ends;
        for(int x=1;x<b.width;x++){
            cout<<conv(b.getTile(x,y)->player)<<" "<<ends;
        }
        cout<<"]"<<endl;
    }
    cout<<endl;
    }

void printBoardWall(Board& b,int bit){
    for(int y=0;y<b.height;y++){
        cout<<"[ "<<b.getTile(0,y)->walls[bit]<<" "<<ends;
        for(int x=1;x<b.width;x++){
            cout<<b.getTile(x,y)->walls[bit]<<" "<<ends;
        }
        cout<<"]"<<endl;
    }
    cout<<endl;
}