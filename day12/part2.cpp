#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void	floodfill( vector<string> &garden, int x, int y, char plant, char sub ) {
	if (y < 0 || x < 0 || y >= garden.size() || x >= garden[y].length() || garden[y][x] != plant)
		return;

	garden[y][x] = sub;

	floodfill(garden, x + 1, y, plant, sub);
	floodfill(garden, x - 1, y, plant, sub);
	floodfill(garden, x, y + 1, plant, sub);
	floodfill(garden, x, y - 1, plant, sub);
}

int	outside_corners( vector<string> &garden, int x, int y ) {
	int	corners = 0;

	// Up-left corner
	if ((y == 0 && x == 0) || (x == 0 && garden[y - 1][x] != '0') || (y == 0 && garden[y][x - 1] != '0') || 
		(y > 0 && x > 0 && garden[y - 1][x] != '0' && garden[y][x - 1] != '0'))
			corners++;

	// Up-right corner
	if ((y == 0 && x == garden[y].length() - 1) || (x == garden[y].length() - 1 && garden[y - 1][x] != '0') ||
		(y == 0 && garden[y][x + 1] != '0') || (x < garden[y].length() - 1 && y > 0 && garden[y - 1][x] != '0' &&
			garden[y][x + 1] != '0'))
			corners++;

	// Down-left corner
	if ((y == garden.size() - 1 && x == 0) || (x == 0 && garden[y + 1][x] != '0') || (y == garden.size() - 1 &&
		garden[y][x - 1] != '0') || (y < garden.size() - 1 && x > 0 && (garden[y + 1][x] != '0' && garden[y][x - 1] != '0')))
			corners++;

	// Down-right corner
	if ((y == garden.size() - 1 && x == garden[y].length() - 1) || (x == garden[y].length() - 1 && garden[y + 1][x] != '0') ||
		(y == garden.size() - 1 && garden[y][x + 1] != '0') || (y < garden.size() - 1 && x < garden[y].length() - 1 &&
		(garden[y + 1][x] != '0' && garden[y][x + 1] != '0')))
			corners++;

	return corners;
}

int	inside_corners( vector<string> &garden, int x, int y ) {
	int	corners = 0;

	// Up-left corner
	if (y > 0 && x > 0 && garden[y - 1][x] == '0' && garden[y][x - 1] == '0' && garden[y - 1][x - 1] != '0')
		corners++;

	// Up-right corner
	if (y > 0 && x < garden[y].length() - 1 && garden[y - 1][x] == '0' && garden[y][x + 1] == '0' && garden[y - 1][x + 1] 
		!= '0')
		corners++;

	// Down-left corner
	if (y < garden.size() - 1 && x > 0 && garden[y + 1][x] == '0' && garden[y][x - 1] == '0' && garden[y + 1][x - 1] != '0')
		corners++;

	// Down-right corner
	if (y < garden.size() - 1 && x < garden[y].length() - 1 && garden[y + 1][x] == '0' && garden[y][x + 1] == '0' && 
		garden[y + 1][x + 1] != '0')
		corners++;

	return corners;
}

size_t	calc_region( vector<string> &garden, int x, int y ) {
	// Change plant to '0' to avoid looking at other regions with the same plant
	floodfill(garden, x, y, garden[y][x], '0');

	size_t	area = 0;
	size_t	sides = 0;

	for (size_t i = 0; i < garden.size(); i++) {
		for (size_t j = 0; j < garden[i].length(); j++) {
			if (garden[i][j] != '0')
				continue;
			area++;
			sides += outside_corners(garden, j, i);
			sides += inside_corners(garden, j, i);
		}
	}
	// Change plant to '.' to be ignored in the future
	floodfill(garden, x, y, '0', '.');
	return area * sides;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string			line;
		vector<string>	garden;
		while (getline(file, line))
			garden.push_back(line);

		size_t	price = 0;
		for (size_t y = 0; y < garden.size(); y++) {
			for (size_t x = 0; x < garden[y].length(); x++) {
				if (garden[y][x] != '.')
					price += calc_region(garden, x, y);
			}
		}

		cout << "Total price: " << price << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}