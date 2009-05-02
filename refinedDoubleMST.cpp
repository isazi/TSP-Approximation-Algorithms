/******************************************************************************\
*
* File:          refinedDoubleMST.cpp
* Creation date: November 25, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#include <arcoTipo.h>

#include <grafo/GrafoNonOrientato.h>
#include <tsp/TSPInstance.h>
#include <tsp/TSPReader.h>
#include <algoritmi/tsp_approssimato.h>
#include <algoritmi/stampa.h>
#include <ArgumentList.h>

#include <iostream>
#include <string>
#include <vector>

using namespace asd;
using sclocco::ArgumentList;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char *argv[]) {
	bool verbose = false;
	/* Argomenti passati all'eseguibile */
	ArgumentList args = ArgumentList(argc, argv);

	if ( argc < 2 || argc > 3 ) {
		cerr << "Utilizzo: " << args.getFirst() << " [-v] <file_istanza_tsp>" << endl;
		cerr << "\t-v : verboso." << endl << endl;
		return -1;
	}
	else {
		cout << args.getFirst() << endl;
	}

	/* Istanza del problema */
	TSPInstance< w_type > *problema = new TSPInstance< w_type >;
	/* Loader dell'istanza */
	TSPReader< w_type > *reader = new TSPReader< w_type >(problema);
	/* Nome del file da cui caricare l'istanza */
	string filename = "";
	/* Soluzione del problema */
	vector< vertice * > *soluzione;

	verbose = args.getSwitch("-v");
	filename = args.getFirst();

	reader->setInputFile(filename);

	if ( ! reader->read() ) {
		cerr << "Impossibile leggere l'istanza." << endl;
		delete problema;
		delete reader;
		return -1;
	}

	if ( verbose ) {
		cout << "Istanza caricata, sta per essere eseguito l'algoritmo di risoluzione." << endl;
	}

	soluzione = new vector< vertice * >;

	doubleMST(problema->getGrafo(), soluzione, true);
	stampaDimensioneCircuito(*soluzione);
	cout << endl;
	stampaCostoCircuito(*soluzione, *(problema->getGrafo()));

	delete soluzione;
	delete problema;
	delete reader;
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
