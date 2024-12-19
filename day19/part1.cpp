#include <iostream>
#include <fstream>
#include <deque>
#include <sstream>

using namespace std;

static deque<string>	patterns, designs;
static int				possible = 0;

bool	is_possible( string design ) {
	if (design.empty())
		return true;
	for (size_t i = 0; i < patterns.size(); i++) {
		if (patterns[i].length() <= design.length() && patterns[i] == design.substr(0, patterns[i].length())) {
			if (is_possible(design.substr(patterns[i].length())))
				return true;
		}
		// cout << i << endl;
	}
	// cout << "b" << endl;
	return false;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string	line;
		getline(file, line);

		istringstream	iss(line);
		while (getline(iss, line, ',')) {
			patterns.push_back(line);
			getline(iss, line, ' ');
		}

		getline(file, line);
		while (getline(file, line)) {
			// possible += is_possible(line);
			designs.push_back(line);
			// cout << designs[i] << " " << (is_possible(designs[i]) ? "YESSIR" : "NOSSIR") << endl;
			// cout << line << endl;
		}

		cout << designs[6] << " " << (is_possible(designs[6]) ? "YESSIR" : "NOSSIR") << endl;
		// for (size_t i = 0; i < designs.size(); i++) {
		// 	possible += is_possible(designs[i]);
		// 	cout << i << endl;
		// }
		cout << "Possible designs: " << possible << endl;

	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}