#include <iostream>
#include <string>
#include <chrono> 
#include "board.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
   
    if (argc > 1 && string(argv[1]) == "perft") {
        int maxDepth = (argc > 2) ? stoi(argv[2]) : 5; 
        
        cout << "=== PERFT ANALYSIS (1 to " << maxDepth << ") ===" << endl;
     
        for (int i = 1; i <= maxDepth; i++) {
            Board chessBoard;
            chessBoard.setBoard(); 
            
            auto start = high_resolution_clock::now();
            
            long long totalNodes = chessBoard.perft(i);
            
            auto end = high_resolution_clock::now(); 
            auto duration = duration_cast<milliseconds>(end - start);
            
            cout << "Depth " << i << " -> Nodes: " << totalNodes 
                 << " (Sure: " << duration.count() << " ms)" << endl;
        }
        return 0;
    }

    Board chessBoard;
    chessBoard.setBoard();
    
    // chessBoard.play();

    return 0;
}