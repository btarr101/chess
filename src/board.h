#pragma once
#include <iostream>
#include <vector>

using namespace std;

class ChessBoard;
class Piece;
struct Move;

enum piece_color
{
	white,
	black,
};

ostream& operator<<(ostream&, const piece_color&);

enum piece_type
{
	none,
	pawn,
	rook,
	knight,
	bishop,
	queen,
	king,
};

ostream& operator<<(ostream&, const piece_type&);

struct Piece
{
	int id = -1;
	piece_color color = white;
	piece_type type   = none;

	int forward();
};

ostream& operator<<(ostream&, const Move&);

struct Move
{
	struct SubMove
	{
		unsigned int pos;
		piece_color color;
		piece_type type;
	};

	vector<SubMove> submoves;
};

Move pieceTranslation(unsigned int, unsigned int);

class ChessBoard
{
	friend ostream& operator<<(ostream&, const ChessBoard&);
	private:
		Piece board[64];

		Move pieceTranslation(unsigned int, int);

		void addPawnMoves  ( unsigned int, vector<Move>& );
		void addRookMoves  ( unsigned int, vector<Move>& );
		void addKnightMoves( unsigned int, vector<Move>& );
		void addBishopMoves( unsigned int, vector<Move>& );
		void addQueenMoves ( unsigned int, vector<Move>& );
		void addKingMoves  ( unsigned int, vector<Move>& );
	public:
		unsigned int turn = 0;

		ChessBoard();
		void reset();
		void newGame();

		const Piece& operator[](unsigned int pos) const;
		unsigned int checkSpot(int pos, piece_color color) const; // 0=empty, 1=enemy, 2=friend/blocked

		vector<Move> getPossibleMoves();
		void applyMove(const Move&);
};

ostream& operator<<(ostream&, const ChessBoard&);
