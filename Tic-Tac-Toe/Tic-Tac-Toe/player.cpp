#include <iostream>
#include <string>
#include <ios>

#include "player.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::getline;

// globals
int count = 1;

// 	cout << player << "'s (" << marker << ")" << " turn to move.";

Player::Player(char marker) {
	cout << "Enter player " << count << "'s name: ";
	cin >> name;
	cin.ignore();

	cout << name << "'s marker is " << marker << endl;
	this->marker = marker;

	++count;
}

string Player::get_name() {
	return name;
}

char Player::get_marker() {
	return marker;
}	

string Player::get_player_move() {
	cout << "Enter a move: ";
	// 1 1
	// make check legit input
	// " 2"
	std::getline(cin, this->move);
	
	return this->move;
}