#include "Database.hpp"

Database::Database() {}

Database::Database(const Database & copy) { *this = copy;}

Database::~Database() {}

Database & Database::operator=(const Database & copy)
{
	if (this != &copy)
		this->_db = copy._db;

    return *this;
}

bool Database::setValue(const std::string & date, float value)
{

    std::pair<std::map<std::string, float>::iterator, bool> res;
	res = this->_db.insert(std::make_pair(date, value));

	if (res.second == false)
	{
		std::cerr << "Dababase error 25: Cannot set: " << date << "|" << value << NEUTRAL <<'\n';
		return false;
	}

	return true;	

}

bool Database::getValue(const std::string & date, float & value)
{
    if (this->_db.empty())
    {
        return false;
    }

    std::map<std::string, float>::const_iterator it = this->_db.lower_bound(date);

    if (it != this->_db.end() && it->first == date)
    {
        value = it->second;
        return true;
    }

    if (it == this->_db.begin())
    {
        return false;
    }

    --it;
    value = it->second;

    return true;
}

