/*
 * TSPReaderTest.cpp
 *
 *  Created on: Jul 23, 2008
 *      Author: isazi
 */

#include <tsp/TSPInstance.h>
#include <tsp/TSPReader.h>
#include <iostream>

using namespace asd;
using std::cout;
using std::endl;

int main(void) {
	GrafoNonOrientatoBetaMetrico< int > *grafo;
	TSPInstance< int > gino;
	TSPReader< int > rino(&gino);

	rino.setInputFile("/home/isazi/Documents/University/Thesis/ALL_tsp/a280.tsp");

	if ( rino.read() ) {
		cout << "Tipo del problema: " << gino.getProblemType() << endl;
		cout << "Tipo degli archi: " << gino.getEdgeWType() << endl;
		cout << "Formato degli archi: " << gino.getEdgeWFormat() << endl;
		cout << endl;

		grafo = gino.getGrafo();

		cout << "Numero di nodi del grafo: " << grafo->numVertici() << endl;
	}
	else {
		cout << "Impossibile leggere l'istanza." << endl;
		return -1;
	}

	return 0;
}
