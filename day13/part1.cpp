#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

size_t	calc_presses( pair<long, long> A, pair<long, long> B, pair<long, long> prize ) {
	size_t	A_presses, B_presses;

	A_presses = ((prize.first * B.second) - (prize.second * B.first)) / ((A.first * B.second) - (A.second * B.first));
	B_presses = ((A.first * prize.second) - (A.second * prize.first)) / ((A.first * B.second) - (A.second * B.first));

	if (((A_presses * A.first + B_presses * B.first) != prize.first) || (A_presses * A.second + B_presses * B.second) != prize.second)
		return 0;

	return (A_presses * 3) + B_presses;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string			line, arg;
		size_t 			cost = 0, i = 0;
		pair<long, long>	A, B, prize;

		while (getline(file, line)) {
			if (line.empty()) {
				i = 0;
				continue;
			}
			istringstream	iss(line);
			if (i == 0) {
				getline(iss, arg, 'X');
				getline(iss, arg, ',');
				A.first = atoi(arg.c_str());
				getline(iss, arg, 'Y');
				getline(iss, arg);
				A.second = atoi(arg.c_str());
			}
			if (i == 1) {
				getline(iss, arg, 'X');
				getline(iss, arg, ',');
				B.first = atoi(arg.c_str());
				getline(iss, arg, 'Y');
				getline(iss, arg);
				B.second = atoi(arg.c_str());
			}
			if (i == 2) {
				getline(iss, arg, '=');
				getline(iss, arg, ',');
				prize.first = atoi(arg.c_str());
				getline(iss, arg, '=');
				getline(iss, arg);
				prize.second = atoi(arg.c_str());
				cost += calc_presses(A, B, prize);
			}
			i++;
		}
		cout << "Total cost: " << cost << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what()<< endl; }
}