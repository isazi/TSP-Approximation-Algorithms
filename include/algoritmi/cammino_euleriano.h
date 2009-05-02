/******************************************************************************\
*
* File:          cammino_euleriano.h
* Creation date: December 16, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef CAMMINO_EULERIANO_H_
#define CAMMINO_EULERIANO_H_

#include <algoritmi/common.h>
#include <grafo/Grafo.h>
#include <Pila.h>

#include <vector>

namespace asd {

/* Algoritmo per il calcolo di un ciclo euleriano */

template< class T > void eulerianCycle(vertice *v, Pila< arco< T > * > *pila, std::vector< arco< T > * > &grafo);

/* Ciclo euleriano */

template< class T > void eulerianCycle(vertice *v, Pila< arco< T > * > *pila, std::vector< arco< T > * > &grafo) {
	int i = 0;
	arco< T > *tempArco = 0;

	while ( (i = findNextArco(grafo, v)) != -1 ) {
		if ( static_cast< unsigned int >(i) != (grafo.size() - 1) ) {
			arco< T > *e = grafo.at(i);
			grafo.at(i) = grafo.at(grafo.size()-1);
			grafo.at(grafo.size()-1) = e;
		}

		tempArco = grafo.at(grafo.size()-1);
		grafo.pop_back();

		if ( v == tempArco->dest ) {
			eulerianCycle(tempArco->sorg, pila, grafo);
		}
		else {
			eulerianCycle(tempArco->dest, pila, grafo);
		}

		pila->push(tempArco);
	}
}

} // namespace asd

#endif /* CAMMINO_EULERIANO_H_ */

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
