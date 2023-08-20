#include <iostream>
#include <string>

#include "player.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;

Player::Player(char marker) {
	cout << "Enter player " << count << "'s name: ";
	getline(cin, this->name);

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
	cout << "Enter a move (" << this->marker << ") " << this->name << ": ";
	getline(cin, this->move);
}

string Player::get_player_move() {
	return this->move;
}