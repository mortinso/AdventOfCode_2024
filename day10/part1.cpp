#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

// Checks if pos is already in coords
bool	find_coords( vector<pair<int, int> > &coords, pair<int, int> pos ) {
	for (size_t i = 0; i < coords.size(); i++) {
		if (coords[i].first == pos.first && coords[i].second == pos.second)
			return true;
	}
	return false;
}

// Recursive fucntion that returns the total_score of the trail by only adding to the score when a new '9' is found
long long	trail_score( vector<string> &topo, int x, int y, vector<pair<int, int> > &coords ) {
	long long	score = 0;

	if (y < topo.size() - 1 && topo[y + 1][x] == topo[y][x] + 1)
		score += trail_score(topo, x, y + 1, coords);
	if (y > 0 && topo[y - 1][x] == topo[y][x] + 1)
		score += trail_score(topo, x, y - 1, coords);
	if (x < topo[y].length() && topo[y][x + 1] == topo[y][x] + 1)
		score += trail_score(topo, x + 1, y, coords);
	if (x > 0 && topo[y][x - 1] == topo[y][x] + 1)
		score += trail_score(topo, x - 1, y, coords);

	pair<int, int>	pos(x, y);
	if (topo[y][x] == '9' && !find_coords(coords, pos)) {
		coords.push_back(pos);
		return score + 1;
	}

	return score;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string					line;
		vector<string>			topo;

		while (getline(file, line))
			topo.push_back(line);

		long long	total_score = 0;
		for (size_t y = 0; y < topo.size(); y++) {
			for (size_t x = 0; x < topo[y].length(); x++) {
				if (topo[y][x] == '0') {
					vector<pair<int, int> >	coords;
					total_score += trail_score(topo, x, y, coords);
				}
			}
		}

		cout << "Total Score: " << total_score << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}