#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

double	get_similarity( vector<double> vec, double num ) {
	double	occ = 0;

	for (size_t i = 0; i < vec.size(); i++) {
		if (vec[i] == num)
			occ++;
	}
	return occ * num;
}


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

		double	similarity = 0;

		for (size_t i = 0; i < a.size() || i < b.size(); i++) {
			similarity += get_similarity(b, a[i]);
		}

		cout << "Total similarity: " << setprecision(numeric_limits<double>::max_digits10) << similarity << endl;
	}
	catch (const exception &e) { cout << "Error " << e.what() << endl; }
}