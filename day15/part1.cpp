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

bool	mover_loop( deque<string> &map, coords pos, coords dir ) {
	if (map[pos.y + dir.y][pos.x + dir.x] == '#')
		return false;
	
	if (map[pos.y + dir.y][pos.x + dir.x] == '.') {
		map[pos.y + dir.y][pos.x + dir.x] = map[pos.y][pos.x];
		map[pos.y][pos.x] = '.';
		return true;
	}
	coords	tmp;
	tmp.x = pos.x + dir.x;
	tmp.y = pos.y + dir.y;
	if (mover_loop(map, tmp, dir)) {
		map[tmp.y][tmp.x] = map[pos.y][pos.x];
		map[pos.y][pos.x] = '.';
		return true;
	}
	return false;
}

void	move_robot( deque<string> &map, char _dir ) {
	coords	dir, bot;
	dir.x = 0;
	dir.y = 0;

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
	mover_loop(map, bot, dir);
}

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
		ifstream	file("input");
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
				if (map[y][x] == 'O')
					boxes += ((y * 100) + x);
			}
		}

		// visualizer(map, '@'); // Uncomment this line to see the final output
		cout << "Sum of all boxes' GPS coordinates: " << boxes << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}