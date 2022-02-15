#include <iostream>
#include <random>
#include <time.h>
#include <ncurses.h>
#include "board.h"

using namespace std;

int main() {
	srand(time(NULL));

	ChessBoard myBoard;

	cout << myBoard << endl;

	myBoard.newGame();

	cout << myBoard << endl;

	vector<Move> moves;

	while ((moves = myBoard.getPossibleMoves()).size() != 0)
	{
		myBoard.applyMove(moves[rand() % moves.size()]);
		++myBoard.turn;

		cout << myBoard << endl;
	}

	return 0;
}
