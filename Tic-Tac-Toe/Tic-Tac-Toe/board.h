#ifndef GUARD_BOARD_H
#define GUARD_BOARD_H

class Board {
public:
	Board();
	char** get_game_board();
	void print_board();
	bool submit_move(std::string, std::string, char);
	bool is_winner(std::string, char);
	bool is_tie();

private:
	char board[3][3];
};

#endif