/******************************************************************************\
*
* File:          GrafoNonOrientato_ListaArchi.h
* Creation date: April 20, 2006
* Author:        Francesco Iovine, Massimiliano Macchia
*
* Purpose:       Fig. 11.2 , 11.3(b)
*                Tab. 11.1
*
* License:       See the end of this file for license information
*
* Modifications:
* 	1) Classe trasformata in un template<class T> per poter cambiare a piacimento
* 	   il tipo di peso di un arco.
* 	   June 20, 2008. Alessio Sclocco
* 	2) Aggiunta l'implementazione del metodo getArcoCompreso.
* 	   October 27, 2008. Alessio Sclocco
* 	3) Modificato il metodo sonoAdiacenti per sfruttare la nuova mappa degli
* 	   archi.
* 	   February 4, 2009. Alessio Sclocco
*
\******************************************************************************/
#ifndef _GRAFONONORIENTATO_LISTAARCHI_H
#define _GRAFONONORIENTATO_LISTAARCHI_H

#include <grafo/Grafo_ListaArchi.h>
#include <grafo/GrafoNonOrientato.h>


namespace asd {



template< class T > class GrafoNonOrientato_ListaArchi : virtual public Grafo_ListaArchi< T > , virtual public GrafoNonOrientato< T > {
  public:  // operazioni
    GrafoNonOrientato_ListaArchi();
    GrafoNonOrientato_ListaArchi(const GrafoNonOrientato_ListaArchi< T >& G);
    virtual ~GrafoNonOrientato_ListaArchi();
    bool sonoAdiacenti(vertice* x, vertice* y) const;
    /* Restituisce l'arco compreso tra i due vertici x ed y */
    arco< T > *getArcoCompreso(vertice *x, vertice *y) const;

  public: //typedefs
    typedef std::list< vertice* >::iterator vertice_iterator;
    typedef std::list< vertice* >::const_iterator vertice_const_iterator;
    typedef typename std::list< arco< T > * >::iterator arco_iterator;
    typedef typename std::list< arco< T > * >::const_iterator arco_const_iterator;
};



/* PUBLIC */

/*
Costruttore di default.
*/
template< class T > GrafoNonOrientato_ListaArchi< T >::GrafoNonOrientato_ListaArchi() : Grafo_ListaArchi< T >() {

}



/*
Distruttore.
*/
template< class T > GrafoNonOrientato_ListaArchi< T >::~GrafoNonOrientato_ListaArchi()
{

}



/*
Elimina il vertice v dalla rappresentazione interna.
*/
template< class T > bool GrafoNonOrientato_ListaArchi< T >::sonoAdiacenti(vertice* x, vertice* y) const {

	if ( this->verticiToArco.find(std::pair< vertice *, vertice *>(x, y)) != this->verticiToArco.end() ) {
		return true;
	}
	else if ( this->verticiToArco.find(std::pair< vertice *, vertice *>(y, x)) != this->verticiToArco.end() ) {
		return true;
	}
	else {
		return false;
	}
}

/* Restituisce l'arco compreso tra x ed y */
template< class T > arco< T > *GrafoNonOrientato_ListaArchi< T >::getArcoCompreso(vertice *x, vertice *y) const {
	if ( this->verticiToArco.find(std::pair< vertice *, vertice *>(x, y)) != this->verticiToArco.end() ) {
		return this->verticiToArco.at(std::pair< vertice *, vertice *>(x, y));
	}
	else if ( this->verticiToArco.find(std::pair< vertice *, vertice *>(y, x)) != this->verticiToArco.end() ) {
		return this->verticiToArco.at(std::pair< vertice *, vertice *>(y, x));
	}
	else {
		return 0;
	}
}

}  // namespace asd


#endif /* _GRAFONONORIENTATO_LISTAARCHI_H */



/******************************************************************************\
 * Copyright (C) 2006 ASD Team

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
\******************************************************************************/
