#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Returns 1 if safe, 0 if not
int	is_safe( vector<double> vec , int bad, int bad_pos ) {
	vector<double>	nvec(vec); // copy of vec
	bool			increasing = true;
	int				bad_counter = bad;

	// If second recursion, erase the member at bad_pos
	if (bad == 1)
		nvec.erase(nvec.begin() + bad_pos);

	if (nvec[0] > nvec[1])
		increasing = false;

	for (size_t i = 0; i < nvec.size() - 1; i++) {
		// If not decreasing nor increasing
		// If decreasing when it should be increasing and vice versa
		if (nvec[i] == nvec[i + 1] || (increasing && nvec[i] > nvec[i + 1]) || (!increasing && nvec[i] < nvec[i + 1]))
			bad_counter += 1;
	
		// If dif is wrong while increasing
		else if (increasing && nvec[i + 1] - nvec[i] > 3)
			bad_counter += 1;

		// If dif is wrong while decreasing
		else if (!increasing && nvec[i] - nvec[i + 1] > 3 )
			bad_counter += 1;
	
		// If bad_counter == 1 and we're not in the first recursion
		//		* Try again without one of the conflicting members
		//		* Try without the first member (to possibly change from decreasing to increasing and vice versa)
		if (bad_counter != bad && bad_counter == 1)
			return (is_safe(nvec, bad_counter, i) || is_safe(nvec, bad_counter, i + 1) || is_safe(nvec, bad_counter, 0));

		if (bad_counter > 1)
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

			count += is_safe(vec, 0, 0);
			vec.clear();
		}
		cout << "Safe reports: " << count << endl;
	}
	catch (const exception &e) { cerr << "Error " << e.what() << endl; }
}