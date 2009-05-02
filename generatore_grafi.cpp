/******************************************************************************\
*
* File:          generatore_grafi.cpp
* Creation date: September 27, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#include <arcoTipo.h>

#include <grafo/GrafoNonOrientatoBetaMetrico_ListaArchi.h>
#include <tsp/TSPInstance.h>
#include <tsp/TSPWriter.h>
#include <ArgumentList.h>

#include <iostream>
#include <sstream>
#include <string>

using namespace asd;
using sclocco::ArgumentList;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::istringstream;

int main(int argc, char *argv[]) {
	unsigned int n = 0;
	double beta = 0.0;
	bool verbose = false, correggi = false;
	string outfile = "";
	istringstream converter;
	GrafoNonOrientatoBetaMetrico_ListaArchi< w_type > grafo;
	TSPInstance< w_type > problema;
	TSPWriter< w_type > *writer;

	ArgumentList args = ArgumentList(argc, argv);

	if ( argc < 6 || argc > 8 ) {
		cerr << "Utilizzo: " << args.getFirst() << " [-c] [-v] -n <nodi> -b <beta> <outfile>" << endl;
		cerr << "\t-c : correggi se non beta metrico;" << endl;
		cerr << "\t-v : verboso." << endl << endl;
		return -1;
	}
	else {
		cout << args.getFirst() << endl;
	}

	verbose = args.getSwitch("-v");
	correggi = args.getSwitch("-c");
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
	grafo.generaRandom(n);

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
