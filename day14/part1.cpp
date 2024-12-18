#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>

#define TIME 100
#define WIDE 101
#define TALL 103

using namespace std;

struct	robot {
	pair<int, int>	pos;
	pair<int, int>	vel;
};

long	calc_factor( deque<robot> &troop ) {
	long	q1 = 0, q2 = 0, q3 = 0, q4 = 0;

	for (size_t i = 0; i < troop.size(); i++) {
		if (troop[i].pos.first < (WIDE / 2) && troop[i].pos.second < (TALL / 2))
			q1++;
		else if (troop[i].pos.first > (WIDE / 2) && troop[i].pos.second < (TALL / 2))
			q2++;
		else if (troop[i].pos.first < (WIDE / 2) && troop[i].pos.second > (TALL / 2))
			q3++;
		else if (troop[i].pos.first > (WIDE / 2) && troop[i].pos.second > (TALL / 2))
			q4++;
	}

	return q1 * q2 * q3 * q4;
}

void	move_around( deque<robot> &troop ) {
	for (size_t i = 0; i < troop.size(); i++) {
		troop[i].pos.first = (troop[i].pos.first + (troop[i].vel.first * TIME) % WIDE);
		troop[i].pos.second = (troop[i].pos.second + (troop[i].vel.second * TIME) % TALL);
		if (troop[i].pos.first < 0)
			troop[i].pos.first += WIDE;
		else if (troop[i].pos.first >= WIDE)
			troop[i].pos.first -= WIDE;
		if (troop[i].pos.second < 0)
			troop[i].pos.second += TALL;
		if (troop[i].pos.second >= TALL)
			troop[i].pos.second -= TALL;
	}
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string			line, arg;
		deque<robot>	troop;
		while (getline(file, line)) {
			istringstream	iss(line);
			robot			guard;

			getline(iss, arg, '=');
			getline(iss, arg, ',');
			guard.pos.first = atoi(arg.c_str());
			getline(iss, arg, ' ');
			guard.pos.second = atoi(arg.c_str());
			getline(iss, arg, '=');
			getline(iss, arg, ',');
			guard.vel.first = atoi(arg.c_str());
			getline(iss, arg);
			guard.vel.second = atoi(arg.c_str());
			troop.push_back(guard);
		}

		move_around(troop);

		cout << "Factor: " << calc_factor(troop) << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}