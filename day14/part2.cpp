// Arguably my worst AoC implementation so far this year, took like 30 minutes to test 10000 seconds

#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>
#include <ctime>

#define TIME 7500
#define WIDTH 101
#define HEIGHT 103

using namespace std;

struct	robot {
	pair<int, int>	pos;
	pair<int, int>	vel;
};

// Returns a visual representation of the map, with the guards being represented by '*'
deque<string>	build_frame( deque<robot> &troop ) {
	deque<string>	frame;
	string			line = "";
	bool			found = false;

	for (size_t y = 0; y < HEIGHT; y++) {
		for (size_t x = 0; x < WIDTH; x++) {
			for (size_t i = 0; i < troop.size(); i++) {
				if (troop[i].pos.first == x && troop[i].pos.second == y) {
					line += "*";
					found = true;
					break;
				}
			}
			if (found == false)
				line += ".";
			found = false;
		}
		line += "\0";
		frame.push_back(line);
		line.clear();
	}
	return frame;
}
static int	factor = 1;

// Creates a visual representation of the map and checks if it contains what looks like the top of a tree
void	check_frame( deque<robot> &troop, int sec ) {
	deque<string>	frame = build_frame(troop);
	bool			possible_tree = false;

	for (size_t i = 0; i < frame.size() - 3; i++) {
		if (frame[i].find("...*...") != string::npos && frame[i + 1].find("..***..") != string::npos &&
			frame[i + 2].find(".*****.") != string::npos && frame[i + 2].find("*******") != string::npos) {
			possible_tree = true;
			break;
		}
	}

	if (!possible_tree)
		return;

	sec++;
	// If a possible solution is found, yell it in the terminal and create a file with the visual representation
	cout << endl << "FRAME " << sec << " \e[34mPOSSIBLE\e[0m" << endl << endl;
	ofstream	file("Frame" + to_string(sec));
	for (size_t i = 0; i < frame.size(); i++)
		file << frame[i] << endl;
}

// Moves the guards around TIME times
void	move_around( deque<robot> &troop ) {
	for (size_t t = 0; t < TIME; t++) {
		for (size_t i = 0; i < troop.size(); i++) {
			troop[i].pos.first = (troop[i].pos.first + troop[i].vel.first % WIDTH);
			troop[i].pos.second = (troop[i].pos.second + troop[i].vel.second % HEIGHT);
			if (troop[i].pos.first < 0)
				troop[i].pos.first += WIDTH;
			else if (troop[i].pos.first >= WIDTH)
				troop[i].pos.first -= WIDTH;
			if (troop[i].pos.second < 0)
				troop[i].pos.second += HEIGHT;
			else if (troop[i].pos.second >= HEIGHT)
				troop[i].pos.second -= HEIGHT;
		}
		check_frame(troop, t);
	}
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string			line, arg;
		deque<robot>	troop;
		while (getline(file, line)) {
			istringstream	iss(line);
			robot			guard;

			getline(iss, arg, '=');
			getline(iss, arg, ',');
			guard.pos.first = atoi(arg.c_str());
			getline(iss, arg, ' ');
			guard.pos.second = atoi(arg.c_str());
			getline(iss, arg, '=');
			getline(iss, arg, ',');
			guard.vel.first = atoi(arg.c_str());
			getline(iss, arg);
			guard.vel.second = atoi(arg.c_str());
			troop.push_back(guard);
		}
		cout << "\e[93mWARNING THIS PROGRAM IS REALLY SLOW\e[0m" << endl;
		cout << "Calculating..." << endl;
		move_around(troop);
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}