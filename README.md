# Headless C++ Chess Engine

A headless chess engine written in modern C++14 with an object-oriented design and RAII-based memory management. The goal is a correct, testable move-generation core that can later serve as the foundation for data pipelines, analysis tools, and simulations.

> **Status:** V1.0 move-generation core. Perft is verified from the starting position up to depth 5. Castling and promotion are implemented in the game logic but are **not yet covered by perft** (see [Known Limitations](#known-limitations)).

## Features

* **Rules implemented:** Piece movement, check detection, checkmate/stalemate detection, en passant, castling, and pawn promotion (`movePiece`).
* **Ownership model:** Pieces are owned through `std::unique_ptr<Piece>` on an 8x8 grid, so there are no manual `new`/`delete` calls.
* **Move simulation:** Legality is checked by making a move, testing for check, and unmaking it. Perft uses the same make/unmake approach and does not copy the board.
* **Headless:** Command-line only, no GUI dependencies, suitable for automated testing and backend integration.

## Perft Validation

Move generation is validated with Perft (performance test), which counts all leaf nodes of the legal-move tree at a given depth. Node counts below match the commonly published reference values for the standard starting position.

| Depth | Nodes     | Time (approx.) | Result |
|-------|-----------|----------------|--------|
| 1     | 20        | < 1 ms         | Pass   |
| 2     | 400       | < 1 ms         | Pass   |
| 3     | 8,902     | ~4 ms          | Pass   |
| 4     | 197,281   | ~70 ms         | Pass   |
| 5     | 4,865,609 | ~1,000 ms      | Pass   |

*Timings are approximate, measured with `-O2` on an Apple M4 Mac. Only the starting position is tested so far.*

## Known Limitations

* Perft currently covers the starting position only. Castling and promotion cannot occur within depth 5 from that position, so they are not exercised by the table above.
* `perft()` does not yet apply the rook move for castling or promotions, and does not generate under-promotions (N/R/B). Results for positions involving those moves (e.g. Kiwipete) are therefore not expected to match yet.
* Castling checks are incomplete: king-in-check and passing-through-check are not verified, and the queenside rook path is not fully checked.
* Move generation is brute-force (every from/to square pair is tested), and each square is a separately allocated polymorphic object. The engine prioritizes clarity and correctness over speed.

## Development Roadmap

- [x] Core: Headless engine with move generation (Perft 1-5 verified from the start position)
- [ ] Integration: FEN (Forsyth-Edwards Notation) parser
- [ ] Testing: Perft with castling, promotion, and under-promotion, validated on standard positions (e.g. Kiwipete)
- [ ] Testing: Run under AddressSanitizer/Valgrind to confirm leak-free behavior
- [ ] Interoperability: `pybind11` bridge for C++/Python bindings
- [ ] Pipeline: Multithreaded PGN data processing
- [ ] UI/UX: Streamlit-based data visualization dashboard

## Build & Execution

### Prerequisites

* `clang++` compiler (C++14 support required)
* `make`

### Run the Perft test

```bash
make test
```

This builds the engine and runs perft from depth 1 to 5. You can also run it directly with a custom depth:

```bash
clang++ *.cpp -std=c++14 -O2 -o play_chess
./play_chess perft 4
```
