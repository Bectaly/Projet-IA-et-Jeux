#include "struct.hpp"

vector<Couple> Bit(4);

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


Board::Board(int width, int height) { // Initialise un board vide, de dimension WIDTH*HEIGHT
	this->width = width;
	this->height = height;
	board.resize(width*height);
	for(int i=0; i<width*height; i++)
	{
		Tile * t = new Tile;
		t->walls.resize(4, false);
		board[i] = t;
	}
}

//void Board::set_Player_Pos(Player p){}

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

bool Board::isMovePossiblePlayer(int x, int y) { // Renvoie si pos (x,y) a porter de player
	if(getTileId(x,y)!=-1)return false;
	Tile * t=getTile(x,y);
	for(int i=0;i<4;i++){
		int bx=Bit[i].x,by=Bit[i].y;
		if(x+bx>=0 && x+bx<width && y+by>=0  && y+by<height && getTileId(x+bx, y+by)==p1.id && !t->walls[(i+2)%4]) return true;
	}
	return false;
}

void Board::moveTo(int x,int y){
	getTile(p1.x,p1.y)->player=-1;
	getTile(x,y)->player=p1.id;
	p1.set_coord(x,y);
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
	if(x+Bit[bit].x<0 && bit==3)return false;
	if(x+Bit[bit].x>=width && bit==1)return false;
	if(y+Bit[bit].y<0 && bit==0)return false;
	if(y+Bit[bit].y>=height && bit==2)return false;
	return !getTileWall(x,y,bit);
}

void Board::addWall(int x, int y, int bit) { // Ajoute le mur sur les DEUX TILES mitoyennes concernées
	addOneWall(x, y, bit);
	addOneWall(x+Bit[bit].x,y+Bit[bit].y,(bit+2)%4);
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