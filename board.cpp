#include <iostream>
#include <string>
#include "board.h"
#include "pieces.h"
#include <utility>
using namespace std;


void Board:: cleanBoard(){
    for (int i = 0; i < 8; i ++){
        for (int j = 0; j < 8 ; j ++){
            Board::grid[i][j] = nullptr;
        }
    }
}

bool Board::simulateMoveandCheck(int startX, int startY, int endX, int endY){
    bool isDanger;

    unique_ptr<Piece> temp = std::move(grid[endX][endY]);
    grid[endX][endY] = std::move(grid[startX][startY]);

    isDanger = isCheck(currentTurn);
    grid[startX][startY] = std::move(grid[endX][endY]);
    grid[endX][endY] = std::move(temp);

    return isDanger;

}

void Board:: setBoard(){
    for (int i = 0; i < 8; i++){
        grid[1][i] = make_unique<Pawn>(PieceColor::WHITE);
        grid[6][i] = make_unique<Pawn>(PieceColor::BLACK);    
    }

    // white pieces
    grid[0][0] = make_unique<Rook>(PieceColor::WHITE);
    grid[0][1] = make_unique<Knight>(PieceColor::WHITE);
    grid[0][2] = make_unique<Bishop>(PieceColor::WHITE);
    grid[0][3] = make_unique<Queen>(PieceColor::WHITE);
    grid[0][4] = make_unique<King>(PieceColor::WHITE);
    grid[0][5] = make_unique<Bishop>(PieceColor::WHITE);
    grid[0][6] = make_unique<Knight>(PieceColor::WHITE);
    grid[0][7] = make_unique<Rook>(PieceColor::WHITE);


    //black pieces
    grid[7][0] = make_unique<Rook>(PieceColor::BLACK);
    grid[7][1] = make_unique<Knight>(PieceColor::BLACK);
    grid[7][2] = make_unique<Bishop>(PieceColor::BLACK);
    grid[7][3] = make_unique<Queen>(PieceColor::BLACK);
    grid[7][4] = make_unique<King>(PieceColor::BLACK);
    grid[7][5] = make_unique<Bishop>(PieceColor::BLACK);
    grid[7][6] = make_unique<Knight>(PieceColor::BLACK);
    grid[7][7] = make_unique<Rook>(PieceColor::BLACK);

}

void Board::showBoard(){
    for (int i = 0; i < 8; i ++){
        for (int j = 0; j<8; j ++){
            if (grid[i][j] != nullptr){
                cout << grid[i][j]-> getSymbol() << ' ';
            }
            else{ 
                cout << ". ";
            } 
        }
        cout << endl;
    }
        
}
bool Board::hasLegalMoves(){
    PieceColor turnColor = (currentTurn == Turn::WHITE)? PieceColor::WHITE : PieceColor::BLACK;

    for (int i = 0; i < 8; i ++){
        for (int j = 0; j<8; j ++){
            if (grid[i][j] != nullptr && grid[i][j]->getColor() == turnColor){
                for (int k = 0; k < 8; k ++){
                    for (int l = 0; l<8; l ++){
                        if(!(k==i && l==j)){
                            if (simulateMoveandCheck(j,i,l,k)) return true;
                            
                        }
                    }
                }
            }

        }
    }
    return false;
}


