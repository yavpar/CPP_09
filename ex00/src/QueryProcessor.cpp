#include "QueryProcessor.hpp"

QueryProcessor::QueryProcessor() : BitcoinExchange(), _db(NULL) {}

QueryProcessor::QueryProcessor(const QueryProcessor & copy) { *this = copy;}

QueryProcessor::~QueryProcessor() {}

QueryProcessor & QueryProcessor::operator=(const QueryProcessor & copy)
{
	if (this != &copy)
		this->_db = copy._db;

	return *this;
}

QueryProcessor::QueryProcessor(Database *copy) : _db(copy) {}

bool QueryProcessor::loadFile(const std::string & filename)
{
	std::ifstream infile(filename);
	if (infile.is_open() == false)
	{
		std::cerr << "Error: cannot open file: " << RED << filename << NEUTRAL << '\n';
		return false;
	}

	std::string line;

    std::getline(infile, line);
    if (line.empty())
    {
        std::cerr << BLUE << "File is empty." << NEUTRAL << '\n';
        return true;
    }

    if (line != "date | value" )
    {
        std::cerr << RED << "Error 39: bad input => " << line << NEUTRAL << '\n';
        return false;  
    }

	while (std::getline(infile, line))
		processLine(line);

	return true;
}

bool QueryProcessor::processLine(const std::string & line)
{
    if (line.empty())
        return false;

    std::istringstream ss(line);
    std::string date;
    float ratio;

    if (line.find('|') == std::string::npos)
    {
        std::cerr << RED << "Error 60: bad input => " << line << NEUTRAL << '\n';
        return false;
    }

    std::getline(ss, date, '|');
    if (!isValidDate(date))
    {
        std::cerr << RED << "Error 67: bad input => " << line << NEUTRAL << '\n';
        return false;
    }

    std::string token;
    if (!(ss >> token))
    {
        std::cerr << RED << "Error 74: bad input => " << line << NEUTRAL << '\n';
        return false;
    }

    char *end;
    ratio = std::strtod(token.c_str(), &end);
    if (*end != '\0')
    {
        std::cerr << RED << "Error 82: bad input => " << line << NEUTRAL << '\n';
        return false;
    }

    if (ratio < 0)
    {
        std::cerr << RED << "Error: not a positive number." << NEUTRAL << '\n';
        return false;
    }

    if (ratio > 1000)
    {
        std::cerr << RED << "Error: too large a number." << NEUTRAL << '\n';
        return false;
    }

    float dbValue;
    if (_db->getValue(date, dbValue) == false)
    {
        std::cerr << RED << "Error 101: bad input => "<< line << NEUTRAL << '\n';
        return false;
    }

    std::cout << GREEN << date << " => " << ratio << " = " << (dbValue * ratio) << NEUTRAL << '\n';

    return true;
}
