#ifndef GUARD_BOARD_H
#define GUARD_BOARD_H

#include <vector>
#include "player.h"

class Board {
public:
	Board();
	void print_board();
	bool submit_move(Player& player);
	bool is_winner(Player& opponent);
	bool is_tie();
	void hint(Player& player);

	// For unit testing
	void set_board(const std::vector<std::vector<char>>&);
	bool is_legit();

private:
	char board[3][3];
	unsigned int empty_tiles;
};

#endif