void Board::movePiece(int startX, int startY, int endX, int endY, char prom) {
    
    if (currentStatus != GameStatus::ONGOING) return;

    if (grid[startX][startY] == nullptr) return; 
    
    PieceColor expectedColor = (currentTurn == Turn::WHITE) ? PieceColor::WHITE : PieceColor::BLACK;
    if (grid[startX][startY]->getColor() != expectedColor) {
        return; 
    }

    Piece* targetPiece = grid[endX][endY].get();

    if (targetPiece != nullptr && targetPiece->getColor() == grid[startX][startY]->getColor()) {
        return; 
    }

    char sym = grid[startX][startY]->getSymbol();
    bool isEP = (sym == 'P' || sym == 'p') && abs(endY - startY) == 1 && endX == enPassantX && endY == enPassantY;

    if (!isEP && !grid[startX][startY]->isValidMove(startX, startY, endX, endY, targetPiece)) {
        return; 
    }

    char symbol = grid[startX][startY]->getSymbol();

    if (symbol != 'N' && symbol != 'n') {
        if (!isPathClear(startX, startY, endX, endY)) {
            return; 
        }
    }

    if(simulateMoveandCheck(startX,startY,endX,endY)) return;

    if (symbol == 'K' || symbol == 'k'){
        if (abs(endY - startY) == 2) {
        int rookStartY = (endY > startY) ? 7 : 0;
        if (grid[startX][rookStartY] == nullptr || grid[startX][rookStartY]->pieceMoved()) return;
        
        int rookEndY = (endY > startY) ? endY - 1 : endY + 1;

        grid[startX][rookEndY] = std::move(grid[startX][rookStartY]);
        grid[startX][rookEndY]->setMove();
}
    }

    
    
    if ((symbol == 'P' || symbol == 'p') && (startY != endY) && grid[endX][endY] == nullptr && endX == enPassantX && endY == enPassantY) {
        grid[startX][endY] = nullptr;
    }

    grid[endX][endY] = std::move(grid[startX][startY]);

    enPassantX = -1;
   enPassantY = -1;

    if ((symbol == 'P' || symbol == 'p') && abs(endX - startX) == 2 && startY == endY) {
        enPassantX = (startX + endX) / 2;
        enPassantY = endY;
    }

    grid[endX][endY]->setMove();

    unique_ptr<Piece> newPiece;

    if (symbol == 'P' || symbol == 'p'){
        if(endX == 0 || endX == 7){
            switch(prom){
                case 'N': case 'n': 
                newPiece = make_unique<Knight>(grid[endX][endY]->getColor());
                break;
            case 'R': case 'r': 
                newPiece = make_unique<Rook>(grid[endX][endY] -> getColor()); 
                break;
            case 'B': case 'b': 
                newPiece = make_unique<Bishop>(grid[endX][endY] -> getColor()); 
                break;
            default:            
                newPiece = make_unique<Queen>(grid[endX][endY] -> getColor()); 
                break;
        }
            grid[endX][endY] = std::move(newPiece);
            }
        }
    



    currentTurn = (currentTurn == Turn::WHITE) ? Turn::BLACK : Turn::WHITE;

    if (!hasLegalMoves()) {
    if (isCheck(currentTurn)) {
        isGameOver = true;
        currentStatus =  (currentTurn == Turn::WHITE) ? GameStatus::BLACK_WIN :GameStatus::WHITE_WIN;

    } else {
        isGameOver = true;
        currentStatus = GameStatus::TIE;
    }
}
}

bool Board::isPathClear(int startX,int startY,int endX,int endY){
    int dirX,dirY;
    if (endX>startX) dirX = 1;
    else if (endX<startX) dirX = -1;
    else dirX = 0;

    if (endY>startY) dirY = 1;
    else if (endY<startY) dirY = -1;
    else dirY = 0;

    int currentX = startX + dirX;
    int currentY = startY + dirY;

    while((currentX != endX)||(currentY != endY)){
        if (grid[currentX][currentY] != nullptr) return false;
        currentX += dirX;
        currentY += dirY;
        
    }
    return true;
}

pair<int,int> Board::kingPosition(Turn turn){
    char symbol = (turn == WHITE)?'K':'k';

    for(int y = 0; y < 8; y ++){
        for (int x = 0; x<8; x++){
            if (grid[x][y] != nullptr && Board::grid[x][y] -> getSymbol() == symbol) return make_pair(x,y);
        }
    }
    return make_pair(-1, -1);
}

