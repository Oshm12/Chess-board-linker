#include "pch.h"
#include "board.h"
#include "Move.h"

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


board::board(){

	//cout << "\nA new board has been created";

}


board::~board() {

}
void board::customSet(board & boardToSet) {
	char rowLetter, pieceType;
	int column, row;
	bool pieceColour, continueToGame = false;

	//boardArray[SIZE][SIZE];

	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < 8; j++) {
			boardToSet.boardArray[i][j].hasPiece = false;
		
		}
	}
	bool suitableInput = false;
	while (!continueToGame){
		
	
		suitableInput = false;
		while (!suitableInput) {
			cout << "\nEnter the location of the piece you wish to place(e.g. C 6) or press Q to continue to the game \n";

			cin >> rowLetter;
			if (rowLetter == 'Q' || rowLetter == 'q') {
				cout << "\nContinuing to Game.";
				continueToGame = true;
				suitableInput = true; 
			}
			if (!continueToGame) {
				cin >> column;
				row = boardToSet.letterToNumber(rowLetter);
				if (boardToSet.withinBoard(row - 1, column - 1)) {
					cout << "\nEnter the piece type (p,c,r,b,Q,K) and its colour (1 for white, 0 for black).\n";
					cin >> pieceType;
					if (pieceType == 'p' || pieceType == 'c' || pieceType == 'r' || pieceType == 'b' || pieceType == 'Q' || pieceType == 'K') {
						cout << "a valid piece";
						int booltest;
							cin >> booltest;
						if (booltest == 1 || booltest == 0) {
							cout << "a avlid colour";
							boardToSet.boardArray[row - 1][column - 1].pieceType = pieceType;
							boardToSet.boardArray[row - 1][column - 1].colour =booltest;
							boardToSet.boardArray[row - 1][column - 1].hasPiece = true;
							boardToSet.boardArray[row - 1][column - 1].column = column - 1;
							boardToSet.boardArray[row - 1][column - 1].row = row - 1;
							suitableInput = true;
							cout << "\nA " << pieceType << booltest << " has been added at " << rowLetter << ", " << column << ".\n";
							if (booltest == 1) {
								pieceColour = true;
							}
							if (booltest == 0) {
								pieceColour = false;
							}
						}

						else {
							cout << "\nInValid colour";
						}
					}

					else {
						cout << "\nAn invalid piece";
					}
				}

				else {
					cout << "\nIncorrect entry, try again\n";
				}

				
			}
		}
	}
}

int board::letterToNumber(char letter) {

	int number = 0;

	switch (letter) {
	case 'A':
	case 'a':
		number = 1;
		break;
	case 'B':
	case 'b':
		number = 2;
		break;
	case 'C':
	case 'c':
		number = 3;
		break;
	case 'D':
	case 'd':
		number = 4;
		break;
	case 'E':
	case 'e':
		number = 5;
		break;
	case 'F':
	case 'f':
		number = 6;
		break;
	case 'G':
	case 'g':
		number = 7;
		break;
	case 'H':
	case 'h':
		number = 8;
		break;
	}

	return number;

}

void board::standardSet(board & boardToSet) {

	const int SIZE = 8;
	//string p = "Pawn", r = "Rook", c = "Castle", b = "Bishop", K = "King", Q = "Queen", s = " ";
	char p = 'p', r = 'r', c = 'c', b = 'b', K = 'K', Q = 'Q', s = ' ';
	char defaultsBoard[SIZE][SIZE] = {
		{ c,r,b,K,Q,b,r,c },
		{p, p, p, p, p, p, p, p},
		{ s,s,s,s,s,s,s,s },
		{ s,s,s,s,s,s,s,s },
		{ s,s,s,s,s,s,s,s },
		{ s,s,s,s,s,s,s,s },
		{ p,p,p,p,p,p,p,p },
		{ c,r,b,K,Q,b,r,c}
	};

	//boardArray[SIZE][SIZE];

	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < 8; j++) {

			if (defaultsBoard[i][j] == s) {
				boardToSet.boardArray[i][j].hasPiece = false;
			}

			else {
				boardToSet.boardArray[i][j].hasPiece = true;
				boardToSet.boardArray[i][j].pieceType = defaultsBoard[i][j];
			}

			if (i <=  1) {
				boardToSet.boardArray[i][j].colour = true;
			}
			if (i >= 6) {
				boardToSet.boardArray[i][j].colour = false;
			}

			boardToSet.boardArray[i][j].row = i;
			boardToSet.boardArray[i][j].column = j;
		}
	}
	//return boardToSet;
}

