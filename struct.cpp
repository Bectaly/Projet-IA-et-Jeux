#include "struct.hpp"

Board::Board(int width = WIDTH, int height = HEIGHT) { // Initialise un board vide, de dimension WIDTH*HEIGHT
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

void Board::set_Player_Pos(Player p){

}

bool isMovePossible(int x, int y, int bit) { // Renvoie si le move dirigé par le bit est possible depuis (x,y)
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

bool Board::isMovePossiblePlayer(int x, int y,int id) { // Renvoie si le move dirigé par le bit est possible depuis (x,y)
Tile * t=getTile(x,y);
if(y-1>=0 && getTileId(x, y-1)==id && !t->walls[2]) return true;
	else if(x-1>=0 && getTileId(x-1, y)==id && !t->walls[1]) return true;
	else if(x+1>=0 && getTileId(x+1, y)==id && !t->walls[3]) return true;
	else if(y+1>=0 && getTileId(x, y+1)==id && !t->walls[0]) return true;
return false;
}

void Board::movePlayer(int x,int y){
getTile(p1.x,p1.y)->player=-1;
getTile(x,y)->player=p1.get_id();
p1.set_coord(x,y);
}

vector<int> Board::possibleMoves(int x, int y) { // Renvoie un vecteur contenant les bits de direction possibles pour un mouvement depuis (x,y)
	vector<int> moves;
	int k = 1;
	
	for(int bit=0; bit<4; bit++) {
		if(isMovePossible(x, y, bit)) {
			moves.resize(k);
			vector[k-1] = bit;
			k++;
		}
	}

	return moves;
}

void Board::addWall(int x, int y, int bit) { // Ajoute le mur sur les DEUX TILES mitoyennes concernées
	addOneWall(x, y, bit);

	if (bit==0) addOneWall(x, y-1, 2);
	else if (bit==1) addOneWall(x+1, y, 3);
	else if (bit==2) addOneWall(x, y+1, 0);
	else if (bit==3) addOneWall(x-1, y, 1);
}