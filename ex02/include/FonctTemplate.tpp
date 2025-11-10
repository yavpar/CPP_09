#ifndef FONCTTEMPLATE_TPP
#define FONCTTEMPLATE_TPP

//	Insert value in the container by ascendant order
template <typename A>
void PmergeMe::insertSorted(A & container, int value)
{
	if (container.empty())
	{
		container.push_back(value);
		return;
	}

	typename A::iterator it = container.begin();

	for (; it != container.end(); ++it)
	{
		if (value < *it)
		{
			container.insert(it, value);
			return ;
		}
	}

	container.push_back(value);
}

// Find the max value in a container and return its position
template <typename C>
int PmergeMe::min_value_idx(C & container)
{
	int idx = -1;	
	int _max = INT_MAX;//MIN;

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

	return (idx);
}

// -	sorts pairs (i, ++i)
// -	add [min  max] to its container [mins  maxs] 	
template <typename T>
void PmergeMe::separateMinMax(T & container, T & mins, T & maxs)
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
			return ;
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

// creates a container with values from CLI
template <typename T>
bool PmergeMe::createStack(const std::string & s, T & container)
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

// prints a container 
template <typename T>
void PmergeMe::printStack(T & container) const
{
	if (container.empty())
	{
		std::cerr << RED << "Container is empty.\n" << NEUTRAL;
		return ;
	}

	std::cout << GREEN << "[ ";
	for (std::size_t i = 0; i < container.size(); i++)
		std::cout << container[i] << " ";
	std::cout << "]\n" << NEUTRAL;
}

template <typename C>
void PmergeMe::insert_sorted_desc_iter(C & container, int value)
{
    typename C::iterator it = container.begin();

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

// generates JACOBSTHAL sequence [0][1][1]...
// next = J(n) = J(n-1)+2*J(n-2)
// total = Diferencial = J(n) - J(n-1)
template <typename A, typename B>
void PmergeMe::generate_jacobsthal_sequence(const A & mins, B & jacob)
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

// creates a container with the size of groups to creates 
// in order to sort.
// if there is 10 number it will be [2][2][6]
template <typename C, typename D>
void PmergeMe::generate_jacobsthal_groups(const C & jacob, D & groups, std::size_t total_mins)
{
    groups.clear();

    if (jacob.size() < 3)
        return;

    std::size_t used = 0; // cuántos mins ya cubrimos

    for (std::size_t i = 3; i < jacob.size() && used < total_mins; ++i)
    {
        int diff = jacob[i] - jacob[i - 1];
        if (diff <= 0)
            continue;

        if (used + static_cast<std::size_t>(diff) > total_mins)
            diff = static_cast<int>(total_mins - used); // ajusta el último grupo

        groups.push_back(diff);
        used += static_cast<std::size_t>(diff);
    }

	if (_DEBUG)
	{
		std::cout << MARRON << "Group:\t" << NEUTRAL;
		printStack(groups);
	}
}


// 1) inicializa el contenedor de posiciones con 0..n-1
template <typename Cont>
void PmergeMe::init_positions(const Cont & sorted, Cont & pos)
{
    pos.resize(sorted.size());
    for (std::size_t i = 0; i < sorted.size(); ++i)
        pos[i] = static_cast<int>(i);
}

// 2) inserta UN mínimo dentro del prefijo que llega hasta su max
template <typename Cont>
std::size_t PmergeMe::insert_one_min(Cont &sorted,
                                     int value_to_insert,
                                     std::size_t max_pos_index)
{
    typename Cont::iterator begin_it  = sorted.begin();
    typename Cont::iterator range_end = begin_it + max_pos_index + 1;

    typename Cont::iterator ins_it =
        std::lower_bound(begin_it,
                         range_end,
                         value_to_insert,
                         PmergeMe::mayorThan);

    std::size_t ins_index = static_cast<std::size_t>(ins_it - begin_it);
    sorted.insert(ins_it, value_to_insert);
    return ins_index;
}

// 3) después de insertar, desplaza las posiciones de los max
template <typename Cont>
void PmergeMe::bump_positions(Cont &pos, std::size_t ins_index)
{
    for (std::size_t j = 0; j < pos.size(); ++j)
    {
        std::size_t cur = static_cast<std::size_t>(pos[j]);
        if (cur >= ins_index)
            pos[j] = static_cast<int>(cur + 1);
    }
}

// 4) función principal
template <typename Cont>
void PmergeMe::push_min(Cont &sorted, const Cont &pending, const Cont &grJacobsthal)
{
	Cont max_orig = sorted;

    Cont pos;
    init_positions(sorted, pos);

    typename Cont::const_iterator g_it  = grJacobsthal.begin();
    typename Cont::const_iterator g_end = grJacobsthal.end();

    std::size_t offset = 0;

    while (g_it != g_end && offset < pending.size())
    {
        std::size_t group_size = adjust_group_size(static_cast<std::size_t>(*g_it),\
													offset,\
													pending.size());

		if (_DEBUG)
			std::cout << MARRON << "Groups created: " << GREEN << "[" ;
        for (std::size_t k = 0; k < group_size; ++k)
        {
            std::size_t idx_in_pending = offset + (group_size - 1 - k);
			
            int value_to_insert = pending[idx_in_pending];
			if (_DEBUG)
				std::cout << value_to_insert << " ";
            std::size_t max_pos_index = static_cast<std::size_t>(pos[idx_in_pending]);

            std::size_t ins_index = insert_one_min(sorted, value_to_insert, max_pos_index);

            bump_positions(pos, ins_index);
        }
		if (_DEBUG)
			std::cout << "]\n" << NEUTRAL;
        offset += group_size;
        ++g_it;
    }

}

#endif
