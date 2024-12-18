#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>
#include <unistd.h>

using namespace std;

struct coords {
	int	x;
	int	y;
};

bool	check_vert( deque<string> &map, coords pos, int y ) {
	coords	lhs, rhs;

	switch (map[pos.y][pos.x]) {
		case '#':
			return false;
		case '.':
			return true;
		case '[':
			lhs = (coords){ pos.x, pos.y + y };
			rhs = (coords){ pos.x + 1, pos.y + y };
			break;
		case ']':
			lhs = (coords){ pos.x - 1, pos.y + y };
			rhs = (coords){ pos.x, pos.y + y };
			break;
		default:
			return false;
	}
	return check_vert(map, lhs, y) && check_vert(map, rhs, y);
}

void	move_vert( deque<string> &map, coords pos, int y ) {
	coords lhs, rhs, lhs_n, rhs_n;

	switch (map[pos.y][pos.x]) {
		case '.':
			return;
		case '[':
			lhs = (coords){ pos.x, pos.y };
			rhs = (coords){ pos.x + 1, pos.y };
			lhs_n = (coords){ pos.x, pos.y + y };
			rhs_n = (coords){ pos.x + 1, pos.y + y };
			break;
		case ']':
			lhs = (coords){ pos.x - 1, pos.y };
			rhs = (coords){ pos.x, pos.y };
			lhs_n = (coords){ pos.x - 1, pos.y + y };
			rhs_n = (coords){ pos.x, pos.y + y };
			break;
		default:
			return;
	}

	move_vert(map, lhs_n, y);
	move_vert(map, rhs_n, y);

	map[lhs_n.y][lhs_n.x] = map[lhs.y][lhs.x];
	map[rhs_n.y][rhs_n.x] = map[rhs.y][rhs.x];
	map[lhs.y][lhs.x] = '.';
	map[rhs.y][rhs.x] = '.';
}

void	move_horiz( deque<string> &map, coords pos, int x ) {
	coords	box = {(pos.x + x) + (2 * x), pos.y};

	// Get furthest box
	while (map[pos.y][box.x] == map[pos.y][pos.x + x])
		box.x += 2 * x;

	if (map[pos.y][box.x] == '#')
		return;

	while (box.x != (pos.x + x)) {
		map[pos.y][box.x] = map[pos.y][box.x - x];
		box.x -= x;
	}

	map[pos.y][pos.x] = '.';
	map[pos.y][pos.x + x] = '@';
}

void	routine( deque<string> &map, coords bot, coords dir ) {
	if (map[bot.y + dir.y][bot.x + dir.x] == '#')
		return;

	if (map[bot.y + dir.y][bot.x + dir.x] == '.') {
		map[bot.y + dir.y][bot.x + dir.x] = '@';
		map[bot.y][bot.x] = '.';
		return;
	}

	if (dir.x != 0) {
		move_horiz(map, bot, dir.x);
		return;
	}
	else {
		coords	npos = (coords){ bot.x + dir.x, bot.y + dir.y };
		if (!check_vert(map, npos, dir.y))
			return;
		move_vert(map, npos, dir.y);
		map[bot.y][bot.x] = '.';
		map[bot.y + dir.y][bot.x] = '@';
	}

}

void	move_robot( deque<string> &map, char _dir ) {
	coords	dir, bot;
	dir = (coords){ 0, 0 };

	if (_dir == '^')
		dir.y -= 1;
	else if (_dir == 'v')
		dir.y += 1;
	else if (_dir == '>')
		dir.x += 1;
	else if (_dir == '<')
		dir.x -= 1;
	
	for (size_t y = 0; y < map.size(); y++) {
		bot.y = y;
		if (map[y].find('@') != string::npos) {
			bot.x = map[y].find('@');
			break;
		}
	}
	routine(map, bot, dir);
}

// Unfortunately causes a bit of screen tearing, takes about 11 minutes to run on the input
void	visualizer( deque<string> map, char dir ) {
	for (size_t i = 0; i < map.size(); i++)
		replace(map[i].begin(), map[i].end(), '.', ' ');

	cout << "\e[92m";
	system("clear");
	for (size_t x = 0; x < map.size(); x++) {
		if (map[x].find('@') != string::npos) {
			cout << map[x].substr(0, map[x].find('@'));
			cout << "\e[96m" << dir << "\e[92m";
			cout << map[x].substr(map[x].find('@') + 1) << endl;
		}
		else
			cout << map[x] << endl;
	}
	cout << "\e[0m";
	usleep(33333);
}

int	main( void ) {
	try {
		ifstream	file("input2");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string			line;
		deque<string>	map, moves;
		while (getline(file, line) && !line.empty())
			map.push_back(line);

		while (getline(file, line))
			moves.push_back(line);

		for (size_t i = 0; i < moves.size(); i++) {
			for (size_t j = 0; j < moves[i].length(); j++) {
				move_robot(map, moves[i][j]);
				visualizer(map, moves[i][j]); // Comment this line to run without the visualizer
			}
		}

		long	boxes = 0;
		for (size_t y = 0; y < map.size(); y++) {
			for (size_t x = 0; x < map[y].length(); x++) {
				if (map[y][x] == '[')
					boxes += ((y * 100) + x);
			}
		}

		// visualizer(map, '@'); // Uncomment this line to see just the final frame
		cout << "Sum of all boxes' GPS coordinates: " << boxes << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}