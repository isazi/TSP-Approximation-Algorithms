/*
 * tsp_approssimatoTest.cpp
 *
 *  Created on: Sep 8, 2008
 *      Author: isazi
 */

#include <grafo/GrafoNonOrientatoBetaMetrico_ListaArchi.h>
#include <albero/Albero.h>
#include <algoritmi/tsp_approssimato.h>
#include <algoritmi/stampa.h>

#include <vector>
#include <iostream>

using namespace asd;
using std::cout;
using std::endl;

int main(void) {
	GrafoNonOrientatoBetaMetrico_ListaArchi< double > grafo;
	std::vector< vertice* > dmst, rdmst, christ, cycle;

	grafo.setBeta(0.75);
	grafo.generaRandom(20);

	cout << "Generato un grafo random con " << grafo.numVertici() << " vertici e " << grafo.numArchi() << " archi." << endl;

	while ( ! grafo.verifyBetaMetric(true) ) {}

	cout << "Eseguiamo sul grafo l'algoritmo Double MST." << endl;
	doubleMST(&grafo, &dmst);
	cout << endl;

	cout << "Eseguiamo sul grafo l'algoritmo Refined Double MST." << endl;
	doubleMST(&grafo, &rdmst, true);
	cout << endl;

	cout << "Eseguiamo sul grafo l'algoritmo Christofides." << endl;
	christofides(&grafo, &christ);
	cout << endl;

	cout << "Eseguiamo sul grafo l'algoritmo Cycle Cover." << endl;
	cycleCover(&grafo, &cycle);
	cout << endl;

	cout << "Risultato dell'algoritmo Double MST: " << endl;;
	stampaCircuito(dmst, grafo);
	stampaDimensioneCircuito(dmst);
	stampaCostoCircuito(dmst, grafo);
	cout << endl;
	cout << "Risultato dell'algoritmo Refined Double MST: " << endl;;
	stampaCircuito(rdmst, grafo);
	stampaDimensioneCircuito(rdmst);
	stampaCostoCircuito(rdmst, grafo);
	cout << endl;
	cout << "Risultato dell'algoritmo Christofides: " << endl;;
	stampaCircuito(christ, grafo);
	stampaDimensioneCircuito(christ);
	stampaCostoCircuito(christ, grafo);
	cout << endl;
	cout << "Risultato dell'algoritmo Cycle Cover: " << endl;;
	stampaCircuito(cycle, grafo);
	stampaDimensioneCircuito(cycle);
	stampaCostoCircuito(cycle, grafo);
	cout << endl;

	return 0;
}
