#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>

using namespace std;

bool	is_valid( deque<string> city, int x, int y ) {
	if (y < 0 || y >= city.size() || x < 0 || x >= city[y].length())
		return false;
	return true;
}

pair<int, int>	next_antena( deque<string> city, int x, int y , char id ) {
	pair<int, int>	next(-1, -1);

	x++;

	while (y < city.size()) {
		while (x < city[y].length()) {
			if (city[y][x] == id) {
				next.first = x;
				next.second = y;
				return next;
			}
			x++;
		}
		x = 0;
		y++;
	}
	return next;
}

int	count_antinodes( deque<string> city ) {
	int	counter = 0;

	for (size_t y = 0; y < city.size(); y++) {
		for (size_t x = 0; x < city[y].length(); x++)
			counter += (city[y][x] == '#');
	}

	return counter;
}

int	radar( deque<string> _city ) {
	deque<string> city(_city);
	pair<int, int>	next;

	for (size_t y = 0; y < _city.size(); y++) {
		for (size_t x = 0; x < _city[y].length(); x++) {
			if (_city[y][x] != '.') {
				next = next_antena( _city, x, y, _city[y][x]);
				while (next.first != -1) {
					if (next.first > x) {
						if (is_valid(_city, x - (next.first - x), y - (next.second - y)))
							city[y - (next.second - y)][x - (next.first - x)] = '#';
						if (is_valid(_city, next.first * 2 - x, next.second * 2 - y))
							city[next.second * 2 - y][next.first * 2 - x] = '#';
					}
					else {
						if (is_valid(_city, x * 2 - next.first, y - (next.second - y)))
							city[y - (next.second - y)][x * 2 - next.first] = '#';
						if (is_valid(_city, next.first - (x - next.first), next.second * 2 - y))
							city[next.second * 2 - y][next.first - (x - next.first)] = '#';
					}
					next = next_antena(_city, next.first, next.second, _city[y][x]);
				}
			}
		}
	}

	return (count_antinodes(city));
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));
		
		string			line;
		deque<string>	city;

		while (getline(file, line))
			city.push_back(line);

		cout << "Antinodes: " << radar(city) << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}