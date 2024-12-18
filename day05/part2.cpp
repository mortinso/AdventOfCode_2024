# include <iostream>
# include <fstream>
# include <vector>
# include <sstream>

using namespace std;

// Returns true if update is in accordance with the rules
bool	is_good( vector<int> update, vector<pair<int, int> > rules ) {
	for (size_t i = 0; i < update.size(); i++)
	{
		vector<int>	before;	// All numbers that need to be before update[i]

		for (size_t j = 0; j < rules.size(); j++) {
			if (rules[j].second == update[i])
				before.push_back(rules[j].first);
		}

		for (size_t j = i + 1; j < update.size(); j++) {
			for (size_t k = 0; k < before.size(); k++) {
				if (update[j] == before[k])
					return false;
			}
		}
	}
	return true;
}

// Reorganizes the update and then returns the middle page number
int	get_middle( vector<int> update, vector<pair<int, int> > rules ) {
	while (!is_good(update, rules)) {
		for (size_t i = 0; i < update.size(); i++) {
			vector<int>	before;			// All numbers that need to be before update[i]
			bool		moved = false;	// Becomes true if update[i] gets moved to the end of the vector

			for (size_t j = 0; j < rules.size(); j++) {
				if (rules[j].second == update[i])
					before.push_back(rules[j].first);
			}

			for (size_t j = i + 1; j < update.size(); j++) {
				// search the before members for update[j]
				for (size_t k = 0; k < before.size(); k++) {
					if (update[j] == before[k]){
						int	tmp = update[i];

						// remove update[i] and add it at the end of the vector
						update.erase(update.begin() + i);
						update.push_back(tmp);
						moved = true;
						break;
					}
				}
				if (moved)
					break;
			}
		}
	}
	return (update[(update.size() - 1) / 2]);
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		vector<pair<int, int> > rules;
		for (size_t i = 0; i < 1176; i++) {
			pair<int, int>	p;
			string			line;

			getline(file, line, '|');
			p.first = atoi(line.c_str());
			getline(file, line);
			p.second = atoi(line.c_str());
			rules.push_back(p);
		}

		string	line;
		double	middles = 0;
		while (getline(file, line)) {
			if (line.empty())
				continue;

			istringstream	istring(line);
			vector<int>		update;
			string			arg;

			while (getline(istring, arg, ','))
				update.push_back(atoi(arg.c_str()));

			if (!is_good(update, rules))
				middles += get_middle(update, rules);
		}
		cout << "Sum of middles: " << middles << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}