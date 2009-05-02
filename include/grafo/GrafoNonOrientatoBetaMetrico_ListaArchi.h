/******************************************************************************\
*
* File:          GrafoNonOrientatoBetaMetrico_ListaArchi.h
* Creation date: June 12, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef GRAFONONORIENTATOBETAMETRICO_LISTAARCHI_H_
#define GRAFONONORIENTATOBETAMETRICO_LISTAARCHI_H_


#include <grafo/GrafoNonOrientato_ListaArchi.h>
#include <grafo/GrafoNonOrientatoBetaMetrico.h>
#include <algoritmi/cammini_minimi.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <map>
#include <vector>

namespace asd {

template< class T = int > class GrafoNonOrientatoBetaMetrico_ListaArchi : public GrafoNonOrientato_ListaArchi< T >, virtual public GrafoNonOrientatoBetaMetrico< T > {
public:
	/* Costruttore di default */
	GrafoNonOrientatoBetaMetrico_ListaArchi();
	/* Distruttore di default */
	~GrafoNonOrientatoBetaMetrico_ListaArchi();
	/* Genera un grafo completo beta metrico di n vertici con pesi casuali */
	void generaRandom(unsigned int nodi);
	/* Verifica che il grafo rispetti la b-disuguaglianza triangolare */
	bool verifyBetaMetric(bool correct = false);
};

template< class T> GrafoNonOrientatoBetaMetrico_ListaArchi< T >::GrafoNonOrientatoBetaMetrico_ListaArchi() : GrafoNonOrientato_ListaArchi< T >() {
}

template< class T > GrafoNonOrientatoBetaMetrico_ListaArchi< T >::~GrafoNonOrientatoBetaMetrico_ListaArchi() {
}

template< class T > void GrafoNonOrientatoBetaMetrico_ListaArchi< T >::generaRandom(unsigned int nodi) {

	srand(time(NULL));
	this->clear();

	for ( unsigned int i(0); i < nodi; i++ ) {
		vertice *temp = this->aggiungiVertice();
		temp->setKey(i);
	}

	T base = 100000;
	T maxPeso = this->getBeta() * (base * 2);
	for ( typename asd::Grafo< T >::vertice_iterator x = this->lista_vertici.begin(); x != --(this->lista_vertici.end()); x++ ) {
		typename asd::Grafo< T >::vertice_iterator temp = x;
		for ( typename asd::Grafo< T >::vertice_iterator y = ++temp; y != this->lista_vertici.end(); y++ ) {
			this->aggiungiArco(*x, *y, static_cast< T >(base + static_cast< T >((maxPeso - base) * (rand() / (RAND_MAX + 1.0)))));
		}
	}
}

template< class T > bool GrafoNonOrientatoBetaMetrico_ListaArchi< T >::verifyBetaMetric(bool correct) {
	bool retval = true;
	double beta = this->getBeta();

	for ( typename asd::Grafo< T >::vertice_iterator x = this->lista_vertici.begin(); x != --(this->lista_vertici.end()); x++ ) {
		typename asd::Grafo< T >::vertice_iterator temp = x;
		for ( typename asd::Grafo< T >::vertice_iterator y = ++temp; y != --(this->lista_vertici.end()); y++ ) {
			temp = y;
			for ( typename asd::Grafo< T >::vertice_iterator z = ++temp; z != this->lista_vertici.end(); z++ ) {
				/* Controllare che il triangolo formato dai 3 vertici rispetti la disuguaglianza triangolare rafforzata */
				arco< T > *xy = this->getArcoCompreso(*x, *y), *xz = this->getArcoCompreso(*x, *z), *yz = this->getArcoCompreso(*y, *z);

				if ( static_cast< double >(xy->costo) > static_cast< double >(beta * (xz->costo + yz->costo)) ) {
					if ( correct ) {
						xy->costo = static_cast< T >(floor(beta * (xz->costo + yz->costo)));
						retval = false;
					}
					else {
						return false;
					}
				}

				if ( static_cast< double >(xz->costo) > static_cast< double >(beta * (xy->costo + yz->costo)) ) {
					if ( correct ) {
						xz->costo = static_cast< T >(floor(beta * (xy->costo + yz->costo)));
						retval = false;
					}
					else {
						return false;
					}
				}

				if ( static_cast< double >(yz->costo) > static_cast< double >(beta * (xy->costo + xz->costo)) ) {
					if ( correct ) {
						yz->costo = static_cast< T >(floor(beta * (xy->costo + xz->costo)));
						retval = false;
					}
					else {
						return false;
					}
				}
			}
		}
	}

	return retval;
}

} // namespace asd

#endif /*GRAFONONORIENTATOBETAMETRICO_LISTAARCHI_H_*/

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
