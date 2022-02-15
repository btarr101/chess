#include "board.h"
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, const piece_color& color)
{
	return out << (color == white ? "white" : "black");
}

ostream& operator<<(ostream& out, const piece_type& type)
{
	const static char chars[] = {
		' ',
		'p',
		'r',
		'h',
		'b',
		'q',
		'k',
	};

	return out << chars[(unsigned int)type];
}

int Piece::forward()
{
	return 1 - (2*(int)color);
}

ostream& operator<<(ostream& out, const Move& mv)
{
	out << "{" << endl;
	for(const Move::SubMove& submv : mv.submoves)
	{
		out << '\t' << submv.pos << " = " << submv.color << ", " << submv.type << endl;
	}
	return out << '}';
}

ChessBoard::ChessBoard() {
	reset();
}

void ChessBoard::reset()
{
	for(unsigned int i=0;i<64;++i) {
		board[i].id    = i;
		board[i].color = white;
		board[i].type  = none;
	}
}

void ChessBoard::newGame()
{
	reset();

	// Rook -> Bishop
	for(unsigned int i=0;i<3;++i)
	{
		board[i].color = white;
		board[7-i].color = white;

		board[i].type = (piece_type)(i+2);
		board[7-i].type = (piece_type)(i+2);
	}

	// Queen
	board[3].color = white;
	board[3].type = queen;

	// King
	board[4].color = white;
	board[4].type = king;

	// Pawns
	for(unsigned int i=8;i<16;++i)
	{
		board[i].color = white;
		board[i].type  = pawn;
	}

	// Copying to black side
	for(unsigned int i=63;i>47;--i)
	{
		board[i].color = black;
		board[i].type = board[63-i].type;
	}
}

const Piece& ChessBoard::operator[](unsigned int pos) const {
	return board[pos];
}

unsigned int ChessBoard::checkSpot(int pos, piece_color color) const
{
	if (pos < 0 || pos > 63) return 2;
	if (board[pos].type != none)
		return 1 + (board[pos].color == color);
	return 0;
}

Move ChessBoard::pieceTranslation(unsigned int pos, int dpos)
{
	Piece piece = board[pos];

	Move translation;
	translation.submoves.push_back( Move::SubMove{.pos = pos,
																								.color = white,
																								.type = none} );
	translation.submoves.push_back( Move::SubMove{.pos = pos + dpos,
																								.color = piece.color,
																								.type = piece.type} );
	return translation;
}

void ChessBoard::addPawnMoves(unsigned int pos, vector<Move>& vec)
{
	Piece& pawn = board[pos];

	if (checkSpot(pos + pawn.forward()*8, pawn.color) == 0)
	{
		// Move forward one (TODO: get piece back)
		vec.push_back(pieceTranslation(pos, pawn.forward()*8));

		// First pawn move
		if (pos / 8 == (7*(int)pawn.color + pawn.forward()) && checkSpot(pos + pawn.forward()*16, pawn.color) == 0)
			vec.push_back(pieceTranslation(pos, pawn.forward()*16));
	}

	// Diagnol captures
	for(int i=-1;i<2;i+=2)
	{
		if (checkSpot(pos + i + pawn.forward()*8, pawn.color) == 1)
		{
			vec.push_back(pieceTranslation(pos, i + pawn.forward()*8));
		}
	}
}

void ChessBoard::addRookMoves(unsigned int pos, vector<Move>& vec)
{

}

void ChessBoard::addKnightMoves(unsigned int pos, vector<Move>& vec)
{

}

void ChessBoard::addBishopMoves(unsigned int pos, vector<Move>& vec)
{

}

void ChessBoard::addQueenMoves(unsigned int pos, vector<Move>& vec)
{

}

void ChessBoard::addKingMoves(unsigned int pos, vector<Move>& vec)
{

}

vector<Move> ChessBoard::getPossibleMoves()
{
	vector<Move> vec;

	for(unsigned int pos=0;pos<64;++pos)
	{
		if (board[pos].color != turn % 2) continue;
		switch (board[pos].type)
		{
			case pawn:
				addPawnMoves(pos, vec); break;
			case rook:
				addRookMoves(pos, vec); break;
			case knight:
				addKnightMoves(pos, vec); break;
			case bishop:
				addBishopMoves(pos, vec); break;
			case queen:
				addQueenMoves(pos, vec); break;
			case king:
				addKingMoves(pos, vec); break;
			default:
				break;
		}
	}

	return vec;
}

void ChessBoard::applyMove(const Move& mv)
{
	for(const Move::SubMove& submv : mv.submoves)
	{
		board[submv.pos].color = submv.color;
		board[submv.pos].type  = submv.type;
	}
}

ostream& operator<<(ostream& out, const ChessBoard& board)
{
	out << "  +-----------------+";
	for(unsigned int i=64;i!=0;)
	{
		if (i % 8 == 0)
			out << endl << (i / 8) << " | ";
		out << board[--i].type << ' ';
	}

	out << endl << "  +-----------------+" << endl << "    ";
	for(unsigned int i=0;i<8;++i) {
		out << (char)('A' + i) << ' ';
	}

	return out;
}