bool Board::isCheck(Turn turn){
    auto kingPos = kingPosition(turn);
    int kingX = kingPos.first;
    int kingY = kingPos.second;
    Piece * kingPiece  = grid[kingX][kingY].get();

    PieceColor enemyColor;
    if (turn == WHITE) enemyColor = PieceColor::BLACK;
    else enemyColor = PieceColor::WHITE;

    for(int y = 0; y < 8; y ++){
        for (int x = 0; x<8; x++){
            if (grid[x][y] != nullptr  && grid[x][y] -> getColor() == enemyColor){
                if (grid[x][y] -> isValidMove(x,y,kingX,kingY,kingPiece)) {
                    char symbol = grid[x][y]->getSymbol();
                    if (symbol == 'N' || symbol == 'n' || isPathClear(x, y, kingX, kingY)) {
                            return true;
                        }
                    } 
                }
        }
    } 
    return false;
}

long long Board::perft(int depth) {
    if (depth == 0) {
        return 1;
    }

    long long nodes = 0;
    PieceColor turnColor = (currentTurn == Turn::WHITE) ? PieceColor::WHITE : PieceColor::BLACK;

    for (int startX = 0; startX < 8; startX++) {
        for (int startY = 0; startY < 8; startY++) {
            if (grid[startX][startY] != nullptr && grid[startX][startY]->getColor() == turnColor) {
                for (int endX = 0; endX < 8; endX++) {
                    for (int endY = 0; endY < 8; endY++) {
                        if (startX == endX && startY == endY) continue;

                        Piece* target = grid[endX][endY].get();
                        if (target != nullptr && target->getColor() == turnColor) continue;

                        char sym = grid[startX][startY]->getSymbol();
                        
                        // VIP Geçiş İzni: Eğer bu bir En Passant hamlesiyse normal kuralları esnet.
                        bool isEP = (sym == 'P' || sym == 'p') && abs(endY - startY) == 1 && endX == enPassantX && endY == enPassantY;
                        if (!isEP && !grid[startX][startY]->isValidMove(startX, startY, endX, endY, target)) continue;

                        if (sym != 'N' && sym != 'n' && !isPathClear(startX, startY, endX, endY)) continue;
                        if (simulateMoveandCheck(startX, startY, endX, endY)) continue;

                        // --- YEDEKLE ---
                        Turn oldTurn = currentTurn;
                        int oldEpX = enPassantX;
                        int oldEpY = enPassantY;
                        GameStatus oldStatus = currentStatus;
                        
                        unique_ptr<Piece> capturedPiece = std::move(grid[endX][endY]);
                        unique_ptr<Piece> epCapturedPiece = nullptr;
                        int capturedEpVictimX = -1, capturedEpVictimY = -1;
                        bool isEnPassantMove = (sym == 'P' || sym == 'p') && (startY != endY) && (capturedPiece == nullptr) && (endX == enPassantX && endY == enPassantY);
                        
                        if (isEnPassantMove) {
                            capturedEpVictimX = startX;
                            capturedEpVictimY = endY;
                            epCapturedPiece = std::move(grid[capturedEpVictimX][capturedEpVictimY]);
                        }

                        // --- HAMLEYİ UYGULA ---
                        grid[endX][endY] = std::move(grid[startX][startY]);
                        
                        // En Passant hafızasını güncelle (Depth 5'te buharlaşan o 258 hamlenin ilacı!)
                        enPassantX = -1;
                        enPassantY = -1;
                        if ((sym == 'P' || sym == 'p') && abs(endX - startX) == 2 && startY == endY) {
                            enPassantX = (startX + endX) / 2;
                            enPassantY = endY;
                        }

                        currentTurn = (currentTurn == Turn::WHITE) ? Turn::BLACK : Turn::WHITE;

                        // --- DÜĞÜMLERİ SAY ---
                        nodes += perft(depth - 1);

                        // --- GERİ AL ---
                        grid[startX][startY] = std::move(grid[endX][endY]);
                        grid[endX][endY] = std::move(capturedPiece);
                        
                        if (isEnPassantMove) {
                            grid[capturedEpVictimX][capturedEpVictimY] = std::move(epCapturedPiece);
                        }

                        currentTurn = oldTurn;
                        enPassantX = oldEpX;
                        enPassantY = oldEpY;
                        currentStatus = oldStatus;
                    }
                }
            }
        }
    }
    return nodes;
}


