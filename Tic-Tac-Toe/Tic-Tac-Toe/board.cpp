#include <iostream>
#include <iomanip>
#include <string>

#include "board.h"

using std::cout;
using std::endl;
using std::cin;
using std::setw;
using std::string;
using std::stoi;

Board::Board(): 
	board{{ ' ' , ' ' , ' ' }, { ' ' , ' ' , ' ' }, { ' ' , ' ' , ' ' }} {
}

char** Board::get_game_board() {
	return (char**)this->board;
}

void Board::print_board() {
	cout << endl;
	for (size_t row = 0; row < 3; ++row) {
		cout << setw(3);

		for (size_t column = 0; column < 3; ++column) {

			cout << "(" << this->board[row][column] << ")";

			if (column == 0 || column == 1) {
				cout << setw(3) << "|" << setw(3);
			}
		}
		if (row == 0 || row == 1) {
			cout << endl << string(23, '-') << endl;
		}
	}
	cout << endl;
	// clear screen
	cout << string(2, '\n');
}


bool Board::submit_move(string move, string player, char marker) {
	// checks to see if input is size 3 and contains a space in the middle
	if (move.size() != 3 ) {
		cout << "Invalid Input " << player << ": Please enter the row and column of your move (Example: 1 1)." << endl;
		return false;
	} 
	else if (move[1] != ' '){
		cout << "Invalid Input " << player << ": Please enter the row and column of your move (Example: 1 1)." << endl;
		return false;
	}
	else if (move == "   ") {
		cout << "Invalid Input " << player << ": Please enter the row and column of your move (Example: 1 1)." << endl;
		return false;
	}

	// convert char input into string
	int row_move = (int)move[0] - 48 - 1;
	int column_move = (int)move[2] - 48 - 1;

	// check to see if current sqaure is taken
	if (this->board[row_move][column_move] == 'X' || this->board[row_move][column_move] == 'O') {
		cout << "This block is taken choose another block " << player << "." << endl;
		return false;
	}

	// check to see if integers are in bound
	if (row_move > 2  || column_move > 2) {
		cout << "Selected region out of bounds." << endl;
		return false;
	}
	
	if (marker == 'X') {
		this->board[row_move][column_move] = 'X';
	}
	if (marker == 'O') {
		this->board[row_move][column_move] = 'O';
	}

	return true;
}

bool Board::is_winner(string player, char marker) {
	if (this->board[0][0] == marker && this->board[0][1] == marker && this->board[0][2] == marker) {
		cout << "Well done " << player << " you have won.";
		return true;
	}
	if (this->board[1][0] == marker && this->board[1][1] == marker && this->board[1][2] == marker) {
		cout << "Well done " << player << " you have won.";
		return true;
	}
	if (this->board[2][0] == marker && this->board[2][1] == marker && this->board[2][2] == marker) {
		cout << "Well done " << player << " you have won.";
		return true;
	}
	if (this->board[0][0] == marker && this->board[1][0] == marker && this->board[2][0] == marker) {
		cout << "Well done " << player << " you have won.";
		return true;
	}
	if (this->board[0][1] == marker && this->board[1][1] == marker && this->board[2][1] == marker) {
		cout << "Well done " << player << " you have won.";
		return true;
	}
	if (this->board[0][2] == marker && this->board[1][2] == marker && this->board[2][2] == marker) {
		cout << "Well done " << player << " you have won.";
		return true;
	}
	if (this->board[0][0] == marker && this->board[1][1] == marker && this->board[2][2] == marker) {
		cout << "Well done " << player << " you have won.";
		return true;
	}
	if (this->board[2][0] == marker && this->board[1][1] == marker && this->board[0][2] == marker) {
		cout << "Well done " << player << " you have won.";
		return true;
	}
	return false;
}

bool Board::is_tie() {
	if (this->board[0][0] != ' ' && this->board[0][1] != ' ' && this->board[0][2] != ' ' 
		&& this->board[1][0] != ' ' && this->board[1][1] != ' '&& this->board[1][2] != ' '
		&& this->board[2][0] != ' '&& this->board[2][1] != ' '&& this->board[2][2] != ' ') {
		cout << "The game has been tied!";
		return true;
	}
	return false;
}