#include "PmergeMe.hpp"

int main()
{
	PmergeMe p;
	const std::string s = "48 0 -12 8 -56 102 6 7 -80 43 -812 64 23 81 57 -478 -46 -32 -67 345 686 54";

	std::cout << s << '\n';
	if (p.parseNumbers(s) == false)
	{
		std::cout << "Error Parsing." << '\n';
		return 1;
	}
	std::cout << "Todo bien" << '\n';

//	itinialiser l'horloge pour deque

// create le deque min / max
	p.createStack(s, p._deque);
	//std::cout << "\nDeque\n";
	//p.printStack(p._deque);
	p.separateMinMax(p._deque, p._Dmin, p._Dmax);

//print les deque
	std::cout << "Min deque\n";
	p.printStack(p._Dmin);
	std::cout << "\nMax deque\n";
	p.printStack(p._Dmax);

	std::cout << MARRON << "Secuencia JACOBSTHAL\n" << NEUTRAL;
	p.generate_jacobsthal_sequence(p._Dmin, p._Djacobsthal);	
	p.printStack(p._Djacobsthal);
	std::cout << MARRON << "Grupos generados\n" << NEUTRAL;
	p.generate_jacobsthal_groups(p._Djacobsthal, p._Dgroups);
	p.printStack(p._Dgroups);

	std::cout << MARRON << "Push!\n" NEUTRAL;
	p.push_min(p._Dmax, p._Dmin, p._Dgroups);
	p.printStack(p._Dmax);
//	initialiser l'horloge pour vector
// create le vector min / max
	/*
	p.createStack(s, p._vect);
	std::cout << "\nVector\n";
	p.printStack(p._vect);
	p.separateMinMax(p._vect, p._Vmin, p._Vmax);
*/
//print les vectors
/*	std::cout << "\n\nMin vector\n";
	p.printStack(p._Vmin);
	std::cout << "\nMax vector\n";
	p.printStack(p._Vmax);
*/	return 0;
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
