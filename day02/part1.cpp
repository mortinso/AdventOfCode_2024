#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

int	is_safe( vector<double> vec ) {
	bool	increasing = true;
	int		dif;

	if (vec[0] > vec[1])
		increasing = false;
	for (size_t i = 0; i < vec.size() - 1; i++) {
		// check if its not decreasing or increasing, if its decreasing when it should be increasing, or if its increasing when it should be decreasing
		if (vec[i] == vec[i + 1] || (increasing && vec[i] > vec[i + 1]) || (!increasing && vec[i] < vec[i + 1]))
			return 0;
		if (increasing)
			dif = vec[i + 1] - vec[i];
		else
			dif = vec[i] - vec[i + 1];
		if (dif > 3)
			return 0;
	}
	return 1;
}

int	main( void ) {
	try {
		ifstream	file("input");

		if (!file.is_open())
			throw(runtime_error("Failed to open file"));

		double	count = 0;
		string	line;
		vector<double> vec;
		while (getline(file, line)) {
			istringstream	istring(line);
			string			buf;

			// Push all to vec
			while (getline(istring, buf, ' '))
				vec.push_back(atof(buf.c_str()));

			count += is_safe(vec);
			vec.clear();
		}
		cout << "Safe reports: " << count << endl;
	}
	catch (const exception &e) { cerr << "Error " << e.what() << endl; }
}