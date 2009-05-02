/******************************************************************************\
*
* File:          betaMetricita.cpp
* Creation date: March 31, 2009.
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

int mappaDistribuzione(double d);

int main(int argc, char *argv[]) {
	bool verbose = false;
	unsigned int distribuzione[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	double maxB = 0.5, minB = std::numeric_limits< double >::max(), averageB = 0, tempB = 1.0;
	/* Argomenti passati all'eseguibile */
	ArgumentList args = ArgumentList(argc, argv);

	if ( argc < 2 || argc > 3 ) {
		cerr << "Utilizzo: " << args.getFirst() << " [-v] <file_istanza_tsp>" << endl;
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
	filename = args.getFirst();

	reader->setInputFile(filename);

	if ( ! reader->read() ) {
		cerr << "Impossibile leggere l'istanza." << endl;
		delete problema;
		delete reader;
		return -1;
	}

	if ( verbose ) {
		cout << "Istanza caricata, sta per essere eseguito l'algoritmo di calcolo della beta metricita' del grafo." << endl;
	}

	unsigned int counter = ((problema->getGrafo())->numVertici() * ((problema->getGrafo())->numVertici() - 1) * ((problema->getGrafo())->numVertici() - 2)) / 2;

	for ( Grafo< w_type >::vertice_iterator x = (problema->getGrafo())->lista_vertici.begin(); x != --((problema->getGrafo())->lista_vertici.end()); x++ ) {
		Grafo< w_type >::vertice_iterator temp = x;
		for ( Grafo< w_type >::vertice_iterator y = ++temp; y != --((problema->getGrafo())->lista_vertici.end()); y++ ) {
			temp = y;
			for ( Grafo< w_type >::vertice_iterator z = ++temp; z != (problema->getGrafo())->lista_vertici.end(); z++ ) {

				w_type xy = (problema->getGrafo())->getPesoArcoCompreso(*x, *y), xz = (problema->getGrafo())->getPesoArcoCompreso(*x, *z), yz = (problema->getGrafo())->getPesoArcoCompreso(*y, *z);

				/* Primo vincolo */
				tempB = 1.01;
				while ( static_cast< double >(xy) < static_cast< double >(tempB * (xz + yz)) && tempB > 0.50 ) {
					tempB -= 0.01;
				}
				if ( tempB < 0.50 ) {
					tempB = 0.50;
				}
				if ( tempB > maxB ) {
					maxB = tempB;
				}
				if ( tempB < minB ) {
					minB = tempB;
				}
				distribuzione[mappaDistribuzione(tempB)] += 1;
				if ( mappaDistribuzione(tempB) != 10 ) {
					averageB += tempB;
				}

				/* Secondo vincolo */
				tempB = 1.01;
				while ( static_cast< double >(xz) < static_cast< double >(tempB * (xy + yz)) && tempB > 0.50 ) {
					tempB -= 0.01;
				}
				if ( tempB < 0.50 ) {
					tempB = 0.50;
				}
				if ( tempB > maxB ) {
					maxB = tempB;
				}
				if ( tempB < minB ) {
					minB = tempB;
				}
				distribuzione[mappaDistribuzione(tempB)] += 1;
				if ( mappaDistribuzione(tempB) != 10 ) {
					averageB += tempB;
				}

				/* Terzo vincolo */
				tempB = 1.01;
				while ( static_cast< double >(yz) < static_cast< double >(tempB * (xz + xy)) && tempB > 0.50 ) {
					tempB -= 0.01;
				}
				if ( tempB < 0.50 ) {
					tempB = 0.50;
				}
				if ( tempB > maxB ) {
					maxB = tempB;
				}
				if ( tempB < minB ) {
					minB = tempB;
				}
				distribuzione[mappaDistribuzione(tempB)] += 1;
				if ( mappaDistribuzione(tempB) != 10 ) {
					averageB += tempB;
				}
			}
		}
	}

	averageB /= (counter - distribuzione[10]);

	cout << fixed << setprecision (3) << endl;
	cout << "Il valore massimo di beta nel grafo è pari a: " << maxB << endl;
	cout << "Il valore minimo di beta nel grafo è pari a: " << minB << endl;
	cout << "Il valore medio di beta nel grafo è pari a: " << averageB << endl;
	cout << endl;
	cout << "La distribuzione è la seguente: " << endl;
	cout << endl;
	cout << "0.50 - 0.55 : " << static_cast< double >(((static_cast< double >(distribuzione[0]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << "0.56 - 0.60 : " << static_cast< double >(((static_cast< double >(distribuzione[1]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << "0.61 - 0.65 : " << static_cast< double >(((static_cast< double >(distribuzione[2]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << "0.66 - 0.70 : " << static_cast< double >(((static_cast< double >(distribuzione[3]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << "0.71 - 0.75 : " << static_cast< double >(((static_cast< double >(distribuzione[4]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << "0.76 - 0.80 : " << static_cast< double >(((static_cast< double >(distribuzione[5]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << "0.81 - 0.85 : " << static_cast< double >(((static_cast< double >(distribuzione[6]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << "0.86 - 0.90 : " << static_cast< double >(((static_cast< double >(distribuzione[7]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << "0.91 - 0.95 : " << static_cast< double >(((static_cast< double >(distribuzione[8]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << "0.96 - 1.00 : " << static_cast< double >(((static_cast< double >(distribuzione[9]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << "     > 1.00 : " << static_cast< double >(((static_cast< double >(distribuzione[10]) / 100) * 100) / (counter / 100)) << "%" << endl;
	cout << endl;

	return 0;
}

int mappaDistribuzione(double d) {
	unsigned int bottom = 50, top = 55, number = static_cast< unsigned int >(d * 100);

	for ( int i(0); i < 10; i++ ) {
		if ( bottom <= number && number <= top ) {
			return i;
		}
		else {
			bottom = top + 1;
			top += 5;
		}
	}

	return 10;
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
