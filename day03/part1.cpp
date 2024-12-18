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

int	main( void ) {
	try {
		ifstream	file("input");

		if (!file.is_open())
			throw(runtime_error("Failed to open file"));

		string	input;
		size_t	pos = 0;
		double	result = 0;


		getline(file, input, '\0');

		while (pos < input.size()) {
			if (input.find("mul(", pos) == string::npos)
				break;
			pos = input.find("mul(", pos) + 4;
			result += get_result(input.c_str() + pos);
		}
		cout << "Result: " << setprecision(numeric_limits<double>::max_digits10) << result << endl;
	}
	catch (const exception &e) { cerr << "Error " << e.what() << endl; }
}