void board::printBoard(board & toPrint) {

	cout << "\n   _________________________\n";

	for (int i = 0; i < 8; i++) {

		cout << setw(3) << toPrint.letterAxis[i] << "  |";

		for (int j = 0; j < 8; j++) {
			if (toPrint.boardArray[i][j].hasPiece) {
				if (toPrint.boardArray[i][j].colour == 1 || toPrint.boardArray[i][j].colour == 0) {
					cout << toPrint.boardArray[i][j].pieceType << toPrint.boardArray[i][j].colour << "|";
				}
				else
				{
					cout << toPrint.boardArray[i][j].pieceType << " |";
				}
			}
			else {
				cout << "  |";
			}
		}

		cout << "\n";
	}

	cout <<  setw(10) << "      1  2  3  4  5  6  7  8  \n";

	//cout << "   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ \n";

}

void board::movePieceTo(chess_board_square & moving, chess_board_square & landing) {

	cout << "\nPiece is being moved";

	
	if (!this->firstMove) {

	//	cout << "\nSecond move and onwards.";
		//cout << "\nData put in for move number: " << moving.row << ", " << moving.column << " and " << landing.row << ", " << landing.column;
		Move *new_move = new Move;

		new_move->begRow = moving.row;
		new_move->begCol = moving.column;
		new_move->endRow = landing.row;
		new_move->endCol = landing.column;

		//cout << "\nNext pointer Address" << new_move;
		last_move_created->set_next_move(new_move);

		cout << last_move_created->get_next_move();
	

		//cout << "\nFirst Move next:" << first_move->get_next_move();
		//cout << "\nSecond Last move an more Move next:" << last_move_created->get_next_move();

		last_move_created = new_move;
		//delete new_move;
	
	}
	if (this->firstMove) {
		//cout << "\nFIRST MOVE";
		//cout << "\nData put in for move number: " << moving.row << ", " << moving.column << " and " << landing.row << ", " << landing.column;
		this->first_move = new Move;
		this->first_move->begRow = moving.row;
		this->first_move->begCol = moving.column;
		this->first_move->endRow = landing.row;
		this->first_move->endCol = landing.column;
		this->last_move_created = this->first_move;
		this->firstMove = false;
		
	}
	moving.column = landing.column;
	moving.row = landing.row;
	landing = moving;
	
	moving.hasPiece = false;
	moving.pieceType = ' ';
	
	cout << "\nPiece has been moved";

}

void  board::printMoveList() {
	
	cout << "\nMove list: ";
	Move *PrintMove = new Move;
//	cout << "\nNULLPOINTR TEST: " << this->last_move_created->next;
	//if (this->last_move_created->next == nullptr) {
	//	cout << "\nIf statement worked";
		PrintMove = this->first_move;
		cout << "\n" << this->letterAxis[PrintMove->begRow] << ", " << PrintMove->begCol + 1 << " to " << this->letterAxis[PrintMove->endRow] << ", " << PrintMove->endCol + 1;
		while (PrintMove->get_next_move() != nullptr) {
			PrintMove = PrintMove->get_next_move();
			//cout << "\nPointer test for next move: " << PrintMove->get_next_move();;
			cout << "\n" << this->letterAxis[PrintMove->begRow] << ", " << PrintMove->begCol + 1 << " to " << this->letterAxis[PrintMove->endRow] << ", " << PrintMove->endCol+1;
		} 
	//}
	
}

