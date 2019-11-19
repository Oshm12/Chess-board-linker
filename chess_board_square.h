#pragma once
#include "pch.h"
#include <string>
#include <vector>

using namespace std;

class chess_board_square
{
public:
	chess_board_square();
	~chess_board_square();
	//void legalMoves(board gameBoard, vector<int> movesArray);
	bool withinBoard();
	
	
	bool hasPiece;
	char pieceType; 
	//colour of each peace, white == true, black == false
	bool colour;
	int row;
	int column;
	static const int SIZE = 34;

};

