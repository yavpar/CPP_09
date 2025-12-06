#include "PmergeMe.hpp"
#include <vector>
#include <algorithm>
#include <climits>
#include <sstream>
#include <iostream>

void PmergeMe::insertSorted(std::vector<int> & container, int value)
{
    if (container.empty())
    {
        container.push_back(value);
        return;
    }

    std::vector<int>::iterator it = container.begin();

    for (; it != container.end(); ++it)
    {
        if (value < *it)
        {
            container.insert(it, value);
            return;
        }
    }

    container.push_back(value);
}

int PmergeMe::min_value_idx(std::vector<int> & container)
{
    int idx = -1;
    int _max = INT_MAX;

    if (container.empty())
        return idx;

    for (std::size_t i = 1; i < container.size(); i += 2)
    {
        if (container[i] <= _max)
        {
            _max = container[i];
            idx = static_cast<int>(i);
        }
    }

    return idx;
}

void PmergeMe::separateMinMax(std::vector<int> & container,
                              std::vector<int> & mins,
                              std::vector<int> & maxs)
{
    mins.clear();
    maxs.clear();
    int leftover = 0;
    bool impair = false;

    if (container.size() % 2 != 0)
    {
        leftover = container.back();
        container.pop_back();
        impair = true;
    }

    for (std::size_t i = 0; i + 1 < container.size(); i += 2)
    {
        if (container[i] > container[i + 1])
            std::swap(container[i], container[i + 1]);
    }
    if (_DEBUG)
    {
        std::cout << MARRON << "Swap:\n" << GREEN;
        for (std::size_t i = 0; i < container.size(); ++i)
        {
            if (i % 2 == 0)
                std::cout << " [ ";
            std::cout << container[i] << " ";
            if (i % 2 != 0)
                std::cout << "] ";
        }
        std::cout << '\n' << NEUTRAL;
    }
    while (!container.empty())
    {
        int idx = min_value_idx(container);
        if (idx == -1)
            return;
        int maxVal = container[idx];
        int minVal = container[idx - 1];
        container.erase(container.begin() + idx - 1, container.begin() + idx + 1);

        maxs.push_back(maxVal);
        mins.push_back(minVal);
    }

    if (impair)
        insertSorted(maxs, leftover);

    if (_DEBUG)
    {
        std::cout << MARRON << "Min: ";
        printStack(mins);
        std::cout << MARRON << "Max: ";
        printStack(maxs);
        std::cout << NEUTRAL;
    }
}

bool PmergeMe::createStack(const std::string & s, std::vector<int> & container)
{
    std::istringstream ss(s);
    int value;
    bool inserted = false;

    while (ss >> value)
    {
        container.push_back(value);
        inserted = true;
    }
    return inserted;
}

void PmergeMe::printStack(std::vector<int> & container) const
{
    if (container.empty())
    {
        std::cerr << RED << "Container is empty.\n" << NEUTRAL;
        return;
    }

    std::cout << GREEN << "[ ";
    for (std::size_t i = 0; i < container.size(); i++)
        std::cout << container[i] << " ";
    std::cout << "]\n" << NEUTRAL;
}

void PmergeMe::insert_sorted_desc_iter(std::vector<int> & container, int value)
{
    std::vector<int>::iterator it = container.begin();

    for (; it != container.end(); ++it)
    {
        if (value < *it)
        {
            container.insert(it, value);
            return;
        }
    }

    container.push_back(value);
}

void PmergeMe::generate_jacobsthal_sequence(const std::vector<int> & mins,
                                            std::vector<int> & jacob)
{
    jacob.clear();

    if (mins.empty())
        return;

    jacob.push_back(0);
    jacob.push_back(1);
    jacob.push_back(1);

    std::size_t j_idx = 2;
    std::size_t total = 0;

    while (total < mins.size())
    {
        int next = jacob[j_idx] + 2 * jacob[j_idx - 1];
        jacob.push_back(next);

        int diff = next - jacob[j_idx];
        total += diff;

        ++j_idx;
    }
    if (_DEBUG)
    {
        std::cout << MARRON << "JACOBSTHAL Sequence:\t" << NEUTRAL;
        printStack(jacob);
    }
}

void PmergeMe::generate_jacobsthal_groups(const std::vector<int> & jacob,
                                          std::vector<int> & groups,
                                          std::size_t total_mins)
{
    groups.clear();

    if (jacob.size() < 3)
        return;

    std::size_t used = 0;

    for (std::size_t i = 3; i < jacob.size() && used < total_mins; ++i)
    {
        int diff = jacob[i] - jacob[i - 1];
        if (diff <= 0)
            continue;

        if (used + static_cast<std::size_t>(diff) > total_mins)
            diff = static_cast<int>(total_mins - used);

        groups.push_back(diff);
        used += static_cast<std::size_t>(diff);
    }

    if (_DEBUG)
    {
        std::cout << MARRON << "Group:\t" << NEUTRAL;
        printStack(groups);
    }
}

void PmergeMe::init_positions(std::vector<int> & sorted,
                              std::vector<int> & pos)
{
    pos.resize(sorted.size());
    for (std::size_t i = 0; i < sorted.size(); ++i)
        pos[i] = static_cast<int>(i);
}

std::size_t PmergeMe::insert_one_min(std::vector<int> & sorted,
                                     int value_to_insert,
                                     std::size_t max_pos_index)
{
    std::vector<int>::iterator begin_it  = sorted.begin();
    std::vector<int>::iterator range_end = begin_it + max_pos_index + 1;

    std::vector<int>::iterator ins_it =
        std::lower_bound(begin_it,
                         range_end,
                         value_to_insert,
                         PmergeMe::mayorThan);

    std::size_t ins_index = static_cast<std::size_t>(ins_it - begin_it);
    sorted.insert(ins_it, value_to_insert);
    return ins_index;
}

void PmergeMe::bump_positions(std::vector<int> & pos, std::size_t ins_index)
{
    for (std::size_t j = 0; j < pos.size(); ++j)
    {
        std::size_t cur = static_cast<std::size_t>(pos[j]);
        if (cur >= ins_index)
            pos[j] = static_cast<int>(cur + 1);
    }
}

void PmergeMe::push_min(std::vector<int> & sorted,
                        const std::vector<int> & pending,
                        const std::vector<int> & grJacobsthal)
{
    std::vector<int> max_orig = sorted;

    std::vector<int> pos;
    init_positions(sorted, pos);

    std::vector<int>::const_iterator g_it  = grJacobsthal.begin();
    std::vector<int>::const_iterator g_end = grJacobsthal.end();

    std::size_t offset = 0;

    while (g_it != g_end && offset < pending.size())
    {
        std::size_t group_size =
            adjust_group_size(static_cast<std::size_t>(*g_it),
                              offset,
                              pending.size());

        if (_DEBUG)
            std::cout << MARRON << "Groups created: " << GREEN << "[";
        for (std::size_t k = 0; k < group_size; ++k)
        {
            std::size_t idx_in_pending = offset + (group_size - 1 - k);

            int value_to_insert = pending[idx_in_pending];
            if (_DEBUG)
                std::cout << value_to_insert << " ";
            std::size_t max_pos_index =
                static_cast<std::size_t>(pos[idx_in_pending]);

            std::size_t ins_index =
                insert_one_min(sorted, value_to_insert, max_pos_index);

            bump_positions(pos, ins_index);
        }
        if (_DEBUG)
            std::cout << "]\n" << NEUTRAL;
        offset += group_size;
        ++g_it;
    }
}
