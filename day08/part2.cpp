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
	deque<string>	city(_city);
	pair<int, int>	next, dif, pos;

	for (size_t y = 0; y < _city.size(); y++) {
		for (size_t x = 0; x < _city[y].length(); x++) {
			if (_city[y][x] != '.') {
				next = next_antena( _city, x, y, _city[y][x]);
				if (next.first != -1)
					city[next.second][next.first] = '#';
				while (next.first != -1) {
					dif.second = next.second - y;
					if (next.first > x) {
						dif.first = next.first - x;
						pos.first = next.first;
						pos.second = next.second;

						while (is_valid(_city, pos.first - dif.first, pos.second - dif.second)) {
							city[pos.second - dif.second][pos.first - dif.first] = '#';
							pos.first -= dif.first;
							pos.second -= dif.second;
						}

						pos.first = next.first;
						pos.second = next.second;

						while (is_valid(_city, pos.first + dif.first, pos.second + dif.second)) {
							city[pos.second + dif.second][pos.first + dif.first] = '#';
							pos.first += dif.first;
							pos.second += dif.second;
						}
					}
					else {
						dif.first = x - next.first;
						pos.first = next.first;
						pos.second = next.second;

						while (is_valid(_city, pos.first + dif.first, pos.second - dif.second)) {
							city[pos.second - dif.second][pos.first + dif.first] = '#';
							pos.first += dif.first;
							pos.second -= dif.second;
						}

						pos.first = next.first;
						pos.second = next.second;

						while (is_valid(_city, pos.first - dif.first, pos.second + dif.second)) {
							city[pos.second + dif.second][pos.first - dif.first] = '#';
							pos.first -= dif.first;
							pos.second += dif.second;
						}
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