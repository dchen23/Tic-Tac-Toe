#ifndef GUARD_PLAYER_H
#define GUARD_PLAYER_H

#include <string>

class Player {
public:
	Player(char);
	std::string get_name();
	char get_marker();
	std::string get_player_move();

private:
	std::string name;
	char marker;
	std::string move;
};

#endif