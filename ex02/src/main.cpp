#include "PmergeMe.hpp"
#include <ctime>


void testDeque(PmergeMe &p, const std::string &input)
{
    p._deque.clear();
    p._Dmin.clear();
    p._Dmax.clear();
    p._Djacobsthal.clear();
    p._Dgroups.clear();

    p.createStack(input, p._deque);
    p.separateMinMax(p._deque, p._Dmin, p._Dmax);
    p.generate_jacobsthal_sequence(p._Dmin, p._Djacobsthal);    
    p.generate_jacobsthal_groups(p._Djacobsthal, p._Dgroups, p._Dmin.size());
    p.push_min(p._Dmax, p._Dmin, p._Dgroups);

    if (_DEBUG)
    {
        std::cout << MARRON << "Deque sorted:\n";
        p.printStack(p._Dmax);
    }
}

void testVector(PmergeMe &p, const std::string &input)
{
    p._vect.clear();
    p._Vmin.clear();
    p._Vmax.clear();
    p._Vjacobsthal.clear();
    p._Vgroups.clear();

    p.createStack(input, p._vect);
    p.separateMinMax(p._vect, p._Vmin, p._Vmax);
    p.generate_jacobsthal_sequence(p._Vmin, p._Vjacobsthal);    
    p.generate_jacobsthal_groups(p._Vjacobsthal, p._Vgroups, p._Vmin.size());
    p.push_min(p._Vmax, p._Vmin, p._Vgroups);

    // Guardamos resultado final en p.after[]
    for (std::size_t i = 0; i < p._Vmax.size(); i++)
        p.after[i] = p._Vmax[i];

    if (_DEBUG)
    {
        std::cout << MARRON << "Vector sorted:\n";
        p.printStack(p._Vmax);
    }
}

int main(int ac, char **av)
{
    PmergeMe p;

    std::clock_t begin_parse = std::clock();
    if (p.parseNumbers(av, ac) == false)
        return 1;
    std::clock_t end_parse = std::clock();

    std::clock_t time_parse = static_cast<double>(end_parse - begin_parse) / CLOCKS_PER_SEC;


    std::string input = std::string(av[1]);

    std::clock_t dequeBegin = std::clock();
    testDeque(p, input);
    std::clock_t dequeEnd = std::clock();
    double elapsed = time_parse + static_cast<double>(dequeEnd - dequeBegin) / CLOCKS_PER_SEC;

    std::clock_t vectorBegin = std::clock();
    testVector(p, input);
    std::clock_t vectorEnd = std::clock();
    double V_elapsed = time_parse + static_cast<double>(vectorEnd - vectorBegin) / CLOCKS_PER_SEC;

    std::cout << BLUE << "Before:\n";
    for (int i = 0; i < p.nElem; i++)
        std::cout << p.before[i] << ' ';
    std::cout << '\n' << NEUTRAL;

    std::cout <<  GREEN << "After:\n";
    for (int i = 0; i < p.nElem; i++)
        std::cout << p.after[i] << ' ';
    std::cout << '\n' << NEUTRAL;

    std::cout << MAGENTA << "Time to process a range of " << p.nElem << " elements with std::deque<int>: " << elapsed << " seconds\n";

    std::cout << MARRON << "Time to process a range of " << p.nElem << " elements with std::vector<int>: " << V_elapsed << " seconds\n";

    return 0;
}
