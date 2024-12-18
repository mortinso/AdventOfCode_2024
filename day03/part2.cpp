#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>


using namespace std;

// Checks that mul is formated correctly, if so returns the result
double	get_result( string line ) {
	istringstream	istring(line);
	string			arg;
	double			num;
	
	getline(istring, arg, ',');
	if (arg.size() > 3 || arg.size() < 1)
		return 0;
	num = atof(arg.c_str());

	getline(istring, arg, ')');
	if (arg.size() > 3 || arg.size() < 1)
		return 0;
	num *= atof(arg.c_str());

	return num;
}

// Calls 
double	calc_snippet( string input, size_t pos, size_t limit ) {
	double	result = 0;

	while (pos < input.size() && pos < limit) {
		pos = input.find("mul(", pos) + 4;
		if (pos == string::npos || pos > limit)
			break;
		result += get_result(input.c_str() + pos);
	}
	return result;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open file"));

		string	input;
		size_t	pos = 0;
		double	result = 0;

		// put everything into 1 string
		getline(file, input, '\0');

		while (pos < input.size()) {
			// if we're closer to a "dont()" then a "do()", skip to the next "do()", except if we're at the start of input
			if (pos != 0 && input.find("don't()", pos) < input.find("do()", pos)) {
				// if there are no more "do()"s, stop the loop
				if (input.find("do()",pos) == string::npos)
					break;
				pos = input.find("do()", pos);
			}
			result += calc_snippet(input, pos, input.find("don't()", pos));
			pos = input.find("don't()",pos);
		}

		cout << "Result: " << setprecision(numeric_limits<double>::max_digits10) << result << endl;
	}
	catch (const exception &e) { cerr << "Error " << e.what() << endl; }
}