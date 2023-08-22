#ifndef GUARD_PLAYER_H
#define GUARD_PLAYER_H

#include <string>
#include <mutex>
#include <condition_variable>

class Player {
public:
	Player(char);
	std::string get_name();
	char get_marker();
	void set_player_move();
	std::string get_player_move();
	void start_timer(Player&);
	void stop_timer();
	void reset_timer();

private:
	std::string name;
	char marker;
	int timer;
	bool timeout;
	std::mutex mt;
	std::condition_variable cv;
	std::string move;
	static inline int count { 1 };
	bool set_player_timer(const std::string&&);
};

#endif