#include "PmergeMe.hpp"
#include <ctime>

void testDeque(std::string input)
{
	PmergeMe d;

	d.createStack(input, d._deque);
	d.separateMinMax(d._deque, d._Dmin, d._Dmax);
	d.generate_jacobsthal_sequence(d._Dmin, d._Djacobsthal);	
	d.generate_jacobsthal_groups(d._Djacobsthal, d._Dgroups, d._Dmin.size());
	d.push_min(d._Dmax, d._Dmin, d._Dgroups);
	if (_DEBUG)
	{
		std::cout << MARRON << "Deque sorted:\n";
		d.printStack(d._Dmax);
	}
}

void testVector(std::string input)
{
	PmergeMe v;

	v.createStack(input, v._vect);
	v.separateMinMax(v._vect, v._Vmin, v._Vmax);
	v.generate_jacobsthal_sequence(v._Vmin, v._Vjacobsthal);	
	v.generate_jacobsthal_groups(v._Vjacobsthal, v._Vgroups, v._Vmin.size());
	v.push_min(v._Vmax, v._Vmin, v._Vgroups);
	if (_DEBUG)
	{
		std::cout << MARRON << "Vector sorted:\n";
		v.printStack(v._Vmax);
	}
}


int main(int ac, char **av)
{
	PmergeMe p;
	if (ac != 2 || p.parseNumbers(av, ac) == false)
	{
		std::cout << "Error Parsing." << '\n';
		return 1;
	}

//	initialiser l'horloge pour deque
	std::cout << MAGENTA << "***	Test deque ***\n" << NEUTRAL;

	std::clock_t dequeBegin = std::clock();
	testDeque(std::string (av[1]));
	std::clock_t dequeEnd = std::clock();

	double elapsed = static_cast<double>(dequeEnd - dequeBegin) / CLOCKS_PER_SEC;
	std::cout << "time for deque: " << elapsed << '\n';
//	initialiser l'horloge pour vector

	std::cout << MAGENTA << "***	Test vector	***\n" << NEUTRAL;

	std::clock_t vectorBegin = std::clock();
	testVector(std::string (av[1]));
	std::clock_t vectorEnd = std::clock();

	double V_elapsed = static_cast<double>(vectorEnd - vectorBegin) / CLOCKS_PER_SEC;
	std::cout << "time for vector: " << V_elapsed << '\n';

	return 0;
}

/*
void f()
{
	int a;
	int b;

	a = -9;
	b = 55;

	// booleano : es el resultado de una comparacion de una expresion, verdadera o falsa.
	//				si es falsa el valor es 0
	//				si es verdadera el valor es diferente de 0. Tipicamente el valor generico es 1

	// como se realiza?

	//		operadores:
	//					< mayor que
	//					> menor que
	//				   == igual que
	//				   <= menor o igual que
	//				   >= mayor o igual que
	//				   != diferente que
	//					! si es falso 

	//		evaluacion de un valor numerico de tipo char. 

	//		instrucciones:
	//					if ()
	//					while ()
	//					asignacion = booleano

	//     8 < 10 ==> 
	//     80 < 10 ==> 

	//     8 > 10 ==> 

	//     8 < 8 ==> 
	//     8 > 8 ==> 
	//     8 <= 8 ==> 

	// ejemplo con if ()

	// ejemplo con while ()

	// ejemplo con asignacion = booleando

	// operadores logicos && || 

	// sintaxis: (expresion_izq operador expresion_der)

	// MODO DE FUNCIONAMIENTO

	//	con && AMBOS resultados deben satisfacer ambas expresiones
	// 	con || debe satisfacer al menos una de las expresiones

	// se realizan de izquierda a derecha: 
	//			con && primero se evalua exp_izq. se es exitoso se evalua exp_der
	//					sino el resultado es falso

	//			con || primero se evalua exp_izq. si no es exitoso se evalua exp_der 

}*/
