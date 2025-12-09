#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN & copy) { *this = copy;}

RPN::~RPN() {}

RPN & RPN::operator=(const RPN & copy)
{
	if (this != &copy)
		*this = copy;

	return *this;
}

float RPN::getResult() const { return _digits.top();}

bool RPN::isOperator(const char op) const
{
	return (op == '+' || op == '-' || op == '*' || op == '/');
}


float RPN::executeOperation(int left, int right, char op, bool & isError)
{
	float result = 0.0;
	switch (op)
	{
		case '+':
			result = left + right;
			break;
		case '-':
			result = left - right;
			break;
		case '*':
			result = left * right;
			break;
		case '/':
			if (right != 0)
				result = left / right;
			else
			{
				isError = true;
				this->_error = "Error: Infinite result.";
				result = 1.0;
			}
			break ;
		default:
			isError = true;
			this->_error = "Error: operation not allowed.";
			break ;
	}

	return result;
}

bool RPN::process(const std::string & entry)
{
	std::istringstream iss(entry);
	std::string token;
	bool isError = false;

	if (entry.empty())
	{
		this->_error = "Error: invalid token. Empty.";
		return false;
	}

	while (iss >> token)
	{
		if (token.size() == 1 && std::isdigit(token[0])) 
			_digits.push(token[0] - '0');
		else if (token.size() == 1 && isOperator(token[0]) == true)
		{
			if (_digits.size() < 2)
			{
				this->_error = "Error: too few arguments";
				isError = true;
				return false;
			}
			char op = token[0];
			
			int right = _digits.top();
			_digits.pop();

			int left = _digits.top();
			_digits.pop();
			
			float result = executeOperation(left, right, op, isError);

			if (isError)
				return false;

			_digits.push(result);
		}
		else
		{
			this->_error = "Error: Bad syntax";
			return false;
		}
	}
	
	if (_digits.size() != 1)
	{
		this->_error = "Error: invalid token. Bad syntax.";
		return false;
	}
	return true;
}

void RPN::printError() const
{
	std::cerr << RED << this->_error << NEUTRAL << '\n';
}



































