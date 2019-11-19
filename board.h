#pragma once
#include "pch.h"
#include "chess_board_square.h"
#include "Move.h"

class board
{
public:
	board();
	~board();
	void printBoard(board & toPrint);
	board legalMoves(int row, int  column);
	bool withinBoard(int row, int column);
	void standardSet(board & boardToSet);
	void customSet(board & boardToSet);
	static const int SIZE = 8;
	void movePieceTo(chess_board_square & moving, chess_board_square & landing);
	void printMoveList();
	int letterToNumber(char letter);

	chess_board_square boardArray[SIZE][SIZE];
	char letterAxis[SIZE] = { 'A','B','C','D','E','F','G','H' };
	bool firstMove = true;



private:
	
	Move *first_move;
	Move *last_move_created = nullptr;


	
};

