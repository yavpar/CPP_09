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

bool isValidDateFormat(const std::string& date)
{
    if (date.size() != 10)
        return false;

    for (int i = 0; i < 10; ++i)
	{
        if (i == 4 || i == 7)
		{
            if (date[i] != '-')
                return false;
        }
		else
		{
            if (!isdigit(date[i]))
                return false;
        }
    }

    return true;
}

bool isValidDate(const std::string& date)
{
    if (!isValidDateFormat(date))
        return false;

    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    if (year < 1 || month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year))
        daysInMonth[1] = 29;

    if (day > daysInMonth[month - 1])
        return false;

    return true;
}

