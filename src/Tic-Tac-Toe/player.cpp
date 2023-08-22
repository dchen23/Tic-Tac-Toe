#include <iostream>
#include <string>

#include "player.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;
using std::stoi;
using std::isdigit;
using std::unique_lock;
using std::mutex;

Player::Player(char marker) : timeout { false } {
	cout << "Enter player " << count << "'s name: ";
	getline(cin, this->name);

	bool is_timer_set = false;
	string raw_timer;
	while (!is_timer_set) {
		cout << "Enter player " << count << "'s timer in seconds [3, 99]: ";
		getline(cin, raw_timer);
		is_timer_set = set_player_timer(std::move(raw_timer));
	}

	cout << this->name << "'s marker is " << marker << endl;
	this->marker = marker;

	++count;
}

string Player::get_name() {
	return this->name;
}

char Player::get_marker() {
	return this->marker;
}	

void Player::set_player_move() {
	cout << "Enter a move (" << this->marker << ") in " << this->timer << " seconds " << this->name << ": ";
	getline(cin, this->move);
}

bool Player::set_player_timer(const string&& raw_timer) {
	if (raw_timer.size() == 0) {
		cout << "Invalid Input[E]: Please enter a number [3, 99]." << endl;
		return false;
	}
	for (size_t i = 0; i < raw_timer.size(); ++i) {
		if (!isdigit(raw_timer[i])) {
			cout << "Invalid Input[NaN]: Please enter a number [3, 99]." << endl;
			return false;
		}
	}
	int input = stoi(raw_timer);
	if (input < 3 || input > 99) {
		cout << "Invalid Input[" << input << "]: Please enter a positive number [3, 99]." << endl;
		return false;
	}
	this->timer = input;
	return true;
}

void Player::start_timer(Player& opponent) {
	unique_lock<mutex> lock(this->mt);
	if (this->cv.wait_for(lock, std::chrono::seconds(this->timer), [this] { return this->timeout; })) {
		return;
	} else {
		cout << endl << this->name << " time's up." << endl;
		cout << opponent.get_name() << " you have won." << endl;
        std::exit(0); // Terminate the program
	}
}

void Player::stop_timer() {
	unique_lock<mutex> lock(this->mt);
	this->timeout = true;
	this->cv.notify_one();
}

void Player::reset_timer() {
	unique_lock<mutex> lock(this->mt);
	this->timeout = false;
}

string Player::get_player_move() {
	return this->move;
}