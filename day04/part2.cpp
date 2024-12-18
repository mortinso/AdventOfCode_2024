#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int	xmas_counter( vector<string> vec, int x, int y ) {
	bool	x_mas = false;

	if (!(x >= 1 && x < vec[y].length() - 1 && y >= 1 && y < vec.size() - 1))
		return 0;

	// 1st if:	X..			2nd if:	..X
	//			.A.					.A.
	//			..X					X..
	if (vec[y + 1][x - 1] == 'M' && vec[y - 1][x + 1] == 'S' || vec[y + 1][x - 1] == 'S' && vec[y - 1][x + 1] == 'M') {
		if (vec[y - 1][x - 1] == 'M' && vec[y + 1][x + 1] == 'S' || vec[y - 1][x - 1] == 'S' && vec[y + 1][x + 1] == 'M')
			x_mas = true;
	}

	return x_mas;
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
				if (vec[y][x] == 'A')
					counter += xmas_counter(vec, x, y);
			}
		}

		cout << "Result: " << counter << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}