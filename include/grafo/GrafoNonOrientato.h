/******************************************************************************\
*
* File:          GrafoNonOrientato.h
* Creation date: April 20, 2006
* Author:        Francesco Iovine, Massimiliano Macchia
*
* Purpose:       Fig. 11.2 , 11.3(a)
*
* License:       See the end of this file for license information
*
* Modifications:
* 	1) Classe trasformata in un template<class T> per poter cambiare a piacimento
* 	   il tipo di peso di un arco.
* 	   June 20, 2008. Alessio Sclocco
* 	2) Aggiunto il metodo sonoArchiAdiacenti.
* 	   January 15, 2009. Alessio Sclocco
*
\******************************************************************************/
#ifndef _GRAFONONORIENTATO_H
#define _GRAFONONORIENTATO_H

#include <grafo/Grafo.h>


namespace asd {

template< class T > class GrafoNonOrientato : virtual public Grafo< T >
{
    public:
		bool diretto() const { return false; };

        bool sonoAdiacenti(vertice* x, vertice* y) const;
        bool sonoArchiAdiacenti(arco< T > *e, arco< T > *l) const;
        void verticiAdiacenti(vertice* v, std::vector< vertice* > &vec) const;
        void verticiAdiacenti(vertice* v, std::vector< adiacente< T > > &vec) const;
};



/*
Restituisce true se esiste l'arco (x, y) oppure (y, x), e false altrimenti.
*/
template< class T > bool GrafoNonOrientato< T >::sonoAdiacenti(vertice* x, vertice* y) const
{
    arco< T >* e;
    for_each_arco(e,(*this))
      if(e->incideSu(x) && e->incideSu(y))
        return true;

    return false;
}

/*
 * Restituisce true se esiste un vertice compreso tra gli archi e ed l, false altrimenti.
 */
template< class T > bool GrafoNonOrientato< T >::sonoArchiAdiacenti(arco< T > *e, arco< T > *l) const {
	if ( e->sorg == l->sorg || e->sorg == l->dest ) {
		return true;
	}
	else if ( e->dest == l->sorg || e->dest == l->dest ) {
		return true;
	}
	else {
		return false;
	}
}


/*
Riempie il vector vec con i vertici adiacenti a v.
*/
template< class T > void GrafoNonOrientato< T >::verticiAdiacenti(vertice* v, std::vector< vertice* > &vec) const
{
    arco< T > *e;
	vec.clear();
    for_each_arco(e,(*this))
      if(e->incideSu(v))
        vec.push_back(e->opposto(v));
}



/*
Riempie il vector vec con oggetti 'adiacente' rispetto a v.
*/
template< class T > void GrafoNonOrientato< T >::verticiAdiacenti(vertice* v, std::vector< adiacente<T> > &vec) const {
    arco< T >* e;
	vec.clear();
    for_each_arco(e,(*this))
      if(e->incideSu(v))
        vec.push_back( adiacente< T >(e->opposto(v),e->costo) );
}



}  // namespace asd


#endif /* _GRAFONONORIENTATO_H */



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
