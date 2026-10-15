#include <iostream>
#include "pieces.h"

Piece::Piece(char piecesymbol, PieceColor piececolor){
    pieceSymbol = piecesymbol;
    pieceColor = piececolor;
}

bool Pawn::isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece){
    if (pieceColor == PieceColor::WHITE){
        bool doubleMove = (startX == 1 && endX == 3 && startY == endY && targetPiece == nullptr);
        bool normalMove = (startY == endY && (endX == startX +1) && targetPiece == nullptr);
        
        bool captureMove = (endX == startX +1 && ((endY == startY +1)||(endY == startY -1))&& targetPiece != nullptr);

        return doubleMove || normalMove || captureMove;

    }
   
    if (pieceColor == PieceColor:: BLACK){

        bool doubleMove = (startX == 6 && endX == 4 && startY == endY && targetPiece == nullptr);
        bool normalMove = (startY == endY && (endX == startX -1) && targetPiece == nullptr);
        
        bool captureMove = (endX == startX -1 && ((endY == startY +1)||(endY == startY -1))&& targetPiece != nullptr);

        return doubleMove || normalMove || captureMove;

    }

    return false;
}


bool Rook::isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece){
    return ((startY == endY)|| (startX == endX));
}   


bool Knight::isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece){
    // horizontal
    if ((endX == startX -2)||(endX == startX +2)){
        return ((endY == startY -1)|| (endY == startY +1));
    }

    //vertical
    if ((endY == startY-2)||(endY == startY +2)){
        return ((endX == startX -1)|| (endX== startX +1));
    }
    return false;
}


bool Bishop::isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece){
    return (abs(endX-startX) == abs(endY - startY));
}


bool Queen::isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece){

    return ((startY == endY) || (startX == endX)) || (abs(endX - startX) == abs(endY - startY));
}


bool King::isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece){
    if (abs(endX - startX) <= 1 && abs(endY - startY) <= 1){
        return true;
    }

    if (abs(endX - startX) == 0 && abs(endY - startY) == 2 && !pieceMoved()) {
        return true;
    }

    return false;
}
