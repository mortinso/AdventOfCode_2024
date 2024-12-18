#include <iostream>
#include <deque>
#include <fstream>

using namespace std;

bool	is_next_exit( deque<string> lab, int x, int y ) {
	if (y == 0 && lab[y][x] == '^')
		return true;
	if (x == lab[y].length() - 1 && lab[y][x] == '>' )
		return true;
	if (y == lab.size() - 1 && lab[y][x] == 'V')
		return true;
	if (x == 0 && lab[y][x] == '<')
		return true;
	return false;
}

bool	is_next_border( deque<string> lab, int x, int y ) {
	if (lab[y][x] == '^' && lab[y - 1][x] == '#')
		return true;
	if (lab[y][x] == '>' && lab[y][x + 1] == '#')
		return true;
	if (lab[y][x] == 'V' && lab[y + 1][x] == '#')
		return true;
	if (lab[y][x] == '<' && lab[y][x - 1] == '#')
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

int	count_x( deque<string> lab ) {
	int	counter = 0;
	for (size_t y = 0; y < lab.size(); y++) {
		for (size_t x = 0; x < lab[y].length(); x++) {
			if (lab[y][x] == 'X')
				counter++;
		}
	}
	return counter;
}

int	guard_route( deque<string> lab, int x, int y) {
	while (!is_next_exit(lab, x, y)) {

		if (is_next_border(lab, x, y))
			lab[y][x] = rotate(lab[y][x]);
		
		while (lab[y][x] == '^' && !is_next_exit(lab, x, y) && !is_next_border(lab, x, y)) {	// Move up
			lab[y][x] = 'X';
			lab[--y][x] = '^';
		}
		while (lab[y][x] == '>' && !is_next_exit(lab, x, y) && !is_next_border(lab, x, y)) {	// Move right
			lab[y][x] = 'X';
			lab[y][++x] = '>';
		}
		while (lab[y][x] == 'V' && !is_next_exit(lab, x, y) && !is_next_border(lab, x, y)) {	// Move down
			lab[y][x] = 'X';
			lab[++y][x] = 'V';
		}
		while (lab[y][x] == '<' && !is_next_exit(lab, x, y) && !is_next_border(lab, x, y)) {	// Move left
			lab[y][x] = 'X';
			lab[y][--x] = '<';
		}
	}
	if (is_next_exit(lab, x, y))
		lab[y][x] = 'X';
	return count_x(lab);
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
		for (size_t i = 0; i < lab.size(); i++) {
			if (lab[i].find('^') != string::npos) {
				counter = guard_route(lab, lab[i].find('^'), i);
				break;
			}
		}
		cout << "Distinct positions: " << counter << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}