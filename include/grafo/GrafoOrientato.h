/******************************************************************************\
*
* File:          GrafoOrientato.h
* Creation date: April 20, 2006
* Author:        Francesco Iovine, Massimiliano Macchia
*
* Purpose:       Fig. 11.2 , 11.4(a)
*
* License:       See the end of this file for license information
* 
* Modifications:
* 	1) Classe trasformata in un template<class T> per poter cambiare a piacimento
* 	   il tipo di peso di un arco.
* 	   June 23, 2008. Alessio Sclocco
*
\******************************************************************************/
#ifndef _GRAFOORIENTATO_H
#define _GRAFOORIENTATO_H

#include <grafo/Grafo.h>


namespace asd {



template< class T> class GrafoOrientato : virtual public Grafo< T >
{
  public:
	GrafoOrientato();
	virtual ~GrafoOrientato();

    bool diretto() const { return true; };

    bool sonoAdiacenti(vertice* x,vertice* y) const;
    unsigned inDegree(vertice* v) const;
	unsigned outDegree(vertice* v) const;
	void verticiAdiacenti(vertice* v, std::vector<vertice*> &vec) const;
	void verticiAdiacenti(vertice* v, std::vector< adiacente< T > > &vec) const;
};



/*
Costruttore.
*/
template< class T> GrafoOrientato< T >::GrafoOrientato()
{}



/*
Distruttore.
*/
template< class T > GrafoOrientato< T >::~GrafoOrientato()
{}



/*
Restituisce true se esiste l'arco (x, y), e false altrimenti.
*/
template< class T > bool GrafoOrientato< T >::sonoAdiacenti(vertice* x, vertice* y) const
{
    arco< T > *e;
    for_each_arco(e,(*this))
      if(e->sorg==x && e->dest==y)
        return true;

    return false;
}



/*
Restituisce il grado in ingresso del vertice v.
*/
template< class T > unsigned GrafoOrientato< T >::inDegree(vertice* v) const
{
    unsigned g = 0;
    arco< T > *e;
    for_each_arco(e,(*this))
      if(e->dest == v)
        ++g;

    return g;
}



/*
Restituisce il grado in uscita del vertice v.
*/
template< class T > unsigned GrafoOrientato< T >::outDegree(vertice* v) const
{
    unsigned g = 0;
    arco< T > *e;
    for_each_arco(e,(*this))
      if(e->sorg == v)
        ++g;

    return g;
}



/*
Riempie il vector vec con i vertici adiacenti a v.
*/
template< class T > void GrafoOrientato< T >::verticiAdiacenti(vertice* v, std::vector<vertice*> &vec) const
{
    arco< T > *e;
	vec.clear();
    for_each_arco(e,(*this))
      if(e->sorg == v)
        vec.push_back(e->dest);
}



/*
Riempie il vector vec con oggetti 'adiacente' rispetto a v.
*/
template< class T > void GrafoOrientato< T >::verticiAdiacenti(vertice* v, std::vector< adiacente< T > > &vec) const
{
    arco< T > *e;
	vec.clear();
    for_each_arco(e,(*this))
      if(e->sorg == v)
        vec.push_back( adiacente< T >(e->dest,e->costo) );
}


}  // namespace asd


#endif /* _GRAFOORIENTATO_H */



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