void Board::perftDivide(int depth) {
    if (depth == 0) return;
    
    long long totalNodes = 0;
    PieceColor turnColor = (currentTurn == Turn::WHITE) ? PieceColor::WHITE : PieceColor::BLACK;

    for (int startX = 0; startX < 8; startX++) {
        for (int startY = 0; startY < 8; startY++) {
            if (grid[startX][startY] != nullptr && grid[startX][startY]->getColor() == turnColor) {
                for (int endX = 0; endX < 8; endX++) {
                    for (int endY = 0; endY < 8; endY++) {
                        if (startX == endX && startY == endY) continue;

                        Piece* target = grid[endX][endY].get();
                        if (target != nullptr && target->getColor() == turnColor) continue;
                        
                        char sym = grid[startX][startY]->getSymbol();
                        
                        // VIP Geçiş İzni
                        bool isEP = (sym == 'P' || sym == 'p') && abs(endY - startY) == 1 && endX == enPassantX && endY == enPassantY;
                        if (!isEP && !grid[startX][startY]->isValidMove(startX, startY, endX, endY, target)) continue;

                        if (sym != 'N' && sym != 'n' && !isPathClear(startX, startY, endX, endY)) continue;
                        if (simulateMoveandCheck(startX, startY, endX, endY)) continue;

                        // --- YEDEKLE ---
                        Turn oldTurn = currentTurn;
                        int oldEpX = enPassantX;
                        int oldEpY = enPassantY;
                        GameStatus oldStatus = currentStatus;
                        
                        unique_ptr<Piece> capturedPiece = std::move(grid[endX][endY]);
                        unique_ptr<Piece> epCapturedPiece = nullptr;
                        int capturedEpVictimX = -1, capturedEpVictimY = -1;
                        bool isEnPassantMove = (sym == 'P' || sym == 'p') && (startY != endY) && (capturedPiece == nullptr) && (endX == enPassantX && endY == enPassantY);
                        
                        if (isEnPassantMove) {
                            capturedEpVictimX = startX;
                            capturedEpVictimY = endY;
                            epCapturedPiece = std::move(grid[capturedEpVictimX][capturedEpVictimY]);
                        }

                        // --- HAMLEYİ UYGULA ---
                        grid[endX][endY] = std::move(grid[startX][startY]);
                        
                        // En Passant hafızasını güncelle
                        enPassantX = -1;
                        enPassantY = -1;
                        if ((sym == 'P' || sym == 'p') && abs(endX - startX) == 2 && startY == endY) {
                            enPassantX = (startX + endX) / 2;
                            enPassantY = endY;
                        }

                        currentTurn = (currentTurn == Turn::WHITE) ? Turn::BLACK : Turn::WHITE;

                        // --- DÜĞÜMLERİ SAY ---
                        long long nodes = perft(depth - 1);
                        totalNodes += nodes;

                        // KARELERİ SATRANÇ NOTASYONUNA ÇEVİR (Örn: e2e4)
                        char startFile = startY + 'a';
                        char startRank = startX + '1';
                        char endFile = endY + 'a';
                        char endRank = endX + '1';
                        
                        cout << startFile << startRank << endFile << endRank << ": " << nodes << endl;

                        // --- GERİ AL ---
                        grid[startX][startY] = std::move(grid[endX][endY]);
                        grid[endX][endY] = std::move(capturedPiece);
                        
                        if (isEnPassantMove) {
                            grid[capturedEpVictimX][capturedEpVictimY] = std::move(epCapturedPiece);
                        }

                        currentTurn = oldTurn;
                        enPassantX = oldEpX;
                        enPassantY = oldEpY;
                        currentStatus = oldStatus;
                    }
                }
            }
        }
    }
    cout << "\nToplam Nodes (Depth " << depth << "): " << totalNodes << endl;
}