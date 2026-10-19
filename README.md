# Headless C++ Chess Engine

A high-performance, headless chess engine implemented in modern C++14. Designed with a strict object-oriented architecture and memory-safe paradigms, this engine serves as a foundational core for advanced data pipelines, algorithmic benchmarking, and simulations.

## System Architecture & Capabilities

* **Legal Move Generation:** 100% accurate implementation of core chess mechanics, fully resolving En Passant, Castling, and Pawn Promotion edge cases.
* **Memory Lifecycle Management:** Zero-leak architecture utilizing `std::unique_ptr` for strict object ownership during massive recursive search tree traversals.
* **State Optimization:** Employs an efficient Make/Unmake move paradigm on an 8x8 matrix representation, eliminating deep-copy overhead and minimizing cache misses.
* **Headless Design:** Pure CLI-driven execution loop with zero GUI dependencies, built for seamless backend integration and automated testing.

## Performance Validation (Perft)

Move generation accuracy and tree traversal efficiency are rigorously validated using the standard Perft (Performance Test) algorithm. System node counts perfectly align with Stockfish baselines.

| Depth | Nodes       | Execution Time | Validation |
|-------|-------------|----------------|------------|
| 1     | 20          | < 1 ms         | Pass       |
| 2     | 400         | < 1 ms         | Pass       |
| 3     | 8,902       | ~8 ms          | Pass       |
| 4     | 197,281     | ~160 ms        | Pass       |
| 5     | 4,865,609   | ~4,000 ms      | Pass       |

## Development Roadmap

The current V1.0 release establishes the verified move-generation core. Ongoing development focuses on Python interoperability and analytical pipelines.

- [x] Core: Headless engine with full move generation (Perft 5 verified)
- [ ] Integration: FEN (Forsyth-Edwards Notation) parser
- [ ] Interoperability: `pybind11` bridge for C++/Python bindings
- [ ] Pipeline: Multithreaded PGN data processing
- [ ] UI/UX: Streamlit-based data visualization dashboard

## Build & Execution

### Prerequisites
* `clang++` compiler (C++14 standard support required)
* `make` build automation tool

### Operations

Initialize the interactive command-line loop:
```bash
make play
