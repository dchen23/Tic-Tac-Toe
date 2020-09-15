#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cstdlib>

#include "board.h"
#include "player.h"

using std::cout;
using std::endl;
using std::cin;
using std::setw;
using std::string;
using std::atoi;
using std::isdigit;

#define X 'X'
#define O 'O'
#define CHAR_TO_INT 48 - 1

Board::Board() :
	board{ { ' ' , ' ' , ' ' }, { ' ' , ' ' , ' ' }, { ' ' , ' ' , ' ' } } {
	this->empty_tiles = 9;
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

bool Board::submit_move(string move, Player player) {
	// checks to see if input is size 3 and contains a space in the middle 1 1
	if (move.size() != 3 || move[1] != ' ' || !(isdigit(move[0])) || !(isdigit(move[2]))) {
		cout << "Invalid Input " << player.get_name() << ": Please enter a column then a row (Example: 1 1)." << endl;
		return false;
	}

	// convert char input into string
	unsigned int column_move = (int)move[0] - CHAR_TO_INT;
	unsigned int row_move = (int)move[2] - CHAR_TO_INT;

	// check to see if integers are in bound
	if (row_move > 2 || column_move > 2) {
		cout << "Selected region out of bounds." << endl;
		return false;
	}

	// check to see if current sqaure is taken
	if (this->board[row_move][column_move] == X || this->board[row_move][column_move] == O) {
		cout << "This square is taken " << player.get_name() << "." << endl;
		return false;
	}

	this->board[row_move][column_move] = player.get_marker();

	// keep track of empty tiles for Board::is_tie() function
	--(this->empty_tiles);

	return true;
}

// check to see if player has 1 out of the 8 winning positions
bool Board::is_winner(Player player) {
	if (this->board[0][0] == player.get_marker() && this->board[0][1] == player.get_marker() && this->board[0][2] == player.get_marker()) {
		cout << "Well done " << player.get_name() << " you have won.";
		return true;
	}
	if (this->board[1][0] == player.get_marker() && this->board[1][1] == player.get_marker() && this->board[1][2] == player.get_marker()) {
		cout << "Well done " << player.get_name() << " you have won.";
		return true;
	}
	if (this->board[2][0] == player.get_marker() && this->board[2][1] == player.get_marker() && this->board[2][2] == player.get_marker()) {
		cout << "Well done " << player.get_name() << " you have won.";
		return true;
	}
	if (this->board[0][0] == player.get_marker() && this->board[1][0] == player.get_marker() && this->board[2][0] == player.get_marker()) {
		cout << "Well done " << player.get_name() << " you have won.";
		return true;
	}
	if (this->board[0][1] == player.get_marker() && this->board[1][1] == player.get_marker() && this->board[2][1] == player.get_marker()) {
		cout << "Well done " << player.get_name() << " you have won.";
		return true;
	}
	if (this->board[0][2] == player.get_marker() && this->board[1][2] == player.get_marker() && this->board[2][2] == player.get_marker()) {
		cout << "Well done " << player.get_name() << " you have won.";
		return true;
	}
	if (this->board[0][0] == player.get_marker() && this->board[1][1] == player.get_marker() && this->board[2][2] == player.get_marker()) {
		cout << "Well done " << player.get_name() << " you have won.";
		return true;
	}
	if (this->board[2][0] == player.get_marker() && this->board[1][1] == player.get_marker() && this->board[0][2] == player.get_marker()) {
		cout << "Well done " << player.get_name() << " you have won.";
		return true;
	}
	return false;
}

bool Board::is_tie() {
	// if there are no empty tiles then it is a tie
	if (this->empty_tiles == 0) {
		cout << "The game has been tied!";
		return true;
	}

	return false;
}