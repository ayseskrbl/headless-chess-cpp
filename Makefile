play:
	clang++ *.cpp -std=c++14 -o play_chess
	./play_chess
test:
	clang++ *.cpp -std=c++14 -O2 -o play_chess
	./play_chess perft 5