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
int PmergeMe::max_value_idx(C & container)
{
	int idx = -1;	
	int _max = INT_MIN;

	if (container.empty())
		return idx;

	//for (std::size_t i = 1; i + 1 < container.size(); i += 2)
	for (std::size_t i = 1; i < container.size(); i += 2)
	{
		if (container[i] >= _max)
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
	std::cout << "SWAP:\n";
	printStack(container);
	std::cout << '\n';
    while (!container.empty())
    {
        int idx = max_value_idx(container);
		if (idx == -1)
			return ;
        int maxVal = container[idx];
        int minVal = container[idx - 1];
		container.erase(container.begin() + idx - 1, container.begin() + idx + 1);

        maxs.push_back(maxVal);
        mins.push_back(minVal);
    }

	if (impair)
		maxs.push_back(leftover);
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
		std::cerr << "Container is empty.\n";
		return ;
	}

	for (std::size_t i = 0; i < container.size(); i++)
		std::cout << "container[" << i << "] = " << container[i] << "\n";
}

template <typename C>
void PmergeMe::insert_sorted_desc_iter(C & container, int value)
{
    // Definimos el iterador explícitamente para C++98
    typename C::iterator it = container.begin();

    for (; it != container.end(); ++it)
    {
        // Como el contenedor está ordenado de MAYOR a MENOR:
        // insertamos cuando encontramos un elemento menor que el valor a insertar
        if (value > *it)
        {
            container.insert(it, value);
            return;
        }
    }

    // Si no se insertó en medio, lo insertamos al final
    container.push_back(value);
}

// generates JACOBSTHAL sequence [0][1][1]...
// next = J(n) = J(n-1)+2*J(n-2)
// totoal = Diferencial = J(n) - J(n-1)
template <typename A, typename B>
void PmergeMe::generate_jacobsthal_sequence(const A & mins, B & jacob)
{
    jacob.clear();

    // Si no hay elementos mínimos, no hay nada que generar
    if (mins.empty())
        return;

    // Inicializar con los 3 primeros términos
    jacob.push_back(0); // J(0)
    jacob.push_back(1); // J(1)
    jacob.push_back(1); // J(2)

    // Contadores para generar la secuencia
    std::size_t j_idx = 2;   // último índice generado (J(2))
    std::size_t total = 0;   // suma acumulada de los diferenciales

    // Mientras no superemos el número de elementos en mins
    while (total < mins.size())
    {
        int next = jacob[j_idx] + 2 * jacob[j_idx - 1];
		jacob.push_back(next);

        int diff = next - jacob[j_idx]; 
        total += diff;

        ++j_idx;
    }
}

// creates a container with the size of groups to creates 
// in order to sort.
// if there is 10 number it will be [2][2][6]
template <typename C, typename D>
void PmergeMe::generate_jacobsthal_groups(const C & jacob, D & groups)
{
    groups.clear();

    if (jacob.size() < 3)
        return; // No hay suficientes números para formar grupos

    // Recorremos desde J(3) en adelante
    for (std::size_t i = 3; i < jacob.size(); ++i)
    {
        int diff = jacob[i] - jacob[i - 1];
        if (diff > 0)
            groups.push_back(diff);
    }
}

template <typename Cont>
void PmergeMe::push_min(Cont &sorted, const Cont &pending, const Cont &grJacobsthal)
{
    // iteramos sobre los tamaños de grupo
    typename Cont::const_iterator g_it  = grJacobsthal.begin();
    typename Cont::const_iterator g_end = grJacobsthal.end();

    std::size_t offset = 0; // desde dónde tomar en 'pending'

    while (g_it != g_end || offset < pending.size())
    {
        std::size_t group_size = static_cast<std::size_t>(*g_it);

		std::size_t remaining = pending.size() - offset;
		if (group_size > remaining)
			group_size = remaining;

        // calculamos el rango [first, last) de este grupo dentro de 'pending'
        typename Cont::const_iterator first = pending.begin() + offset;
        typename Cont::const_iterator last  = first + group_size;

        // construimos un contenedor temporal con ese grupo
        Cont group(first, last);

        // vamos a insertar los elementos del grupo en orden inverso
        typename Cont::const_reverse_iterator rit     = group.rbegin();
        typename Cont::const_reverse_iterator rit_end = group.rend();

        while (rit != rit_end)
        {
            // buscamos dónde va este elemento dentro de 'sorted'
            typename Cont::iterator pos =
                std::lower_bound(sorted.begin(),
                                 sorted.end(),
                                 *rit,
                                 PmergeMe::mayorThan); // usa orden descendente

            sorted.insert(pos, *rit);
            ++rit;
        }

        // avanzamos al siguiente grupo
        offset += group_size;
        ++g_it;
    }
}

#endif
