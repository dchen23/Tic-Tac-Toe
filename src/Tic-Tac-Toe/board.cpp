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
using std::stoi;
using std::isdigit;

#define X 'X'
#define O 'O'
#define TO_INDEX 1

Board::Board() :
	board{ { ' ' , ' ' , ' ' }, { ' ' , ' ' , ' ' }, { ' ' , ' ' , ' ' } } {
	this->empty_tiles = 9;
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

// prompt user for input then write to board
bool Board::submit_move(Player& player) {
	// prompt user for input
	player.set_player_move();

	// checks to see if input is size 3 and contains a space in the middle 1 1
	if (player.get_player_move().size() != 3 || player.get_player_move()[1] != ' ' || !(isdigit(player.get_player_move()[0])) || !(isdigit(player.get_player_move()[2]))) {
		cout << "Invalid Input " << player.get_name() << ": Please enter a column then a row (Example: 1 1)." << endl;
		return false;
	}

	// convert char input into string
	unsigned int column_move = stoi(string(1, player.get_player_move()[0])) - TO_INDEX;
	unsigned int row_move = stoi(string(1, player.get_player_move()[2])) - TO_INDEX;

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

// check to see if player has a winning position
bool Board::is_winner(Player& opponent) {

	// check row
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3 ; ++j) {
			if (this->board[i][j] != opponent.get_marker()) {
				break;
			}
			if (j == 2) {
				cout << "Well done " << opponent.get_name() << " you have won." << endl;
				return true;
			}
		}
	}

	// check column
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (this->board[j][i] != opponent.get_marker()) {
				break;
			}
			if (j == 2) {
				cout << "Well done " << opponent.get_name() << " you have won." << endl;
				return true;
			}
		}
	}

	// check diagonal
	for (int i = 0; i < 3; ++i) {
		if (this->board[i][i] != opponent.get_marker()) {
			break;
		}
		if (i == 2) {
			cout << "Well done " << opponent.get_name() << " you have won." << endl;
			return true;
		}
	}

	// check inverse diagonal
	for (int i = 0, j = 2; i < 3; ++i, --j) {
		if (this->board[j][i] != opponent.get_marker()) {
			break;
		}
		if (i == 2) {
			cout << "Well done " << opponent.get_name() << " you have won." << endl;
			return true;
		}
	}
	
	return false;
}

void Board::hint(Player& player) {
	int player_tiles;
	int emply_tiles;
	std::pair<int, int> winning_position;

	// check row
	for (int i = 0; i < 3; ++i) {
		player_tiles = 0;
		emply_tiles = 0;
		for (int j = 0; j < 3 ; ++j) {
			if (this->board[i][j] == player.get_marker()) {
				++player_tiles;
			} else if (this->board[i][j] == ' ') {
				winning_position = std::make_pair(j, i);
				++emply_tiles;
			}
			if (player_tiles == 2 && emply_tiles == 1) {
				cout << "Hint: placing " << player.get_marker() << " at position (" << winning_position.first + TO_INDEX << ", " <<
					winning_position.second + TO_INDEX << ") will win the game!" << endl;
				break;
			}
		}
	}

	// check column
	for (int i = 0; i < 3; ++i) {
		player_tiles = 0;
		emply_tiles = 0;
		for (int j = 0; j < 3 ; ++j) {
			if (this->board[j][i] == player.get_marker()) {
				++player_tiles;
			} else if (this->board[j][i] == ' ') {
				winning_position = std::make_pair(i, j);
				++emply_tiles;
			}
			if (player_tiles == 2 && emply_tiles == 1) {
				cout << "Hint: placing " << player.get_marker() << " at position (" << winning_position.first + TO_INDEX << ", " <<
					winning_position.second + TO_INDEX << ") will win the game!" << endl;
				break;
			}
		}
	}

	// check diagonal
	player_tiles = 0;
	emply_tiles = 0;
	for (int i = 0; i < 3; ++i) {
		if (this->board[i][i] == player.get_marker()) {
			++player_tiles;
		} else if (this->board[i][i] == ' ') {
			winning_position = std::make_pair(i, i);
			++emply_tiles;
		}
		if (player_tiles == 2 && emply_tiles == 1) {
			cout << "Hint: placing " << player.get_marker() << " at position (" << winning_position.first + TO_INDEX << ", " <<
				winning_position.second + TO_INDEX << ") will win the game!" << endl;
			break;
		}
	}

	// check inverse diagonal
	player_tiles = 0;
	emply_tiles = 0;
	for (int i = 0, j = 2; i < 3; ++i, --j) {
		if (this->board[j][i] == player.get_marker()) {
			++player_tiles;
		} else if (this->board[j][i] == ' ') {
			winning_position = std::make_pair(i, j);
			++emply_tiles;
		}
		if (player_tiles == 2 && emply_tiles == 1) {
			cout << "Hint: placing " << player.get_marker() << " at position (" << winning_position.first + TO_INDEX << ", " <<
				winning_position.second + TO_INDEX << ") will win the game!" << endl;
			break;
		}
	}
}

bool Board::is_tie() {
	// if there are no empty tiles then it is a tie
	if (this->empty_tiles == 0) {
		cout << "The game has been tied!" << endl;
		return true;
	}

	return false;
}