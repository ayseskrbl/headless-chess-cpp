#pragma once
#include "pieces.h"
#include <iostream>
#include <memory>
#include <utility>

using namespace std;

enum Turn{
    WHITE,
    BLACK
};

enum GameStatus{
    ONGOING,
    WHITE_WIN,
    BLACK_WIN,
    TIE
};

class Board{
    private:
        unique_ptr<Piece> grid[8][8];
        pair<int,int> kingPosition(Turn turn);
        bool isGameOver = false;
    public:
        int enPassantX,enPassantY = -1;

        Turn currentTurn = Turn::WHITE;
        GameStatus currentStatus = GameStatus::ONGOING;

        void cleanBoard();
        void setBoard();
        void showBoard();
        void movePiece(int startX, int startY, int endX, int endY,char prom = 'Q');
        bool isPathClear(int startX, int startY, int endX, int endY);
        bool isCheck(Turn turn);
        bool simulateMoveandCheck(int startX, int startY, int endX, int endY);
        bool hasLegalMoves();
        void perftDivide(int depth);
        long long perft(int depth);
};

