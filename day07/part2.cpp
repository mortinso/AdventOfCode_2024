#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

//	Returns the concatenated numbers
double	concatenate( long long a, long long	 b ) {
	return atof((to_string(a) + to_string(b)).c_str());
}

bool	is_good( vector<double> vec, double num, int pos ) {
	if (pos == vec.size())
		return (num == vec[0]);

	if (pos == 1)
		return (is_good(vec, vec[1] + vec[2], 3) || is_good(vec, vec[1] * vec[2], 3) || is_good(vec, concatenate(vec[1], vec[2]), 3));

	return (is_good(vec, num + vec[pos], pos + 1) || is_good(vec, num * vec[pos], pos + 1) || is_good(vec, concatenate(num, vec[pos]), pos + 1));
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		double	result = 0;
		string	line;

		cout << "Calculating..." << endl;
		while (getline(file, line)) {
			istringstream	istring(line);
			string			arg;
			vector<double>	operands;

			getline(istring, arg, ':');
			operands.push_back(atof(arg.c_str()));
	
			getline(istring, arg, ' ');

			while (getline(istring, arg, ' '))
				operands.push_back(atof(arg.c_str()));

			if (is_good(operands, 0, 1))
				result += operands[0];
		}
		cout << "Final result: " << setprecision(numeric_limits<double>::max_digits10) << result << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}