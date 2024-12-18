#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct block {
	long	id;
	long	size;
};

vector<struct block>	get_blocks( string input ) {
	size_t	id = 0;
	vector<struct block>	disk;

	for (size_t i = 0; i < input.length(); i++) {
		struct block	node;
		if (i % 2 == 0)
			node.id = id++;
		else
			node.id = -1;

		node.size = input[i] - '0';
		disk.push_back(node);
	}
	return disk;
}

long	fragmenter( string input ) {
	vector<struct block>	disk = get_blocks(input);
	vector<long>			fragments;
	long					checksum = 0;

	for (size_t i = 0; i < disk.size(); i++) {
		if (disk[i].id != -1) {
			while (disk[i].size-- > 0)
				fragments.push_back(disk[i].id);
		}
		else {
			for (size_t x = disk.size() - 1; disk[i].size > 0 && x > i; x--) {
				if (disk[i].size == 0 || disk[x].id == -1 || disk[i].size < disk[x].size)
					continue;

				for (size_t y = 0; y < disk[x].size; y++, disk[i].size--)
					fragments.push_back(disk[x].id);

				disk[x].id = -1;
			}

			while (disk[i].size-- > 0)
				fragments.push_back(0);
		}
	}
	for (size_t i = 0; i < fragments.size(); i++)
		checksum += (fragments[i] * i);
	return checksum;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string	line;
		getline(file, line);

		cout << "Checksum: " << fragmenter(line) << endl;
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}