#include <iostream>
#include <string>

#include "player.h"
#include "board.h"

using std::cout;
using std::endl;
using std::string;

#define TITLE "Tic-Tac-Toe"

int main() {
	// display title
	string padding = string(11, '*');
	cout << padding << endl << TITLE << endl << padding << endl;

	// initialise objects
	Player player1('X');
	Player player2('O');
	Board board;

	// game loop
	while (true) {
		board.print_board();
		// player 1's turn
		// has player 2 won the game or is the game a tie?
		if (board.is_winner(player2) || board.is_tie()) {
			return 0;
		}
		// check to see if player 1's move is legit then write it to the board
		while (!(board.submit_move(player1))) {
			continue;
		}
		board.print_board();

		// player 2's turn
		// has player 1 won the game or is the game a tie?
		if (board.is_winner(player1) || board.is_tie()) {
			return 0;
		}
		// check to see if player 2's move is legit then write it to the board
		while (!(board.submit_move(player2))) {
			continue;
		}
	}

	return 0;
}