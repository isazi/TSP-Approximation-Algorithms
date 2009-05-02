/******************************************************************************\
*
* File:          matching.h
* Creation date: October 1, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef MATCHING_H_
#define MATCHING_H_

#include <algoritmi/KolmogorovBlossomV.h>
#include <grafo/GrafoNonOrientato.h>
#include <vector>
#include <map>

namespace asd {

/* Algoritmi per il Matching */

template< class T > void minCostPerfectMatching(const GrafoNonOrientato< T > *grafo, std::vector< arco< T > * > *sol);

/* Matching perfetto di peso minimo */

template< class T > void minCostPerfectMatching(const GrafoNonOrientato< T > *grafo, std::vector< arco< T > * > *sol) {
	/* Mappatura degli archi negli indici utilizzati da Kolmogorov */
	std::map< int, arco< T > * > indiceToArco;
	/* Struttura dati rappresentate il matching */
	PerfectMatching matching(grafo->numVertici(), grafo->numArchi());

	for ( typename Grafo< T >::arco_const_iterator e = grafo->lista_archi.begin(); e != grafo->lista_archi.end(); e++ ) {
		indiceToArco[matching.AddEdge(((*e)->sorg)->getKey(), ((*e)->dest)->getKey(), (*e)->costo)] = *e;
	}

	matching.Solve();

	/* Ricondurre la soluzione sul grafo originario */
	for ( int i(0); i < static_cast< int >(grafo->numArchi()); i++ ) {
		if ( matching.GetSolution(i) == 1 ) {
			sol->push_back(indiceToArco[i]);
		}
	}
}

} // namespace asd

#endif /* MATCHING_H_ */

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