board board::legalMoves(int row, int  column) {

	//cout << this->boardArray[row][column].hasPiece;

	char pieceType = this->boardArray[row][column].pieceType;
	cout << "Legal move check";
	board legalBoard;

	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < 8; j++) {
			legalBoard.boardArray[i][j].pieceType = 's';
			legalBoard.boardArray[i][j].hasPiece = false;
		}
	}

	//cout << "\n " << pieceType << "\n";

	int i, j, k, l;
	bool noPieceInWay;

	switch (pieceType) {
	case 'c'://check column up
		i = column + 1;
		noPieceInWay = true;
		for (i; i < 8 && noPieceInWay; i++) {
			if (this->boardArray[row][i].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[row][i].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << row << ", " << i;
					legalBoard.boardArray[row][i].hasPiece = true;
					legalBoard.boardArray[row][i].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[row][i].hasPiece = true;
				legalBoard.boardArray[row][i].pieceType = 'X';
				cout << "\n Legal move at: " << row << ", " << i;
			}
		}

		//check column down
		i = column - 1;
		noPieceInWay = true;
		for (i; i >= 0 && noPieceInWay; i--) {

			if (this->boardArray[row][i].hasPiece) {
				noPieceInWay = false;
				if (this->boardArray[row][i].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << row << ", " << i;
					legalBoard.boardArray[row][i].hasPiece = true;
					legalBoard.boardArray[row][i].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[row][i].hasPiece = true;
				legalBoard.boardArray[row][i].pieceType = 'X';
				cout << "\n Legal move at: " << row << ", " << i;
			}
		}

		//check row left
		j = row - 1;
		noPieceInWay = true;
		for (j; j >= 0 && noPieceInWay; j--) {

			if (this->boardArray[j][column].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[j][column].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << j << ", " << column;
					legalBoard.boardArray[j][column].hasPiece = true;
					legalBoard.boardArray[j][column].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[j][column].hasPiece = true;
				legalBoard.boardArray[j][column].pieceType = 'X';
				cout << "\n Legal move at: " << j << ", " << column;
			}
		}

		//check row right
		j = row + 1;
		noPieceInWay = true;
		for (j; j < 8 && noPieceInWay; j++) {

			if (this->boardArray[j][column].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[j][column].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << j << ", " << column;
					legalBoard.boardArray[j][column].hasPiece = true;
					legalBoard.boardArray[j][column].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[j][column].hasPiece = true;
				legalBoard.boardArray[j][column].pieceType = 'X';
				cout << "\n Legal move at: " << j << ", " << column;
			}
		}
		cout << "Case: Castle";
		
		break;
	case 'Q':
		cout << "Case: Queen";
		//check column up
		i = column + 1;
		noPieceInWay = true;
		for (i; i < 8 && noPieceInWay; i++) {
			if (this->boardArray[row][i].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[row][i].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << row << ", " << i;
					legalBoard.boardArray[row][i].hasPiece = true;
					legalBoard.boardArray[row][i].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[row][i].hasPiece = true;
				legalBoard.boardArray[row][i].pieceType = 'X';
				cout << "\n Legal move at: " << row << ", " << i;
			}
		}

		//check column down
		i = column - 1;
		noPieceInWay = true;
		for (i; i >= 0 && noPieceInWay; i--) {

			if (this->boardArray[row][i].hasPiece) {
				noPieceInWay = false;
				if (this->boardArray[row][i].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << row << ", " << i;
					legalBoard.boardArray[row][i].hasPiece = true;
					legalBoard.boardArray[row][i].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[row][i].hasPiece = true;
				legalBoard.boardArray[row][i].pieceType = 'X';
				cout << "\n Legal move at: " << row << ", " << i;
			}
		}

		//check row left
		j = row - 1;
		noPieceInWay = true;
		for (j; j >= 0 && noPieceInWay; j--) {

			if (this->boardArray[j][column].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[j][column].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << j << ", " << column;
					legalBoard.boardArray[j][column].hasPiece = true;
					legalBoard.boardArray[j][column].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[j][column].hasPiece = true;
				legalBoard.boardArray[j][column].pieceType = 'X';
				cout << "\n Legal move at: " << j << ", " << column;
			}
		}

		//check row right
		j = row + 1;
		noPieceInWay = true;
		for (j; j < 8 && noPieceInWay; j++) {

			if (this->boardArray[j][column].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[j][column].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << j << ", " << column;
					legalBoard.boardArray[j][column].hasPiece = true;
					legalBoard.boardArray[j][column].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[j][column].hasPiece = true;
				legalBoard.boardArray[j][column].pieceType = 'X';
				cout << "\n Legal move at: " << j << ", " << column;
			}
		}

		k = row + 1;
		l = column + 1;
		noPieceInWay = true;
		while (k < 8 && l < 8 && noPieceInWay) {

			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << k << ", " << l;
					legalBoard.boardArray[k][l].hasPiece = true;
					legalBoard.boardArray[k][l].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}

			k++;
			l++;
		}

		k = row - 1;
		l = column + 1;
		noPieceInWay = true;
		while (k >= 0 && l < 8 && noPieceInWay) {

			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << k << ", " << l;
					legalBoard.boardArray[k][l].hasPiece = true;
					legalBoard.boardArray[k][l].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}

			k--;
			l++;
		}

		k = row - 1;
		l = column - 1;
		noPieceInWay = true;
		while (k >= 0 && l >= 0 && noPieceInWay) {

			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << k << ", " << l;
					legalBoard.boardArray[k][l].hasPiece = true;
					legalBoard.boardArray[k][l].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}

			k--;
			l--;
		}

		k = row + 1;
		l = column - 1;
		noPieceInWay = true;
		while (k < 8 && l < 8 && noPieceInWay) {

			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << k << ", " << l;
					legalBoard.boardArray[k][l].hasPiece = true;
					legalBoard.boardArray[k][l].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}

			k++;
			l--;
		}
		break;
	case 'b':
		cout << "Case Bishop";
		k = row + 1;
		l = column + 1;
		noPieceInWay = true;
		while (k < 8 && l < 8 && noPieceInWay) {

			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << k << ", " << l;
					legalBoard.boardArray[k][l].hasPiece = true;
					legalBoard.boardArray[k][l].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}

			k++;
			l++;
		}

		k = row - 1;
		l = column + 1;
		noPieceInWay = true;
		while (k >= 0 && l < 8 && noPieceInWay) {

			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << k << ", " << l;
					legalBoard.boardArray[k][l].hasPiece = true;
					legalBoard.boardArray[k][l].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}

			k--;
			l++;
		}

		k = row - 1;
		l = column - 1;
		noPieceInWay = true;
		while (k >= 0 && l >= 0 && noPieceInWay) {

			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << k << ", " << l;
					legalBoard.boardArray[k][l].hasPiece = true;
					legalBoard.boardArray[k][l].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}

			k--;
			l--;
		}

		k = row + 1;
		l = column - 1;
		noPieceInWay = true;
		while (k < 8 && l < 8 && noPieceInWay) {

			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << k << ", " << l;
					legalBoard.boardArray[k][l].hasPiece = true;
					legalBoard.boardArray[k][l].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}

			k++;
			l--;
		}
		break;
	case 'K': ////////////////adddddddddddddddddddddddddddd a within board 
		cout << "Case King";
		
		k = row;
		l = column + 1;
		if (this->withinBoard(k, l)) {
			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					legalBoard.boardArray[k][l].hasPiece = true;
						legalBoard.boardArray[k][l].pieceType = 'O';
						cout << "\n Legal move at: " << k << ", " << l;
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}
		}
		k = row + 1;
		l = column + 1;
		if (this->withinBoard(k, l)) {
			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					legalBoard.boardArray[k][l].hasPiece = true;
						legalBoard.boardArray[k][l].pieceType = 'O';
						cout << "\n Legal move at: " << k << ", " << l;
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}
		}
		k = row + 1;
		l = column;
		if (this->withinBoard(k, l)) {
			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					legalBoard.boardArray[k][l].hasPiece = true;
						legalBoard.boardArray[k][l].pieceType = 'O';
						cout << "\n Legal move at: " << k << ", " << l;
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}
		}
		k = row + 1;
		l = column - 1;
		if (this->withinBoard(k, l)) {
			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					legalBoard.boardArray[k][l].hasPiece = true;
						legalBoard.boardArray[k][l].pieceType = 'O';
						cout << "\n Legal move at: " << k << ", " << l;
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}
		}
		k = row;
		l = column - 1;
		if (this->withinBoard(k, l)) {
			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					legalBoard.boardArray[k][l].hasPiece = true;
						legalBoard.boardArray[k][l].pieceType = 'O';
						cout << "\n Legal move at: " << k << ", " << l;
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}
		}
		k = row - 1;
		l = column - 1;
		if (this->withinBoard(k, l)) {
			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					legalBoard.boardArray[k][l].hasPiece = true;
						legalBoard.boardArray[k][l].pieceType = 'O';
						cout << "\n Legal move at: " << k << ", " << l;
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}
		}
		k = row - 1;
		l = column ;
		if (this->withinBoard(k, l)) {
			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					legalBoard.boardArray[k][l].hasPiece = true;
						legalBoard.boardArray[k][l].pieceType = 'O';
						cout << "\n Legal move at: " << k << ", " << l;
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}
		}
		
		k = row - 1;
		l = column + 1;
		if (this->withinBoard(k, l)) {
			if (this->boardArray[k][l].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[k][l].colour == this->boardArray[row][column].colour) {
					legalBoard.boardArray[k][l].hasPiece = true;
						legalBoard.boardArray[k][l].pieceType = 'O';
						cout << "\n Legal move at: " << k << ", " << l;
				}
			}
			else {
				legalBoard.boardArray[k][l].hasPiece = true;
				legalBoard.boardArray[k][l].pieceType = 'X';
				cout << "\n Legal move at: " << k << ", " << l;
			}
		}
		break;
	case 'r':
		// up left + right
		cout << "Case Rook";
		
		i = row + 1;
		j = column + 2;
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[i][j].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << i << ", " << j;
					legalBoard.boardArray[i][j].hasPiece = true;
					legalBoard.boardArray[i][j].pieceType = 'O';
				}
			}
			else{
				legalBoard.boardArray[i][j].hasPiece = true;
				legalBoard.boardArray[i][j].pieceType = 'X';
				cout << "\n Legal move at: " << i << ", " << j;
			}
		}
		i = row - 1;
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[i][j].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << i << ", " << j;
					legalBoard.boardArray[i][j].hasPiece = true;
					legalBoard.boardArray[i][j].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[i][j].hasPiece = true;
				legalBoard.boardArray[i][j].pieceType = 'X';
				cout << "\n Legal move at: " << i << ", " << j;
			}
		}
		// down left and right
		j = column - 2;
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[i][j].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << i << ", " << j;
					legalBoard.boardArray[i][j].hasPiece = true;
					legalBoard.boardArray[i][j].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[i][j].hasPiece = true;
				legalBoard.boardArray[i][j].pieceType = 'X';
				cout << "\n Legal move at: " << i << ", " << j;
			}
		}
		i = row + 1;
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[i][j].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << i << ", " << j;
					legalBoard.boardArray[i][j].hasPiece = true;
					legalBoard.boardArray[i][j].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[i][j].hasPiece = true;
				legalBoard.boardArray[i][j].pieceType = 'X';
				cout << "\n Legal move at: " << i << ", " << j;
			}
		}
		i = row + 2;
		j = column + 1;
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[i][j].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << i << ", " << j;
					legalBoard.boardArray[i][j].hasPiece = true;
					legalBoard.boardArray[i][j].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[i][j].hasPiece = true;
				legalBoard.boardArray[i][j].pieceType = 'X';
				cout << "\n Legal move at: " << i << ", " << j;
			}
		}
		j = column - 1;
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[i][j].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << i << ", " << j;
					legalBoard.boardArray[i][j].hasPiece = true;
					legalBoard.boardArray[i][j].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[i][j].hasPiece = true;
				legalBoard.boardArray[i][j].pieceType = 'X';
				cout << "\n Legal move at: " << i << ", " << j;
			}
		}
		i = row - 2;
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[i][j].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << i << ", " << j;
					legalBoard.boardArray[i][j].hasPiece = true;
					legalBoard.boardArray[i][j].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[i][j].hasPiece = true;
				legalBoard.boardArray[i][j].pieceType = 'X';
				cout << "\n Legal move at: " << i << ", " << j;
			}
		}
		j = column + 1;
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[i][j].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << i << ", " << j;
					legalBoard.boardArray[i][j].hasPiece = true;
					legalBoard.boardArray[i][j].pieceType = 'O';
				}
			}
			else {
				legalBoard.boardArray[i][j].hasPiece = true;
				legalBoard.boardArray[i][j].pieceType = 'X';
				cout << "\n Legal move at: " << i << ", " << j;
			}
		}
		break;
	case 'p':
		
		//cout << row << " and Column: " << column;
		int startRow, startColumn;
		//cout << "\n" << this->boardArray[row][column].colour;
		if (!this->boardArray[row][column].colour) {
			cout << "\n true";
			i = row - 1;
			j = column;
			k = row - 2;
			l = column;
			startRow = 6;
		}
		if (this->boardArray[row][column].colour) {
			cout << "\n false";
			i = row + 1;
			j = column;
			k = row + 2;
			l = column;
			startRow = 1;
			
		}
		//forwards
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
			}
			else {
				legalBoard.boardArray[i][j].hasPiece = true;
				legalBoard.boardArray[i][j].pieceType = 'X';
				cout << "\n Legal move at: " << i << ", " << j;
			}
		}
		if (row == startRow) {
			cout << "\nDouble move";
			if (this->withinBoard(k, l)) {
				if (this->boardArray[k][l].hasPiece) {
					noPieceInWay = false;
				}
				else {
					legalBoard.boardArray[k][l].hasPiece = true;
					legalBoard.boardArray[k][l].pieceType = 'X';
					cout << "\n Legal move at: " << k << ", " << l;
				}
			}
		}
		j = column- 1;
		//taking left
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[i][j].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << i << ", " << j;
					legalBoard.boardArray[i][j].hasPiece = true;
					legalBoard.boardArray[i][j].pieceType = 'O';
				}
			}
		}
		j = column + 1;
		//taking right
		if (this->withinBoard(i, j)) {
			if (this->boardArray[i][j].hasPiece) {
				noPieceInWay = false;
				if (!this->boardArray[i][j].colour == this->boardArray[row][column].colour) {
					cout << "\n Legal move to take a piece at: " << i << ", " << j;
					legalBoard.boardArray[i][j].hasPiece = true;
					legalBoard.boardArray[i][j].pieceType = 'O';

				}
			}
		}
		break;
	}
	return legalBoard;
}

bool board::withinBoard(int row, int column) {

	if (row > 7 || column > 7) {
		return false;
	}

	if (row < 0 || column < 0) {
		return false;
	}

	return true;
}
