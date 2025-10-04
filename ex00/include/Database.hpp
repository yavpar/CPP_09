#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

# define BLUE "\033[1;34m"
# define RED "\033[1;31m"
# define MARRON "\033[1;33m"
# define GREEN "\033[1;32m"
# define MAGENTA "\033[1;35m"
# define NEUTRAL "\033[0m"

class Database
{
	public:
		Database();
		Database(const Database & copy);
		~Database();
		Database &operator=(const Database & copy);

		bool setValue(const std::string & date, float value);
		bool getValue(const std::string & date, float & value);

	private:
		std::map<std::string, float> _db;
};

#endif
