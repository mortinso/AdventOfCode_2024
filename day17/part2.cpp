#include <iostream>
#include <fstream>
#include <deque>
#include <cmath>

using namespace std;

static long long unsigned	A, B, C, index, cached_A;
static deque<int>	program, output;

typedef void (*Instruction) (int op);

long long unsigned	get_literal( int combo ) {
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
	if (get_literal(op) < 0)
		cout << "yep " << op << endl;
	output.push_back(get_literal(op) % 8);
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

void	adjust( void ) {
	if (output.size() < program.size()) {
		// found lowest possible A for output to be the same size of program
		cached_A += pow(8, output.size() - 1);
		return;
	}
	if (output.size() > program.size())
		throw(runtime_error("Output size larger than program"));
	for (size_t i = program.size() - 1; i >= 0; i--) {
		if (output[i] != program[i]) {
			cached_A += pow(8, i); // Increase number on output at index by 1
			break;
		}
	}
}

void	run_program( void ) {
	Instruction functions[8] = { &adv, &bxl, &bst, &jnz, &bxc, &out, &bdv, &cdv };

	cached_A = 0;
	long	iterations = 0;
	while (true) {
		A = cached_A;
		B = 0;
		C = 0;
		index = 0;
		output.clear();
		while (index < program.size())
			functions[program[index]](program[index + 1]);
		if (output == program)
			break;
		iterations++;
		adjust();
	}
	cout << "Value of A for the program to output a copy of itself: " << cached_A << endl;
	cout << "Found after: " << iterations << " tries" << endl;
}

int	main( void ) {
	try {
		ifstream	file("example");
		if (!file.is_open())
			throw(runtime_error("Failed to open input file"));

		string	line;
		getline(file, line, ':');
		getline(file, line, ':');
		getline(file, line, ':');
		getline(file, line, ':');

		while (getline(file, line, ','))
			program.push_back(atoi(line.c_str()));

		run_program();
	}
	catch (exception &e) { cout << "Error: " << e.what() << endl; }
}