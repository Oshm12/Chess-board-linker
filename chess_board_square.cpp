#include "pch.h"
#include "chess_board_square.h"


#include <iostream>
#include <vector>

using namespace std;


chess_board_square::chess_board_square(){

}


chess_board_square::~chess_board_square(){

}
/*
void chess_board_square::legalMoves(board gameBoard, vector<int> movesArray) {

	cout << "Legal move check";

	//get all possible moves for the piece from start pos, then check

	int row = this->row;
	int column = this->column;



	switch (this->pieceType)
	{
	case 'c':
		//check column up
		int i = column + 1;
		bool noPieceInWay = true;
		for ( i; !gameBoard.boardArray[row][i].withinBoard() && noPieceInWay ; i++) {

			if (gameBoard.boardArray[row][i].hasPiece) {
				noPieceInWay = false;
			}
			else {
				movesArray.push_back(row);
				movesArray.push_back(i);
			}
		}

		//check column down
		i = column - 1;
		noPieceInWay = true;
		for (i; !gameBoard.boardArray[row][i].withinBoard() && noPieceInWay; i--) {

			if (gameBoard.boardArray[row][i].hasPiece) {
				noPieceInWay = false;
			}
			else {
				movesArray.push_back(row);
				movesArray.push_back(i);
			}
		}

		//check row left
		int j = row + 1;
		bool noPieceInWay = true;
		for (j; !gameBoard.boardArray[j][column].withinBoard() && noPieceInWay; j++) {

			if (gameBoard.boardArray[j][column].hasPiece) {
				noPieceInWay = false;
			}
			else {
				movesArray.push_back(j);
				movesArray.push_back(column);
			}
		}

		//check row right
		j = row - 1;
		noPieceInWay = true;
		for (j; !gameBoard.boardArray[j][column].withinBoard() && noPieceInWay; j--) {

			if (gameBoard.boardArray[j][column].hasPiece) {
				noPieceInWay = false;
			}
			else {
				movesArray.push_back(j);
				movesArray.push_back(column);
			}
		}
	}
}*/

bool chess_board_square::withinBoard() {

	if (this->row < 1 ||  this->row > 8 ) {
		return false;
	}

	if (this->column < 1 || this->column > 8) {
		return false;
	}

	return true;

}