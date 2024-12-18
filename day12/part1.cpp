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

long	calc_region( vector<string> &garden, int x, int y ) {
	floodfill(garden, x, y, garden[y][x], '0');

	size_t	area = 0, perim = 0;

	for (size_t i = 0; i < garden.size(); i++) {
		for (size_t j = 0; j < garden[i].length(); j++) {
			if (garden[i][j] != '0')
				continue;
			area++;
			// Above || Below
			perim += (i == 0 || garden[i - 1][j] != '0') + (i == garden.size() - 1 || garden[i + 1][j] != '0');
			// Left || Right
			perim += (j == 0 || garden[i][j - 1] != '0') + (j == garden[i].length() - 1 || garden[i][j + 1] != '0');
		}
	}
	floodfill(garden, x, y, '0', '.');
	return area * perim;
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

		long	price = 0;
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