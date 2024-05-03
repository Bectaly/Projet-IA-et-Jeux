#ifndef BOARD_H
#define BOARD_H

typedef struct z_tile
{
    bool up;
    bool right;
    bool down;
    bool left;
    bool p1;
    bool p2;
} Tile;

typedef Tile* Board;

Board createBoard(int w, int h)
Board initGame(Board board)

void printBoard(Board board)
void printBoardHumanReadable(Board board)

void placeWall(Board board, int x, int y, int bit)
void movePlayer(Board board, int id, int bit)

void getTileData(Board board, int x, int y)



#endif
