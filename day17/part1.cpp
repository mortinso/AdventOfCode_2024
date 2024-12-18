#include <iostream>
#include <fstream>
#include <deque>
#include <cmath>

using namespace std;

static int	A = 0;
static int	B = 0;
static int	C = 0;
static int	index = 0;

static deque<int>	program;
static string		output = "";

typedef void (*Instruction) (int op);

int	get_literal( int combo ) {
	if (combo >= 0 && combo <= 3)
		return combo;

	if (combo == 4)
		return A;
	if (combo == 5)
		return B;
	if (combo == 6)
		return C;
	else
		throw(runtime_error("Invalid combo operator"));
}

void	adv( int op ) { // opcode 0
	A /= pow(2, get_literal(op));
	index += 2;
}

void	bxl( int op ) { // opcode 1
	B = op ^ B;
	index += 2;
}

void	bst( int op ) { // opcode 2
	B = get_literal(op) % 8;
	index += 2;
}

void	jnz( int op ) { // opcode 3
	if (A == 0)
		index += 2;
	else
		index = op;
}

void	bxc( int op ) { // opcode 4
	B = (B ^ C);
	index += 2;
}

void	out( int op ) { // opcode 5
	output += to_string(get_literal(op) % 8) + ",";
	index += 2;
}

void	bdv( int op ) { // opcode 6
	B = (A / pow(2, get_literal(op)));
	index += 2;
}

void	cdv( int op ) { // opcode 7
	C = (A / pow(2, get_literal(op)));
	index += 2;
}

void	run_program( void ) {
	Instruction functions[8] = { &adv, &bxl, &bst, &jnz, &bxc, &out, &bdv, &cdv };

	while (index < program.size())
		functions[program[index]](program[index + 1]);

	output.erase(output.length() - 1); // remove trailing ','
	cout << output << endl;
}

int	main( void ) {
	try {
		ifstream	file("input");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string	line;
		getline(file, line, ':');
		getline(file, line);
		A = atoi(line.c_str());
		getline(file, line, ':');
		getline(file, line);
		B = atoi(line.c_str());
		getline(file, line, ':');
		getline(file, line);
		C = atoi(line.c_str());
		getline(file, line);
		getline(file, line, ':');

		while (getline(file, line, ','))
			program.push_back(atoi(line.c_str()));

		run_program();
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}