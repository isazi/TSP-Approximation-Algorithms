/******************************************************************************\
*
* File:          distribuzionePesi.cpp
* Creation date: March 5, 2009.
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#include <arcoTipo.h>

#include <grafo/GrafoNonOrientato.h>
#include <tsp/TSPInstance.h>
#include <tsp/TSPReader.h>

#include <ArgumentList.h>

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <sstream>

using namespace asd;
using std::cout;
using std::cerr;
using std::endl;
using std::fixed;
using std::setprecision;
using std::map;
using std::pair;
using std::string;
using std::istringstream;
using sclocco::ArgumentList;


int main(int argc, char *argv[]) {
	bool verbose = false;
	unsigned int intervalli = 10;
	/* Argomenti passati all'eseguibile */
	ArgumentList args = ArgumentList(argc, argv);

	if ( argc < 4 || argc > 5 ) {
		cerr << "Utilizzo: " << args.getFirst() << " [-v] -k <intervalli> <file_istanza_tsp>" << endl;
		cerr << "\t-k: numero di intervalli;" << endl;
		cerr << "\t-v : verboso." << endl << endl;
		return -1;
	}
	else {
		cout << endl << args.getFirst() << endl << endl;
	}

	/* Istanza del problema */
	TSPInstance< w_type > *problema = new TSPInstance< w_type >;
	/* Loader dell'istanza */
	TSPReader< w_type > *reader = new TSPReader< w_type >(problema);
	/* Nome del file da cui caricare l'istanza */
	string filename = "";
	istringstream converter;

	verbose = args.getSwitch("-v");
	converter.str(args.getSwitchArgument("-k"));
	converter >> intervalli;
	filename = args.getFirst();

	reader->setInputFile(filename);

	if ( ! reader->read() ) {
		cerr << "Impossibile leggere l'istanza." << endl;
		delete problema;
		delete reader;
		return -1;
	}

	if ( verbose ) {
		cout << "Istanza caricata, sta per essere eseguito l'algoritmo di calcolo della distribuzione dei pesi." << endl;
	}

	/* Mappa contenente gli intervalli di distribuzione dei pesi e le percentuali */
	map< double, double > *distribuzione = new map< double, double >();
	/* Dimensioni di un intervallo */
	double dimBlocco = 0;
	/* Peso minimo e massimo di un arco */
	w_type min = std::numeric_limits< w_type >::max(), max = std::numeric_limits< w_type >::min();

	for ( Grafo< w_type >::arco_const_iterator e = (problema->getGrafo())->lista_archi.begin(); e != (problema->getGrafo())->lista_archi.end(); e++ ) {
		if ( (*e)->costo < min ) {
			min = (*e)->costo;
		}

		if ( (*e)->costo > max ) {
			max = (*e)->costo;
		}
	}

	if ( verbose ) {
		cout << "Il peso minimo di un arco e' " << min << " mentre il peso massimo e' " << max << endl;
	}

	dimBlocco = (max - min) / static_cast< double >(intervalli);

	for ( unsigned int i(0); i <= intervalli; i++ ) {
		distribuzione->insert(pair< double, unsigned int >(min + (i * dimBlocco), 0));
	}

	for ( Grafo< w_type >::arco_const_iterator e = (problema->getGrafo())->lista_archi.begin(); e != (problema->getGrafo())->lista_archi.end(); e++ ) {
		for ( unsigned int i(1); i <= intervalli; i++ ) {
			if ( min + (i * dimBlocco) > (*e)->costo ) {
				((distribuzione->find(min + ((i - 1) * dimBlocco)))->second)++;
				break;
			}
		}
	}

	for ( map< double, double >::iterator i = (distribuzione->begin())++; i != distribuzione->end(); i++ ) {
		(*i).second = static_cast< double >(((*i).second * 100)) / (problema->getGrafo())->numArchi();
	}

	cout << endl;
	for ( map< double, double >::iterator i = (distribuzione->begin())++; i != --(distribuzione->end()); i++ ) {
		cout << fixed << setprecision (2) << "Da " << (*(--i)).first << " a " << (*(++i)).first << ": " << (*i).second << "%" << endl;
	}
	cout << endl;

	return 0;
}

/******************************************************************************\
 * Copyright (C) 2009 Alessio Sclocco <alessio@sclocco.eu>

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
