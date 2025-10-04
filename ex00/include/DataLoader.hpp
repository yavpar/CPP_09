#ifndef DATALOADER_HPP
#define DATALOADER_HPP

#include "BitcoinExchange.hpp"
#include "Database.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <map>

class DataLoader : public BitcoinExchange
{
	public:
		DataLoader();
		DataLoader(const DataLoader & copy);
		~DataLoader();
		DataLoader &operator=(const DataLoader & copy);

		DataLoader(Database *copy);

		virtual bool loadFile(const std::string & filename);
		virtual bool processLine(const std::string & line);

	private:
		Database *_db;
};

#endif
