//---------------------------------------------------------------------------------------
//                                        LAB 7
//                                   finish my tic-tac-toe game
//---------------------------------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;
const int bDim = 3;

//---------------------------------------------------------------------------------------
//                                        initBoard
//---------------------------------------------------------------------------------------
// is given a board and sets all values to ' ' (blank)
void initBoard(char board[][bDim]){
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			board[i][j] = ' ';
		}
	}
}


//---------------------------------------------------------------------------------------
//                                        printBoard
//---------------------------------------------------------------------------------------
// FINISH this to print the values in the given board inside the game table
void printBoard(char b[][bDim]) {
	// cout << "   |   |    \n";
	// cout << "---+---+----\n";
	// cout << "   |   |    \n";
	// cout << "---+---+----\n";
	// cout << "   |   |    \n";
	// loop through each row and construct the string as you go
	for (int i=0; i<3; i++){
		string row = " ";
		for (int j=0; j<3; j++){
			if (b[j][i] != ' '){
				row += b[j][i];
			}
			else {
				row += " ";
			}
			row += " ";
			if (j < 2){
				row += "| ";
			}
		}
		cout << row << endl;
		if (i < 2){
			cout << "---+---+---\n";
		}
	}
}

//---------------------------------------------------------------------------------------
//                                        isWinner
//---------------------------------------------------------------------------------------
// FINISH this by finishing the boolean expression. Comments have been added for each line needed.
bool isWinner(char b[][bDim]) {
	if (((b[0][0] == b[0][1]) && (b[0][0] == b[0][2]) && (b[0][0] != ' ')) ||	// row 0
		((b[1][0] == b[1][1]) && (b[1][0] == b[0][2]) && (b[1][0] != ' ')) ||   // row 1
		((b[2][0] == b[2][1]) && (b[2][0] == b[2][2]) && (b[2][0] != ' ')) ||   // row 2
		((b[0][0] == b[1][0]) && (b[0][0] == b[2][0]) && (b[0][0] != ' ')) ||			// col 0
		((b[0][1] == b[1][1]) && (b[0][1] == b[2][1]) && (b[1][0] != ' ')) || // col 1
		((b[0][2] == b[1][2]) && (b[0][2] == b[2][2]) && (b[2][0] != ' ')) || // col 2
		((b[0][0] == b[1][1]) && (b[0][0] == b[2][2]) && (b[0][0] != ' ')) || // diag top/Left to bot/Right
		((b[2][0] == b[1][1]) && (b[2][0] == b[0][2]) && (b[2][0] != ' '))) // diag top/Right to bot/Left
		return true;
	else
		return false;
}

//---------------------------------------------------------------------------------------
//                                        getChoice
//---------------------------------------------------------------------------------------
// DONE!
void getChoice(char player, char board[][bDim], int &x, int &y) {
	bool OK = false;
	while (!OK) {
		cout << player << ", choose a spot (x y): ";
		cin >> x >> y;
		if (x < 0 || x > 2)
			cout << "Invalid x: pick a number 0 to 2!\n";
		else if (y < 0 || y>2)
			cout << "Invalid y: pick a number 0 to 2!\n";
		else if (board[x][y] != ' ')
			cout << "That position is already taken! Try again!\n";
		else
			OK = true;
	}
}

//---------------------------------------------------------------------------------------
//                                        isTie
//---------------------------------------------------------------------------------------
// returns TRUE if all positions are not blank; returns FALSE if at least one position is blank.
bool isTie(char board[][bDim]){
	for (int i=0; i<3; i++){
		for (int j=0; j<3; j++){
			if (board[i][j] == ' '){
				return false;
			}
		}
	}
	return true;
}

//---------------------------------------------------------------------------------------
//                                        takeTurn
//---------------------------------------------------------------------------------------
// DONE!
// player is 'X' or 'O'
bool takeTurn(char player, char board[][bDim]) {
	int  x, y;
	bool  keepPlaying = false;			// assume there is a winner or a tie
	printBoard(board);					// print the board
	getChoice(player, board, x, y);		// sets x and y to the valid chosen spot
	board[x][y] = player;				// place X/O in the chosen spot

	if (isWinner(board))
		cout << player << " wins!\n";
	else if (isTie(board))
		cout << "Tie game! Game Over!\n";
	else
		keepPlaying = true;
	return keepPlaying;
}


//---------------------------------------------------------------------------------------
//                                        main
//---------------------------------------------------------------------------------------
// DONE!
int main() {
	bool keepPlaying;
	char playAgain = 'Y';
	char board[bDim][bDim];

	do {
		initBoard(board);		// set all spots to ' ' (blank)
		do {
			keepPlaying = takeTurn('X', board);
			if (keepPlaying)
				keepPlaying = takeTurn('O', board);
		} while (keepPlaying); //!!!!!!!!!!
		cout << "Play again? (Y/N): ";
		cin >> playAgain;
	} while (playAgain == 'Y' || playAgain == 'y');

	system("pause");
	return 0;
}
