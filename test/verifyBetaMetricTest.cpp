/*
 * verifyBetaMetricTest.cpp
 *
 *  Created on: Jan 21, 2009
 *      Author: Alessio Sclocco <alessio@sclocco.eu>
 */

typedef unsigned int w_type;

#include <grafo/GrafoNonOrientatoBetaMetrico_ListaArchi.h>
#include <tsp/TSPInstance.h>
#include <tsp/TSPReader.h>

#include <iostream>
#include <string>

using namespace asd;
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
	double beta;
	TSPInstance< w_type > *problema = new TSPInstance< w_type >;
	TSPReader< w_type > *reader = new TSPReader< w_type >(problema);
	string filename = argv[1];

	reader->setInputFile(filename);
	if ( reader->read() ) {
		cout << "Il problema e' stato letto ed è ora possibile la verifica." << endl;
		cout << "Il grafo del problema ha " << (problema->getGrafo())->numVertici() << " vertici e " << (problema->getGrafo())->numArchi() << " archi." << endl;
	}
	else {
		cout << "Non è stato possibile leggere il problema." << endl;
		return 1;
	}

	do {
		cout << "Inserire un valore per beta: ";
		cin >> beta;
	} while ( !(problema->getGrafo())->setBeta(beta) );

	if ( (problema->getGrafo())->verifyBetaMetric() ) {
		cout << "Il grafo è risultato beta-metrico." << endl;
	}
	else {
		cout << "Il grafo non è risultato beta-metrico." << endl;
	}

	return 0;
}
