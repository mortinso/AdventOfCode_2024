#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int	xmas_counter( vector<string> vec, int x, int y ) {
	int	counter = 0;

	//vertical
	if (y < vec.size() - 3 && vec[y + 1][x] == 'M' && vec[y + 2][x] == 'A' && vec[y + 3][x] == 'S')
		counter++;
	//vertical upside down
	if (y >= 3 && vec[y - 1][x] == 'M' && vec[y - 2][x] == 'A' && vec[y - 3][x] == 'S')
		counter++;
	// horizontal
	if (x < vec[y].length() - 3 && vec[y][x + 1] == 'M' && vec[y][x + 2] == 'A' && vec[y][x + 3] == 'S')
		counter++;
	// horizontal backwards
	if (x >= 3 && vec[y][x - 1] == 'M' && vec[y][x - 2] == 'A' && vec[y][x - 3] == 'S')
		counter++;
	// diagonal right down
	if (x < vec[y].length() - 3 && y < vec.size() - 3 && vec[y + 1][x + 1] == 'M' && vec[y + 2][x + 2] == 'A' && vec[y + 3][x + 3] == 'S')
		counter++;
	// diagonal right up
	if (x < vec[y].length() - 3 && y >= 3 && vec[y - 1][x + 1] == 'M' && vec[y - 2][x + 2] == 'A' && vec[y - 3][x + 3] == 'S')
		counter++;
	// diagonal left down
	if (x >= 3 && y < vec.size() - 3 && vec[y + 1][x - 1] == 'M' && vec[y + 2][x - 2] == 'A' && vec[y + 3][x - 3] == 'S')
		counter++;
	// diagonal left up
	if (x >= 3 && y >= 3 && vec[y - 1][x - 1] == 'M' && vec[y - 2][x - 2] == 'A' && vec[y - 3][x - 3] == 'S')
		counter++;

	return counter;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw (runtime_error("Failed to open input file"));

		string			line;
		vector<string>	vec;

		while (getline(file, line))
			vec.push_back(line);

		int	counter = 0;
		for (size_t y = 0; y < vec.size(); y++) {
			for (size_t x = 0; x < vec[y].length(); x++) {
				if (vec[y][x] == 'X')
					counter += xmas_counter(vec, x, y);
			}
		}

		cout << "Result: " << counter << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}