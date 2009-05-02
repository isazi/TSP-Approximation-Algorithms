/******************************************************************************\
*
* File:          stampa.h
* Creation date: September 8, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef STAMPA_H_
#define STAMPA_H_

#include <grafo/Grafo.h>
#include <iostream>
#include <iomanip>
#include <vector>

using std::cout;
using std::endl;

namespace asd {

/* Funzioni di stampa */

template< class T > void stampaCircuito(const std::vector< vertice* > &tour, const Grafo< T > &grafo);
void stampaDimensioneCircuito(const std::vector< vertice* > &tour);
template< class T > void stampaCostoCircuito(const std::vector< vertice* > &tour, const Grafo< T > &grafo);

/* Funzione che stampa un vettore di vertici */

template< class T > void stampaCircuito(const std::vector< vertice* > &tour, const Grafo< T > &grafo) {

	for ( std::vector< vertice* >::const_iterator v = tour.begin(); v != tour.end(); v++ ) {
		if ( v != --(tour.end()) ) {
			cout << (*v)->getKey() << " -> ";
		}
		else {
			cout << (*v)->getKey() << " -> " << (*(tour.begin()))->getKey() << endl;
		}
	}
}

void stampaDimensioneCircuito(const std::vector< vertice * > &tour) {
	cout << "Dimensione del tour: " << tour.size();
	cout << endl;
}

template< class T > void stampaCostoCircuito(const std::vector< vertice* > &tour, const Grafo< T > &grafo) {
	double sum = 0.0;

	for ( std::vector< vertice* >::const_iterator v = tour.begin(); v != tour.end(); v++ ) {
		std::vector< vertice* >::const_iterator temp;
		if ( v != --(tour.end()) ) {
			temp = v;
			sum += grafo.getPesoArcoCompreso(*v, *(++temp));
		}
		else {
			temp = tour.begin();
			sum += grafo.getPesoArcoCompreso(*v, *temp);
		}
	}

	cout << "Costo del tour: " << std::fixed << std::setprecision (6) << sum << endl;
	cout << endl;
}

} // namespace asd

#endif /* STAMPA_H_ */

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
