#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <iostream>
#include <sstream>

# define BLUE "\033[1;34m"
# define RED "\033[1;31m"
# define MARRON "\033[1;33m"
# define GREEN "\033[1;32m"
# define MAGENTA "\033[1;35m"
# define NEUTRAL "\033[0m" 

class RPN
{
	public:
		RPN();
		RPN(const RPN & copy);
		~RPN();
		RPN & operator=(const RPN & copy);

		float getResult() const;
		bool isOperator(const char op) const;
		float executeOperation(int left, int right, char op, bool & _errorOp);
		bool process(const std::string & entry);
		void printError() const;

	private:
		std::stack<float> _digits;
		std::string _error;
};

#endif
