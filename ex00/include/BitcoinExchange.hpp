#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cctype>

# define BLUE "\033[1;34m"
# define RED "\033[1;31m"
# define MARRON "\033[1;33m"
# define GREEN "\033[1;32m"
# define MAGENTA "\033[1;35m"
# define NEUTRAL "\033[0m"

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange & copy);
		virtual ~BitcoinExchange();
		BitcoinExchange & operator=(const BitcoinExchange & copy);

		virtual bool loadFile(const std::string & filename) = 0;
		virtual bool processLine(const std::string & line) = 0;
		bool isValidDate(const std::string & date);
};

#endif
