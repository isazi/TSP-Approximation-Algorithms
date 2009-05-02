
#include <arcoTipo.h>
#include <grafo/GrafoNonOrientatoBetaMetrico_ListaArchi.h>
#include <iostream>

using namespace asd;

int main(void) {
	GrafoNonOrientatoBetaMetrico_ListaArchi< w_type > grafo;
	double beta;
	unsigned int nodi;

	do {
		std::cout << "Inserire un valore per beta: ";
		std::cin >> beta;
	} while ( !grafo.setBeta(beta) );

	do {
		std::cout << "Inserire il numero di nodi desiderato: ";
		std::cin >> nodi;
	} while ( nodi < 2 );

	grafo.generaRandom(nodi);

	std::cout << std::endl;
	std::cout << "Grafo generato con n = " << grafo.numVertici() << ", m = " << grafo.numArchi() << std::endl;
	std::cout << std::endl;

	if ( grafo.verifyBetaMetric() ) {
		std::cout << "Grafo " << grafo.getBeta() << "-metrico." << std::endl;
	}
	else {
		char correct = 'N';
		std::cout << "Grafo non " << grafo.getBeta() << "-metrico." << std::endl;
		std::cout << "Si vuole tentare di correggere il grafo (S/N): ";
		std::cin >> correct;
		if ( correct == 'S' ) {
			unsigned int counter(0);
			while ( !grafo.verifyBetaMetric(true) ) {
				counter++;
			}
			std::cout << "Sono state necessarie " << counter << " iterazioni per correggere il grafo." << std::endl;
		}
	}

	for ( asd::GrafoNonOrientatoBetaMetrico_ListaArchi< w_type >::vertice_const_iterator v = grafo.lista_vertici.begin(); v != --(grafo.lista_vertici.end()); v++ ) {
		asd::GrafoNonOrientatoBetaMetrico_ListaArchi< w_type >::vertice_const_iterator temp = v;
		for ( asd::GrafoNonOrientatoBetaMetrico_ListaArchi< w_type >::vertice_const_iterator u = ++temp; u != grafo.lista_vertici.end(); u++ ) {
			w_type dist = grafo.getPesoArcoCompreso(*v, *u);
			std::cout << "La distanza tra " << (*v)->getKey() << " e " << (*u)->getKey() << " è: ";
			if ( dist != std::numeric_limits< w_type >::max() ) {
				std::cout << dist;
			}
			else {
				std::cout << "INF";
			}
			std::cout << std::endl;
		}
	}

	std::cout << std::endl;
	return 0;
}
