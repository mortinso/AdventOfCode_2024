#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>

#define	SIDE 71
#define	NUM_BYTES 1024

using namespace std;

typedef pair<int, int>	Pair;

static deque<Pair>		incoming;
static deque<string>	path;
static char				mem_space[SIDE][SIDE + 1];
static long				cells[SIDE][SIDE];
static long				num_moves = 0;;

void	move( Pair pos, deque<string> maze ) {
	if (pos == make_pair(SIDE - 1, SIDE - 1)) {
		maze[pos.second][pos.first] = '0';
		if (num_moves == 0 || cells[pos.second][pos.first] < num_moves) {
			num_moves = cells[pos.second][pos.first];
			path = maze;
		}
		return;
	}

	// right
	if (pos.first < SIDE - 1 && maze[pos.second][pos.first + 1] == '.' && cells[pos.second][pos.first] + 1 < cells[pos.second][pos.first + 1]) {
		cells[pos.second][pos.first + 1] = cells[pos.second][pos.first] + 1;
		maze[pos.second][pos.first] = '0';
		move(make_pair(pos.first + 1, pos.second), maze);
	}
	// down
	if (pos.second < SIDE - 1 && maze[pos.second + 1][pos.first] == '.' && cells[pos.second][pos.first] + 1 < cells[pos.second + 1][pos.first]) {
		cells[pos.second + 1][pos.first] = cells[pos.second][pos.first] + 1;
		maze[pos.second][pos.first] = '0';
		move(make_pair(pos.first, pos.second + 1), maze);
	}
	// left
	if (pos.first > 0 && maze[pos.second][pos.first - 1] == '.' && cells[pos.second][pos.first] + 1 < cells[pos.second][pos.first - 1]) {
		cells[pos.second][pos.first - 1] = cells[pos.second][pos.first] + 1;
		maze[pos.second][pos.first] = '0';
		move(make_pair(pos.first - 1, pos.second), maze);
	}
	// up
	if (pos.second > 0 && maze[pos.second - 1][pos.first] == '.' && cells[pos.second][pos.first] + 1 < cells[pos.second - 1][pos.first]) {
		cells[pos.second - 1][pos.first] = cells[pos.second][pos.first] + 1;
		maze[pos.second][pos.first] = '0';
		move(make_pair(pos.first, pos.second - 1), maze);
	}
}

void	bytes_fall( void ) {
	// Fill mem_space with '.'
	for (size_t i = 0; i < SIDE; i++) {
		for (size_t j = 0; j < SIDE; j++)
			mem_space[i][j] = '.';
		mem_space[i][SIDE] = 0;
	}

	// Init cells
	for (size_t i = 0; i < SIDE; i++) {
		for (size_t j = 0; j < SIDE; j++) {
			cells[i][j] = __LONG_MAX__;
		}
	}

	cells[0][0] = 0;

	// Mark fallen with '#'
	for (size_t i = 0; i < NUM_BYTES; i++)
		mem_space[incoming[i].second][incoming[i].first] = '#';
	mem_space[0][0] = '0';

	deque<string>	maze;
	for (size_t i = 0; i < SIDE; i++) {
		maze.push_back(mem_space[i]);
	}

	move(make_pair(0,0), maze);
	for (size_t i = 0; i < SIDE; i++)
		cout << path[i] << endl;

	cout << num_moves << endl;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));
		
		string	line;
		while (getline(file, line)) { // Build incoming
			istringstream	iss(line);
			Pair			byte;
			string			arg;
			getline(iss, arg, ',');
			byte.first = atoi(arg.c_str());
			getline(iss, arg);
			byte.second = atoi(arg.c_str());
			incoming.push_back(byte);
		}

		cout << "Calculating..." << endl;
		bytes_fall();
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}