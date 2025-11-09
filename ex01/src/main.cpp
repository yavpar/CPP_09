#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: Usage: ./RPN \"operation in Reverse Polish Notation\"\nExample: ./RPN \"1 2 + 3 -\"" << NEUTRAL << '\n';
		return 1;
	}

	RPN calc;

	if (calc.process(av[1]))
		std::cout << GREEN << calc.getResult() << NEUTRAL << '\n';
	else
		calc.printError();

	return 0;
}
