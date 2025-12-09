#include "DataLoader.hpp"

DataLoader::DataLoader() : BitcoinExchange(), _db(NULL) {}

DataLoader::DataLoader(const DataLoader & copy) : BitcoinExchange(copy) { *this = copy;}

DataLoader::~DataLoader() {}

DataLoader & DataLoader::operator=(const DataLoader & copy)
{
	if (this != &copy)
		this->_db = copy._db;

	return *this;
}

DataLoader::DataLoader(Database *copy) : _db(copy) {}

bool DataLoader::loadFile(std::string filename)
{
	std::ifstream infile(filename.c_str());

	if (infile.is_open() == false)
	{
		std::cerr << RED << "DataLoader error 25: cannot open file: " << filename << NEUTRAL << '\n';
		return false;
	}

	std::string line;

	std::getline(infile, line);
    if (line != "date,exchange_rate")
    {
        std::cerr << RED << "Error: bad input => " << line << NEUTRAL << '\n';
        return false;  
    }

	while (std::getline(infile, line))
		if (processLine(line) == false)
		{
			std::cerr << "DataLoader error 34: processing line: " << line << NEUTRAL << '\n';
			return false;
		}

	return true;
}

bool DataLoader::processLine(const std::string & line)
{
	std::istringstream ss(line);
	std::string date;
	float value;

	if (line.empty() == true)
		return false ;

	if (line.find(',') == std::string::npos)
	{
		std::cerr << "DataLoader error 52: bad input => " << line << NEUTRAL << '\n';
		return false;
	}

	if (line == "date,exchange_rate") 
		return true;

	std::getline(ss, date, ',');

	if (date.empty() == true || date.size() != 10)
	{
		std::cerr << "DataLoader error 63: bad input => " << line << NEUTRAL << '\n';
		return false;
	}

	if (isValidDate(date) == false)
	{
		std::cerr << "DataLoader error 69: bad input => " << line << NEUTRAL << '\n';
		return false;
	}

	std::string token;

	if (!(ss >> token))
	{
		std::cerr << "DataLoader error 77: bad input => " << line << NEUTRAL << '\n';
		return false;
	}
	char *end;
	value = std::strtod(token.c_str(), &end);

	if (*end != '\0')
	{
		std::cerr << "DataLoader error 85: bad input => " << line << NEUTRAL << '\n';
		return false;
	}

	if (_db->setValue(date, value) == false)
	{
		std::cerr << "DataLoader error 91: already exist => " << line << NEUTRAL << '\n';
		return false;
	}
	
	return true;
}
