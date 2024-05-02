#include <iostream>
#include <cstdio>
#include "board.hpp"

Board createBoard(int w, int h)
{
    assert
    int size = w*h;
    int * board = malloc(size*sizeof(int));

    int i;
    for(i=0; i<size; i++)
    {
        board[i] = 0;
    }
}

Board initGame(Board board)

void printBoard(Board board)

void printBoardHumanReadable(Board board)

void placeWall(int x, int y, int bit)

void movePlayer(int id, int bit)