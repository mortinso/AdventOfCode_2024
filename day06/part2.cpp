#include <iostream>
#include <deque>
#include <fstream>
#include <tuple>
#include <set>

using namespace std;

bool	is_next_exit( deque<string> lab, int x, int y, char dir ) {
	if (y == 0 && dir == '^')
		return true;
	if (x == lab[y].length() - 1 && dir == '>' )
		return true;
	if (y == lab.size() - 1 && dir == 'V')
		return true;
	if (x == 0 && dir == '<')
		return true;
	return false;
}

bool	is_next_border( deque<string> lab, int x, int y, char dir ) {
	if (dir == '^' && lab[y - 1][x] == '#')
		return true;
	if (dir == '>' && lab[y][x + 1] == '#')
		return true;
	if (dir == 'V' && lab[y + 1][x] == '#')
		return true;
	if (dir == '<' && lab[y][x - 1] == '#')
		return true;
	return false;
}

char	rotate( char dir ) {
	if (dir == '^')
		return '>';
	else if (dir == '>')
		return 'V';
	else if (dir == 'V')
		return '<';
	else
		return '^';
}

int	is_loopable( deque<string> lab, pair<int, int> guard, pair<int, int> wall, char dir) {
	set<tuple<int, int, char> >	saved_positions;
	int							y = guard.second;
	int							x = guard.first;

	lab[wall.second][wall.first] = '#';

	int	i = 0;
	while (!is_next_exit(lab, x, y, dir)) {
		if (dir == '^') {
			saved_positions.insert({x, y, dir});
			if (is_next_border(lab, x, y, dir)) {
				dir = rotate(dir);
				continue;
			}
			y--;
		}
		else if (dir == 'V') {
			saved_positions.insert({x, y, dir});
			if (is_next_border(lab, x, y, dir)){
				dir = rotate(dir);
				continue;
			}
			y++;
		}
		else if (dir == '>') {
			saved_positions.insert({x, y, dir});
			if (is_next_border(lab, x, y, dir)){
				dir = rotate(dir);
				continue;
			}
			x++;
		}
		else if (dir == '<') {
			saved_positions.insert({x, y, dir});
			if (is_next_border(lab, x, y, dir)){
				dir = rotate(dir);
				continue;
			}
			x--;
		}
		if (saved_positions.size() != 0 && saved_positions.find({x, y, dir}) != saved_positions.end())
			return 1;
	}
	return 0;
}

int	guard_route( deque<string> lab, int x, int y) {
	char	dir;
	int		obstructions = 0;

	dir	= lab[y][x];
	while (!is_next_exit(lab, x, y, dir)) {

		if (is_next_border(lab, x, y, dir))
			dir = rotate(dir);
		
		while (dir == '^' && !is_next_exit(lab, x, y, dir) && !is_next_border(lab, x, y, dir)) {	// Move up
			if (lab[y - 1][x] != 'X')
				obstructions += is_loopable(lab, {x, y}, {x, y - 1}, dir);
			lab[y][x] = 'X';
			y--;
		}
		while (dir == '>' && !is_next_exit(lab, x, y, dir) && !is_next_border(lab, x, y, dir)) {	// Move right
			if (lab[y][x + 1] != 'X')
				obstructions += is_loopable(lab, {x, y}, {x + 1, y}, dir);
			lab[y][x] = 'X';
			x++;
		}
		while (dir == 'V' && !is_next_exit(lab, x, y, dir) && !is_next_border(lab, x, y, dir)) {	// Move down
			if (lab[y + 1][x] != 'X')
				obstructions += is_loopable(lab, {x, y}, {x, y + 1}, dir);
			lab[y][x] = 'X';
			y++;
		}
		while (dir == '<' && !is_next_exit(lab, x, y, dir) && !is_next_border(lab, x, y, dir)) {	// Move left
			if (lab[y][x - 1] != 'X')
				obstructions += is_loopable(lab, {x, y}, {x - 1, y}, dir);
			lab[y][x] = 'X';
			x--;
		}
	}
	return obstructions;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));
		
		string			line;
		deque<string>	lab;
		int				counter = 0;

		while (getline(file, line))
			lab.push_back(line);
		for (size_t y = 0; y < lab.size(); y++) {
			if (lab[y].find('^') != string::npos) {
				cout << "I'm not frozen, I'm just really really slow" << endl;
				counter = guard_route(lab, lab[y].find('^'), y);
				break;
			}
		}
		cout << "Distinct positions: " << counter << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}
