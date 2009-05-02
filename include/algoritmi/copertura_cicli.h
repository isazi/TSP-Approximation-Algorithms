/******************************************************************************\
*
* File:          copertura_cicli.h
* Creation date: December 16, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef COPERTURA_CICLI_H_
#define COPERTURA_CICLI_H_

#include <algoritmi/common.h>
#include <grafo/Grafo.h>

#include <vector>

namespace asd {

/* Algoritmi per le coperture mediante cicli di un grafo */

template< class T > void cover(const std::vector< arco< T > * > *archiDelCiclo, std::vector< std::vector< arco< T > * > * > *cycles);

/* Funzioni accessorie e di uso interno */

template< class T > void creaCiclo(arco< T > *start, std::vector< arco< T > * > *tempCycle, const std::vector< arco< T > * > *archiDelCiclo, std::map< arco< T > *, bool > *foundArchi, std::map< vertice *, bool > *foundVertici);

/* Implementazioni */

template< class T > void cover(const std::vector< arco< T > * > *archiDelCiclo, std::vector< std::vector< arco< T > * > * > *cycles) {
	std::map< arco< T > *, bool > *foundArchi = new std::map< arco< T > *, bool >;
	std::map< vertice *, bool > *foundVertici = new std::map< vertice *, bool >;

	for ( typename std::vector< arco< T > * >::const_iterator x = archiDelCiclo->begin(); x != archiDelCiclo->end(); x++ ) {
		if ( foundArchi->find(*x) == foundArchi->end() && (foundVertici->find((*x)->sorg) == foundVertici->end() && foundVertici->find((*x)->dest) == foundVertici->end()) ) {
			/* Vettore che rappresenta un ciclo */
			std::vector< arco< T > * > *tempCycle = new std::vector< arco< T > * >;

			tempCycle->clear();

			creaCiclo(*x, tempCycle, archiDelCiclo, foundArchi, foundVertici);

			if ( tempCycle->size() >= 3 ) {
				cycles->push_back(tempCycle);

				for ( typename std::vector< arco< T > * >::const_iterator e = tempCycle->begin(); e != tempCycle->end(); e++ ) {
					foundArchi->insert(std::pair< arco< T > *, bool >(*e, true));
					foundVertici->insert(std::pair< vertice *, bool >((*e)->sorg, true));
					foundVertici->insert(std::pair< vertice *, bool >((*e)->dest, true));
				}
			}
			else {
				delete tempCycle;
			}
		}
	}

	delete foundArchi;
	delete foundVertici;
}

template< class T > void creaCiclo(arco< T > *start, std::vector< arco< T > * > *tempCycle, const std::vector< arco< T > * > *archiDelCiclo, std::map< arco< T > *, bool > *foundArchi, std::map< vertice *, bool > *foundVertici) {
	bool continua = true;
	int i = 0;
	std::vector< arco< T > * > mucchioArchi;
	std::vector< vertice * > mucchioVertici;
	std::vector< arco< T > * > fakeArchiDelCiclo = *archiDelCiclo;

	mucchioArchi.push_back(start);
	mucchioVertici.push_back(start->sorg);
	mucchioVertici.push_back(start->dest);

	while ( (i = findNextArco(fakeArchiDelCiclo, mucchioVertici.at(mucchioVertici.size()-1))) != -1 && continua ) {
		if ( static_cast< unsigned int >(i) != fakeArchiDelCiclo.size() - 1 ) {
			arco< T > *tempArco = fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1);
			fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1) = fakeArchiDelCiclo.at(i);
			fakeArchiDelCiclo.at(i) = tempArco;
		}

		if ( (foundArchi->find(fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1)) == foundArchi->end() && (foundVertici->find((fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1))->sorg) == foundVertici->end() && foundVertici->find((fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1))->dest) == foundVertici->end()) ) && ((contaOccorrenze((fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1))->sorg, &mucchioVertici) <= 2) && (contaOccorrenze((fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1))->dest, &mucchioVertici) <= 2)) ) {
			if ( fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1)->dest == mucchioVertici.at(mucchioVertici.size()-1) ) {
				mucchioVertici.push_back(fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1)->sorg);
			}
			else {
				mucchioVertici.push_back(fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1)->dest);
			}
			mucchioArchi.push_back(fakeArchiDelCiclo.at(fakeArchiDelCiclo.size()-1));

			if ( mucchioVertici.at(mucchioVertici.size()-1) == start->sorg ) {
				continua = false;
			}
		}

		fakeArchiDelCiclo.pop_back();
	}

	if ( continua == false ) {
		for ( typename std::vector< arco< T > * >::iterator e = mucchioArchi.begin(); e != mucchioArchi.end(); e++ ) {
			tempCycle->push_back(*e);
		}
	}
}

} // namespace asd

#endif /* COPERTURA_CICLI_H_ */

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
