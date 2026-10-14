#include <iostream>
#include "board.h"
#include "pieces.h"

using namespace std;

int main() {
    cout << "=== CHESS ENGINE PERFORMANCE TESTS ===" << endl;

    Board chessBoard;
    chessBoard.setBoard();
    
    cout << "Board setted." << endl;
    chessBoard.showBoard();
    cout << "---------------------------------------" << endl;

    // TODO: perft fonksiyonunu Board sınıfına ekledikten sonra burada çağırabilirsin:
    // long long totalNodes = chessBoard.perft(1);
    // cout << "Depth 1 Nodes: " << totalNodes << endl;

    return 0;
}