#pragma once
#include <iostream>

enum class PieceColor{
    WHITE,
    BLACK,
    NONE
};

class Piece{
    protected:
        char pieceSymbol;
        PieceColor pieceColor;
        bool isMoved = false;

    public:
        Piece(char pieceSymbol, PieceColor pieceColor);
        
        char getSymbol(){
            return pieceSymbol;
        }
        PieceColor getColor(){
            return pieceColor;
        }
        bool pieceMoved(){
            return isMoved;
        }
        void setMove(){
            isMoved = true;
        }
        
        virtual bool isValidMove(int startX, int startY, int endX, int endY,Piece * targetPiece) { return true; }
};

class Rook : public Piece{
    public:
        Rook(PieceColor pieceColor) : Piece(' ', pieceColor){
            if (pieceColor == PieceColor::WHITE){
                pieceSymbol = 'R';
            }
            else{
                pieceSymbol = 'r';
            }
        }
        bool isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece) override;
};

class Knight : public Piece{
    public:
        Knight(PieceColor pieceColor) : Piece(' ', pieceColor){
                if (pieceColor == PieceColor::WHITE){
                    pieceSymbol = 'N';
                }
                else{
                    pieceSymbol = 'n';
                }
            }
        bool isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece) override;
    
};
class Bishop : public Piece{
    public:
        Bishop(PieceColor pieceColor) : Piece(' ', pieceColor){
                    if (pieceColor == PieceColor::WHITE){
                        pieceSymbol = 'B';
                    }
                    else{
                        pieceSymbol = 'b';
                    }
                }
        bool isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece) override;
};


class King : public Piece{
    public:
        King(PieceColor pieceColor) : Piece(' ', pieceColor){
                if (pieceColor == PieceColor::WHITE){
                    pieceSymbol = 'K';
                }
                else{
                    pieceSymbol = 'k';
                }
            }
        bool isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece) override;

};

class Queen : public Piece{
    public:
        Queen(PieceColor pieceColor) : Piece(' ', pieceColor){
                if (pieceColor == PieceColor::WHITE){
                    pieceSymbol = 'Q';
                }
                else{
                    pieceSymbol = 'q';
                }
            }
        bool isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece) override;

};

class Pawn: public Piece{
    public:
        Pawn(PieceColor pieceColor) : Piece(' ', pieceColor){
            if (pieceColor == PieceColor::WHITE){
                pieceSymbol = 'P';
            }
            else{
                pieceSymbol = 'p';
            }
        }

        bool isValidMove(int startX, int startY, int endX, int endY, Piece * targetPiece) override;
};