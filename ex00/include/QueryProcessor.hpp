#ifndef QUERYPROCESSOR_HPP 
#define QUERYPROCESSOR_HPP 

#include "BitcoinExchange.hpp"
#include "Database.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>

class QueryProcessor : public BitcoinExchange
{
	public:
		QueryProcessor();
		QueryProcessor(const QueryProcessor & copy);
		~QueryProcessor();
		QueryProcessor &operator=(const QueryProcessor & copy);

		QueryProcessor(Database *copy);

		virtual bool loadFile(std::string filename);
		virtual bool processLine(const std::string & line);

	private:
		Database *_db;
};

#endif
