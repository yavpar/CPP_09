#include "Database.hpp"
#include "DataLoader.hpp"
#include "QueryProcessor.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << RED << "Error: usage: ./btc filename" << NEUTRAL << '\n';
        return 1;
    }

    Database db;

    DataLoader loader(&db);
    if (loader.loadFile("./Database/data.csv") == false)
    {
        std::cerr << RED << "Error uploading database: data.csv" << NEUTRAL << '\n';
        return 1;
    }

    std::cout << MARRON << "Database loaded succesfuly" << NEUTRAL << '\n';

    QueryProcessor queries(&db);
    if (queries.loadFile(av[1]) == false)
        return 1;

    return 0;
}
