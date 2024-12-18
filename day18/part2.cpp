#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>

#define	SIDE 71

using namespace std;

typedef pair<int, int>	Pair;

static deque<Pair>	incoming;
static char			mem_space[SIDE][SIDE + 1];

void	floodfill( Pair pos, deque<string> &maze ) {
	maze[pos.second][pos.first] = '0';

	// up
	if (pos.second > 0 && maze[pos.second - 1][pos.first] == '.')
		floodfill(make_pair(pos.first, pos.second - 1), maze);
	// down
	if (pos.second < SIDE - 1 && maze[pos.second + 1][pos.first] == '.')
		floodfill(make_pair(pos.first, pos.second + 1), maze);
	// left
	if (pos.first > 0 && maze[pos.second][pos.first - 1] == '.')
		floodfill(make_pair(pos.first - 1, pos.second), maze);
	// right
	if (pos.first < SIDE - 1 && maze[pos.second][pos.first + 1] == '.')
		floodfill(make_pair(pos.first + 1, pos.second), maze);
}

void	bytes_fall( void ) {
	// Fill mem_space with '.'
	for (size_t i = 0; i < SIDE; i++) {
		for (size_t j = 0; j < SIDE; j++)
			mem_space[i][j] = '.';
		mem_space[i][SIDE] = 0;
	}


	deque<string>	maze;
	size_t			i;

	for (size_t i = 0; i < incoming.size(); i++) {
		mem_space[incoming[i].second][incoming[i].first] = '#';
		for (size_t j = 0; j < SIDE; j++)
			maze.push_back(mem_space[j]);
		floodfill(make_pair(0, 0), maze);
		if (maze[SIDE - 1][SIDE - 1] != '0') {
			cout << "Byte that will block the path: " << incoming[i].first << "," << incoming[i].second << endl;
			break;
		}
		maze.clear();
	}

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