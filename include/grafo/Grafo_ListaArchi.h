/******************************************************************************\
*
* File:          Grafo_ListaArchi.h
* Creation date: April 20, 2006
* Author:        Francesco Iovine, Massimiliano Macchia
*
* Purpose:       Fig. 11.2
*
* License:       See the end of this file for license information
*
* Modifications:
* 	1) Classe trasformata in un template<class T> per poter cambiare a piacimento
* 	   il tipo di peso di un arco.
* 	   June 20, 2008. Alessio Sclocco
* 	2) Reimplementazione dei metodi aggiungiArco e rimuoviArco per permettere la
* 	   ricerca di un arco in tempo costante.
* 	   January 26, 2009. Alessio Sclocco
*
\******************************************************************************/
#ifndef _GRAFO_LISTAARCHI_H
#define _GRAFO_LISTAARCHI_H

#include <grafo/Grafo.h>

#include <map>

namespace asd {



template<class T> class Grafo_ListaArchi : virtual public Grafo<T>
{
  public:  // operazioni
    Grafo_ListaArchi();
    virtual ~Grafo_ListaArchi();

    arco< T > *aggiungiArco(vertice* x, vertice* y, T costo);
    void rimuoviArco(arco< T > *e);

    // questi cinque metodi non hanno bisogno di corpo
    void inserisciVertice(vertice* v) {};
    void inserisciArco(arco<T>* e) {};
    void eliminaArco(arco<T>* e) {};
    void eliminaVertice(vertice* v) {};
    void reset() {};

  public: //typedefs
	//typedef std::list< vertice* >::iterator vertice_iterator;
    //typedef std::list< vertice* >::const_iterator vertice_const_iterator;
    //typedef std::list< arco* >::iterator arco_iterator;
    //typedef std::list< arco* >::const_iterator arco_const_iterator;

  protected:	// dati uso interno
	  std::map< std::pair< vertice *, vertice * >, arco< T > * > verticiToArco;

};



/* PUBLIC */

/*
Costruttore.
*/
template<class T> Grafo_ListaArchi<T>::Grafo_ListaArchi()
{

}



/*
Distruttore.
*/
template<class T> Grafo_ListaArchi<T>::~Grafo_ListaArchi()
{

}

template< class T > arco< T > *Grafo_ListaArchi< T >::aggiungiArco(vertice* x, vertice* y, T costo) {
	arco< T > *temp = Grafo< T >::aggiungiArco(x, y, costo);

	this->verticiToArco[ std::pair< vertice *, vertice *>(x, y) ] = temp;

	return temp;
}

template< class T > void Grafo_ListaArchi< T >::rimuoviArco(arco< T > *e) {
	vertice *x = e->sorg, *y = e->dest;
	Grafo< T >::rimuoviArco(e);

	this->verticiToArco.erase(std::pair< vertice *, vertice *>(x, y));
}


}  // namespace asd


#endif /* _GRAFO_LISTAARCHI_H */



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
