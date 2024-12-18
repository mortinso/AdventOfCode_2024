#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int	main( void ) {
	try {
		ifstream file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input"));
		if (file.eof())
			throw (runtime_error("Empty file"));

		std::vector<double>	a;
		std::vector<double>	b;
		string				line;
		string				first, second;

		// Build vectors
		while (getline(file, line)) {

			istringstream istring(line);

			istring >> first >> second;
			a.push_back(atof(first.c_str()));
			b.push_back(atof(second.c_str()));
		}

		// Sort vectors
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());

		double	dist = 0;
		// Add up the distance between the numbers in each vector
		for (size_t i = 0; i < a.size() || i < b.size(); i++) {
			if (a[i] > b[i])
				dist += a[i] - b[i];
			else
				dist += b[i] - a[i];
		}

		cout << "Total distance: " << setprecision(numeric_limits<double>::max_digits10) << dist << endl;
	}
	catch (const exception &e) { cout << "Error " << e.what() << endl; }
}