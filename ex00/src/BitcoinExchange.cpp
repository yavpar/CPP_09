#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{ 
	//std::cout << MARRON << "Default constructor: BitcoinExchange\n" << NEUTRAL;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange & copy)
{
	//std::cout << MARRON << "Copy operator: BitcoinExchange\n" << NEUTRAL;
	(void)copy;
}

BitcoinExchange::~BitcoinExchange() 
{
	//std::cout << MARRON << "~Destructor: BitcoinExchange\n" << NEUTRAL;
}

BitcoinExchange & BitcoinExchange::operator=(const BitcoinExchange & copy)
{
	//std::cout << MARRON << "Assigment operator: BitcoinExchange\n" << NEUTRAL;
	(void)copy;

	return *this;
}

bool isLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

std::string trim(const std::string &s)
{
	std::string::size_type start = 0;
	std::string::size_type end = s.length();

	while (start < end && std::isspace(static_cast<unsigned char>(s[start])))
		++start;

	while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
		--end;

	return s.substr(start, end - start);
}

bool isValidDateFormat(const std::string& date)
{
	std::string s = trim(date);
    if (s.size() != 10)
	{
       // std::cerr << RED << "Error: data.size() != 10 : " << date << "." << NEUTRAL << '\n';
        return false;
	}

    for (int i = 0; i < 10; ++i)
	{
		if (i == 4 || i == 7)
		{
			if (s[i] != '-')
			{
				//std::cerr << RED << "Error: != [-]" << NEUTRAL << '\n';
				return false;
			}
		}
		else
		{
			if (!isdigit(s[i]))
			{
				//std::cerr << RED << "Error: not a digit" << NEUTRAL << '\n';
				return false;
			}
		}
	}

	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date)
{
    if (!isValidDateFormat(date))
	{
        //std::cerr << RED << "Error: IsValidFormat" << NEUTRAL << '\n';
        return false;
	}
    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if (year < 1 || month < 1 || month > 12 || day < 1)
	{
        return false;
	}

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year))
        daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1])
	{
        //std::cerr << RED << "Error: day > [month - 1]" << NEUTRAL << '\n';
        return false;
	}

    return true;
}

