#include <iostream>
#include <string>
#include <thread>

#include "player.h"
#include "board.h"

using std::cout;
using std::endl;
using std::string;
using std::thread;

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
		// print hint if player 1 is close to victory
		board.hint(player1);
		// start player 1's timer
		thread player1_timer([&player1, &player2]() {
			player1.start_timer(player2);
		});
		// check to see if player 1's move is legit then write it to the board
		while (!(board.submit_move(player1))) {
			continue;
		}
		// stop and reset player 1's timer
		player1.stop_timer();
		player1_timer.join();
		player1.reset_timer();

		board.print_board();

		// player 2's turn
		// has player 1 won the game or is the game a tie?
		if (board.is_winner(player1) || board.is_tie()) {
			return 0;
		}
		// print hint if player 2 is close to victory
		board.hint(player2);
		// start player 2's timer
		thread player2_timer([&player2, &player1]() {
			player2.start_timer(player1);
		});
		// check to see if player 2's move is legit then write it to the board
		while (!(board.submit_move(player2))) {
			continue;
		}
		// stop and reset player 2's timer
		player2.stop_timer();
		player2_timer.join();
		player2.reset_timer();
	}

	return 0;
}