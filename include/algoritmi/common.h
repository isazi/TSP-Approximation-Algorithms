/******************************************************************************\
*
* File:          common.h
* Creation date: December 16, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef COMMON_H_
#define COMMON_H_

namespace asd {

/* Funzioni accessorie di vario utilizzo */

template< class T > int findNextArco(const std::vector< arco< T > * > &archi, const arco< T > *pos);
vertice *getVerticeAssociato(vertice *v, const std::map< vertice *, std::vector< vertice * > * > *v_ausi);
int contaOccorrenze(const vertice *v, const std::vector< vertice * > *vertici);
template< class T > int contaOccorrenze(const arco< T > *e, const std::vector< arco< T > * > *archi);

/* Implementazioni */

template< class T > int findNextArco(const std::vector< arco< T > * > &archi, vertice *pos) {
	for ( unsigned int i(0); i < archi.size(); i++ ) {
		if ( archi[static_cast< int >(i)]->incideSu(pos) ) {
			return static_cast< int >(i);
		}
	}

	return -1;
}

template< class T > arco< T > *getArcoOriginale(arco< T > *e, const std::map< arco< T > *, std::vector< arco< T > * > * > *e_ausi) {
	for ( typename std::map< arco< T > *, std::vector< arco< T > * > * >::const_iterator row = e_ausi->begin(); row != e_ausi->end(); row++ ) {
		for ( typename std::vector< arco< T > * >::const_iterator l = (*row).second->begin(); l != (*row).second->end(); l++ ) {
			if ( e == *l ) {
				return (*row).first;
			}
		}
	}

	return 0;
}

int contaOccorrenze(const vertice *v, const std::vector< vertice * > *vertici) {
	int i = 0;
	for ( std::vector< vertice * >::const_iterator u = vertici->begin(); u != vertici->end(); u++ ) {
		if ( *u == v ) {
			i++;
		}
	}

	return i;
}

template< class T > int contaOccorrenze(const arco< T > *e, const std::vector< arco< T > * > *archi) {
	int i = 0;
	for ( typename std::vector< arco< T > * >::const_iterator l = archi->begin(); l != archi->end(); l++ ) {
		if ( *l == e ) {
			i++;
		}
	}

	return i;
}

} // namespace asd

#endif /* COMMON_H_ */

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
