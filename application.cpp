#include "pch.h"
#include "application.h"
#include "board.h"

#include <iostream>
#include <string>

using namespace std;


application::application(){

	cout << "Application class created";

}


application::~application(){

}

void application::test() {

	board testBoard;

	//TEST LETTER TO NUMBER
	if (testBoard.letterToNumber('C') != 3) {
		cout << "\nErroR with letterToNumber function";
	}
	if (testBoard.letterToNumber('e') != 5) {
		cout << "\nErroR with letterToNumber function";
	}

	//TEST WITHIN BOARD

	if (!testBoard.withinBoard(3, 4)) {
		cout << "\nError with 'within board' function";
	}
	if (testBoard.withinBoard(-3, 4)) {
		cout << "\nError with 'within board' function";
	}


}

void application::run() {

	cout << "\nRunning standard setup";

	board gameBoard;


	//variables
	bool gameLoop = true;
	char rowLetter;
	int column, row;
	string selectedPiece;

	bool correctSetUp = false;

	while (!correctSetUp) {
		cout << "\nEnter S for a standard set up or enter C for a custom one.\n";

		string setUpPreference;
		cin >> setUpPreference;



		if (setUpPreference == "S" || setUpPreference == "s") {
			correctSetUp = true;
			gameBoard.standardSet(gameBoard);
		}

		if (setUpPreference == "C" || setUpPreference == "c") {
			correctSetUp = true;
			gameBoard.customSet(gameBoard);
		}
	}
	gameBoard.printBoard(gameBoard);

	bool lastPieceColour = false;
	bool debugOptionChosen = false;
	bool debug = false;
	bool takeTurns = false;
	string turnAboutInput;

	while (!debugOptionChosen) {

		cout << "\nDo you wish teams to play turn about in or in debug mode. Enter Y or D.\n";
		cin >> turnAboutInput;

		if (turnAboutInput == "Y" || turnAboutInput == "y") {
			debug = false;
			takeTurns = true;
			debugOptionChosen = true;
		}
		if (turnAboutInput == "D" || turnAboutInput == "d") {
			debug = true;
			takeTurns = false;
			debugOptionChosen = true;
			cout << "\nRunning in debug mode\n";
		}


	}

	//white == true, blacck == false ,white starts first therefore lastPiece defaults to false

	while (gameLoop) {


		bool suitableInput = false;
		if (takeTurns) {
			while (!suitableInput) {
				cout << "\n Chooose which piece you wish to move (eg. A 6 etc.). Or enter Q to exit \n";

				//inputs
				cin >> rowLetter;
				if (rowLetter == 'Q' || rowLetter == 'q') {
					cout << "exiting";
					return;

				}
				cin >> column;
				row = gameBoard.letterToNumber(rowLetter);
				//adress now found
				if (gameBoard.boardArray[row - 1][column - 1].hasPiece) {
					selectedPiece = gameBoard.boardArray[row - 1][column - 1].pieceType;
					cout << "You have chosen the " << selectedPiece << ", at " << rowLetter << " " << column << ". \n";
				}
				if (!gameBoard.boardArray[row - 1][column - 1].hasPiece) {
					cout << "\nThat square contain no pieces. Try a different one.\n";
				}

				if (gameBoard.boardArray[row - 1][column - 1].colour == lastPieceColour) {
					cout << "\nThat piece is the wrong colour, it is the other 'players' turn, pick a pick from the other side\n";
				}
				if (!gameBoard.boardArray[row - 1][column - 1].colour == lastPieceColour && gameBoard.boardArray[row - 1][column - 1].hasPiece) {
					cout << "\nValid Piece\n";
					suitableInput = true;
				}
			}
		}

		if (!takeTurns) {
			while (!suitableInput) {
				cout << "\n Chooose which piece you wish to move (eg. A 6 etc.). Or enter Q to exit. \n";

				//inputs
				cin >> rowLetter;
				if (rowLetter == 'Q' || rowLetter == 'q') {
					cout << "exiting";
					return;

				}
				cin >> column;
				row = gameBoard.letterToNumber(rowLetter);
				//adress now found

				if (gameBoard.boardArray[row - 1][column - 1].hasPiece) {
					selectedPiece = gameBoard.boardArray[row - 1][column - 1].pieceType;
					cout << "You have chose the " << selectedPiece << ", at " << rowLetter << " " << column << ". \n";
					suitableInput = true;
				}

				if (!gameBoard.boardArray[row - 1][column - 1].hasPiece) {
					cout << "\nThat square contain no pieces. Try a different one.\n";
				}

			}

		}

		////moving code
		board legalMoves = gameBoard.legalMoves(row - 1, column - 1);

		legalMoves.printBoard(legalMoves);

		bool availableMove = false;
		while (!availableMove) {

			cout << "Enter the address you wish to move to or enter N not to move\n";

			char moveRowLetter;
			int moveColumn, moveRow;

			cin >> moveRowLetter;
			// debug false so restrict moves
			if (!debug) {
				cout << "\nTesting legal moves";
				if (moveRowLetter == 'N' || moveRowLetter == 'n') {
					cout << "\n No Move wanted";
					availableMove = true;

				}

				else {
					//cout << "else statemnt triggered";
					cin >> moveColumn;

					if (gameBoard.withinBoard(gameBoard.letterToNumber(moveRowLetter) - 1, moveColumn - 1)) {

						moveRow = gameBoard.letterToNumber(moveRowLetter);
						
						if (gameBoard.boardArray[moveRow - 1][moveColumn - 1].pieceType == 'K') {
							gameBoard.movePieceTo(gameBoard.boardArray[row - 1][column - 1], gameBoard.boardArray[moveRow - 1][moveColumn - 1]);
							gameBoard.printBoard(gameBoard);
							cout << "\n\nThe enemy king has been taken! The game is over.\n";
							return;
						}

							if (legalMoves.boardArray[moveRow - 1][moveColumn - 1].hasPiece) {

								gameBoard.movePieceTo(gameBoard.boardArray[row - 1][column - 1], gameBoard.boardArray[moveRow - 1][moveColumn - 1]);

									gameBoard.printBoard(gameBoard);

									availableMove = true;

									if (lastPieceColour) {
										lastPieceColour = false;
										cout << "\nNext turn a white piece must be plated";
									}
									else if (!lastPieceColour) {
										lastPieceColour = true;
										cout << "\nNext turn a black piece must be plated";
									}
							}

						if (!legalMoves.boardArray[moveRow - 1][moveColumn - 1].hasPiece) {
							cout << "\nInvalid move. Try again.";
						}
					}
				}
			}
			//debug so unrestricted moves
			if (debug) {
				if (moveRowLetter == 'N' || moveRowLetter == 'n') {
					cout << "\n No Move wanted";
					availableMove = true;
				}

				else {
					cin >> moveColumn;

					moveRow = gameBoard.letterToNumber(moveRowLetter);
					cout << "\nData being put into move function: " << row - 1 << ", " << column - 1 << " and " << moveRow - 1 << ", " << moveColumn - 1;
					gameBoard.movePieceTo(gameBoard.boardArray[row - 1][column - 1], gameBoard.boardArray[moveRow - 1][moveColumn - 1]);

					gameBoard.printBoard(gameBoard);
					availableMove = true;
				}
			}
			gameBoard.printMoveList();
		}
	}
}




