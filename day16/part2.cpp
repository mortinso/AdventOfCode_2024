#include <limits>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <deque>
#include <map>

using namespace std;

#define	HEIGHT 141
#define	WIDTH 141

typedef pair<int, int> Pair;


struct cell {
	map<Pair, long>	combos;
};

static map<Pair, char>			dir_chars;
static long						g_score = 0;
static deque<deque<string> >	paths;
static deque<string>			seats;

bool	is_safe( deque<string> maze, Pair pos, Pair dir ) {
	return (maze[pos.second + dir.second][pos.first + dir.first] == '.' || maze[pos.second + dir.second][pos.first + dir.first] == 'E');
}

bool	is_good_dir( cell _cell, Pair dir, long n_score ) {
	if (_cell.combos.find(dir) == _cell.combos.end()) {
		_cell.combos[dir] = __LONG_MAX__;
		return true;
	}
	if (_cell.combos[dir] >= n_score)
		return true;
	return false;
}

void	print_maze( deque<string> maze ) {
	for (size_t i = 0; i < maze.size(); i++)
		cout << maze[i] << endl;
	cout << endl;
}

int	get_seats( void ) {
	for (size_t i = 0; i < paths.size(); i++) {
		for (size_t j = 0; j < paths[i].size(); j++) {
			replace(paths[i][j].begin(), paths[i][j].end(), '<', 'O');
			replace(paths[i][j].begin(), paths[i][j].end(), '^', 'O');
			replace(paths[i][j].begin(), paths[i][j].end(), '>', 'O');
			replace(paths[i][j].begin(), paths[i][j].end(), 'v', 'O');
			replace(paths[i][j].begin(), paths[i][j].end(), 'E', 'O');
		}
	}
	seats = paths[0];
	for(size_t i = 1; i < paths.size(); i++) {
		for (size_t y = 0; y < paths[i].size(); y++) {
			for (size_t x = 0; x < paths[i][y].length(); x++) {
				if (paths[i][y][x] == 'O')
					seats[y][x] = 'O';
			}
		}
	}

	int	seat_counter = 0;
	for (size_t i = 0; i < seats.size(); i++) {
		for (size_t j = 0; j < seats[i].length(); j++) {
			if (seats[i][j] == 'O')
				seat_counter++;
		}
	}
	return seat_counter;
}

void	score_paths( deque<string> maze, cell cells[HEIGHT][WIDTH], Pair pos, Pair dir ) {
	if (g_score != 0 && cells[pos.second][pos.first].combos[dir] > g_score)
		return;
	if (maze[pos.second][pos.first] == 'E') {
		if (g_score != 0 && cells[pos.second][pos.first].combos[dir] < g_score)
			paths.clear();
		g_score = cells[pos.second][pos.first].combos[dir];
		paths.push_back(maze);
		return;
	}

	Pair	lhs, rhs;

	if (dir.first == 1) {
		lhs = make_pair(0, -1);
		rhs = make_pair(0, 1);
	}
	else if (dir.first == -1) {
		lhs = make_pair(0, 1);
		rhs = make_pair(0, -1);
	}
	if (dir.second == 1) {
		lhs = make_pair(1, 0);
		rhs = make_pair(-1, 0);
	}
	else if (dir.second == -1) {
		lhs = make_pair(-1, 0);
		rhs = make_pair(1, 0);
	}

	// forward
	Pair	next = make_pair(pos.first + dir.first, pos.second + dir.second);
	if (is_safe(maze, pos, dir) && is_good_dir(cells[next.second][next.first], dir, cells[pos.second][pos.first].combos[dir] + 1)) {
		cells[next.second][next.first].combos[dir] = cells[pos.second][pos.first].combos[dir] + 1;
		maze[pos.second][pos.first] = dir_chars[dir];
		score_paths(maze, cells, next, dir);
	}
	// turn left
	next = make_pair(pos.first + lhs.first, pos.second + lhs.second);
	if (is_safe(maze, pos, lhs) && is_good_dir(cells[next.second][next.first], dir, cells[pos.second][pos.first].combos[dir] + 1001)) {
		cells[next.second][next.first].combos[lhs] = cells[pos.second][pos.first].combos[dir] + 1001;
		maze[pos.second][pos.first] = dir_chars[lhs];
		score_paths(maze, cells, next, lhs);
	}
	// turn right
	next = make_pair(pos.first + rhs.first, pos.second + rhs.second);
	if (is_safe(maze, pos, rhs) && is_good_dir(cells[next.second][next.first], dir, cells[pos.second][pos.first].combos[dir] + 1001)) {
		cells[next.second][next.first].combos[rhs] = cells[pos.second][pos.first].combos[dir] + 1001;
		maze[pos.second][pos.first] = dir_chars[rhs];
		score_paths(maze, cells, next, rhs);
	}
}

void	calc_score( deque<string> &maze ) {
	Pair	start, fin;
	for (size_t i = 0; i < maze.size(); i++) {
		if (maze[i].find('S') != string::npos)
			start = (Pair){ (int)maze[i].find('S'), i };
	}

	dir_chars[make_pair(1, 0)] = '>';
	dir_chars[make_pair(-1, 0)] = '<';
	dir_chars[make_pair(0, 1)] = 'v';
	dir_chars[make_pair(0, -1)] = '^';

	cell	cells[HEIGHT][WIDTH];

	cells[start.second][start.first].combos[make_pair(1, 0)] = 0;

	score_paths(maze, cells, start, make_pair(1, 0));
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string			line;
		deque<string>	maze;
		while (getline(file, line))
			maze.push_back(line);

		cout << "Have patience, I'm REALLY slow" << endl << "Calculating..." << endl;
		calc_score(maze);

		int	chairs = get_seats();
		print_maze(seats);
		cout << "Number of seats: " << chairs << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}
