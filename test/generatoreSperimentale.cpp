/******************************************************************************\
*
* File:          generatoreSperimentale.cpp
* Creation date: March 7, 2009
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#include <arcoTipo.h>

#include <algoritmi/cammini_minimi.h>
#include <grafo/GrafoNonOrientatoBetaMetrico_ListaArchi.h>
#include <tsp/TSPInstance.h>
#include <tsp/TSPWriter.h>
#include <ArgumentList.h>
#include <Space.h>
#include <Point.h>

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <map>

using namespace asd;
using sclocco::ArgumentList;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::istringstream;
using std::map;
using std::pair;

int main(int argc, char *argv[]) {
	unsigned int n = 0;
	double beta = 0.0;
	bool verbose = false, correggi = false, shortest = false, l1 = false, l2 = false, linf = false, endpoint = false;
	w_type maxPeso = 100000;
	string outfile = "";
	istringstream converter;
	GrafoNonOrientatoBetaMetrico_ListaArchi< w_type > grafo;
	TSPInstance< w_type > problema;
	TSPWriter< w_type > *writer;

	ArgumentList args = ArgumentList(argc, argv);

	if ( argc < 7 || argc > 9 ) {
		cerr << "Utilizzo: " << args.getFirst() << " [-c] [-v] [-s|-e|-l1|-l2|-li] -n <nodi> -b <beta> <outfile>" << endl;
		cerr << "\t-c\t : correggi se non beta metrico;" << endl;
		cerr << "\t-s\t : metrica shortest path;" << endl;
		cerr << "\t-e\t : metrica endpoint;" << endl;
		cerr << "\t-l1\t : metrica spazio l1;" << endl;
		cerr << "\t-l2\t : metrica spazio l2;" << endl;
		cerr << "\t-li\t : metrica spazio linf;" << endl;
		cerr << "\t-v\t : verboso." << endl << endl;
		return -1;
	}
	else {
		cout << args.getFirst() << endl;
	}

	verbose = args.getSwitch("-v");
	correggi = args.getSwitch("-c");
	shortest = args.getSwitch("-s");
	endpoint = args.getSwitch("-e");
	l1 = args.getSwitch("-l1");
	l2 = args.getSwitch("-l2");
	linf = args.getSwitch("-li");
	converter.str(args.getSwitchArgument("-n"));
	converter >> n;
	converter.clear();
	converter.str(args.getSwitchArgument("-b"));
	converter >> beta;

	if ( n < 2 || beta < 0.5 ) {
		cerr << "Il numero di nodi del grafo dev'essere maggiore di 2 ed il valore di beta >= 0.5" << endl;
		return -1;
	}

	outfile = args.getFirst();

	grafo.clear();
	problema.clear();
	grafo.setBeta(beta);

	srand(time(NULL));

	if ( shortest ) {
		/* Metrica shortest path */

		for ( unsigned int i(0); i < n; i++ ) {
			vertice *temp = grafo.aggiungiVertice();
			temp->setKey(i);
		}

		for ( Grafo< w_type >::vertice_iterator x = grafo.lista_vertici.begin(); x != --(grafo.lista_vertici.end()); x++ ) {
			Grafo< w_type >::vertice_iterator temp = x;
			for ( Grafo< w_type >::vertice_iterator y = ++temp; y != grafo.lista_vertici.end(); y++ ) {
				grafo.aggiungiArco(*x, *y, static_cast< w_type >(1.0 + (maxPeso * (rand() / (RAND_MAX + 1.0)))));
			}
		}

		map< pair<vertice*, vertice*>, w_type > distanze = FloydWarshall(grafo);

		for ( Grafo< w_type >::vertice_iterator x = grafo.lista_vertici.begin(); x != --(grafo.lista_vertici.end()); x++ ) {
			Grafo< w_type >::vertice_iterator temp = x;
			for ( Grafo< w_type >::vertice_iterator y = ++temp; y != grafo.lista_vertici.end(); y++ ) {
				if ( distanze[pair<vertice*, vertice*>(*x, *y)] < grafo.getPesoArcoCompreso(*x, *y) ) {
					(grafo.getArcoCompreso(*x, *y))->costo = distanze[pair<vertice*, vertice*>(*x, *y)];
				}
			}
		}
	}
	else if ( endpoint ) {
		/* Metrica endpoint */

	}
	else {
		Space< w_type > spazio;
		map< vertice *, Point * > verticeToPoint;

		for ( unsigned int i(0); i < n; i++ ) {
			vertice *temp = grafo.aggiungiVertice();
			temp->setKey(i);
			verticeToPoint[temp] = spazio.addPoint(static_cast< w_type >(1.0 + (maxPeso * (rand() / (RAND_MAX + 1.0)))), static_cast< w_type >(1.0 + (maxPeso * (rand() / (RAND_MAX + 1.0)))));
		}

		for ( Grafo< w_type >::vertice_iterator v = grafo.lista_vertici.begin(); v != --(grafo.lista_vertici.end()); v++ ) {
			Grafo< w_type >::vertice_iterator temp = v;
			for ( Grafo< w_type >::vertice_iterator u = ++temp; u != grafo.lista_vertici.end(); u++ ) {
				if ( l1 ) {
					/* Metrica spazio l1 */
					grafo.aggiungiArco(*v, *u, static_cast< w_type >(spazio.l1Distance(verticeToPoint[*v], verticeToPoint[*u])));
				}
				else if ( l2 ) {
					/* Metrica spazio l2 */
					grafo.aggiungiArco(*v, *u, static_cast< w_type >(spazio.l2Distance(verticeToPoint[*v], verticeToPoint[*u])));
				}
				else if ( linf ) {
					/* Metrica spazio linf */
					grafo.aggiungiArco(*v, *u, static_cast< w_type >(spazio.lInfDistance(verticeToPoint[*v], verticeToPoint[*u])));
				}
			}
		}
	}

	if ( verbose ) {
		cout << "Grafo generato con n = " << grafo.numVertici() << " ed m = " << grafo.numArchi() << endl;
	}

	if ( correggi ) {
		while ( !grafo.verifyBetaMetric(correggi) ) {};
		if ( verbose ) {
			cout << "Il grafo è risultato " << grafo.getBeta() << "-metrico." << endl;
		}
	}

	problema.setProblemType("TSP");
	problema.setEdgeWType("EXPLICIT");
	problema.setEdgeWFormat("UPPER_ROW");
	problema.setGrafo(&grafo);

	writer = new TSPWriter< w_type >(&problema);
	writer->setOutputFile(outfile);
	if ( !writer->write() ) {
		cerr << "Si e' verificato un problema durante il salvataggio dell'istanza su file." << endl;
		delete writer;
		return 1;
	}
	delete writer;

	if ( verbose ) {
		cout << "L'istanza e' stata salvata in " << outfile << endl;
	}

	return 0;
}

/******************************************************************************\
 * Copyright (C) 2008 Alessio Sclocco <alessio@sclocco.eu>

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
\******************************************************************************/
