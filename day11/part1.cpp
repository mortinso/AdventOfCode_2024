#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

long	count_digits( long n ) {
	if (n == 0)
		return	1;

	long	counter = 0;

	while (n != 0) {
		n /= 10;
		counter++;
	}

	return counter;
}

map<long, long>	blink( map<long, long> stones ) {
	map<long, long>	result;

	for (map<long, long>::iterator it = stones.begin(); it != stones.end(); it++) {
		if (it->first == 0)
			result[1] = (result[1] ? result[1] : 0) + it->second;

		else if (count_digits(it->first) % 2 == 0) {
			string	s;
			long	num1, num2;
			s = to_string(it->first);
			num1 = atol((s.substr(0, s.length() / 2)).c_str());
			num2 = atol((s.substr(s.length() / 2, s.length() / 2)).c_str());

			result[num1] = (result[num1] ? result[num1] : 0) + it->second;
			result[num2] = (result[num2] ? result[num2] : 0) + it->second;
		}

		else
			result[it->first * 2024] = (result[it->first * 2024] ? result[it->first * 2024] : 0) + it->second;
	}
	return result;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string			arg;
		map<long, long>	stones;
		while (getline(file, arg, ' '))
			stones[atol(arg.c_str())] = 1;

		cout << "Blinking..." << endl;

		for (size_t x = 0; x < 25; x++)
			stones = blink(stones);

		long	size = 0;
		for (map<long, long>::iterator it = stones.begin(); it != stones.end(); it++)
			size += it->second;

		cout << "Size: " << size << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}