/******************************************************************************\
*
* File:          visita_Albero.h
* Creation date: June 17, 2005 00:05
* Author:        Francesco Iovine
*
* License:       See the end of this file for license information
*
* Modifications:
* 	1)	Aggiunta una nuova versione della funzione visitaDFS che prende in
* 		input un albero ed un vettore da popolare.
* 		September 5, 2008. Alessio Sclocco
*
\******************************************************************************/

#ifndef _VISITA_ALBERO_H
#define _VISITA_ALBERO_H

#include <albero/Albero.h>
#include <grafo/GrafoNonOrientatoBetaMetrico.h>
#include <codapriorita/HeapFibonacci.h>
#include <Pila.h>
#include <Coda.h>

#include <vector>


namespace asd {

/*
Algoritmi di visita di un albero
rappresentato con una struttura collegata basata su liste di figli.
*/
template<class Chiave> void visitaDFS(nodo<Chiave>* r, void (*visita)(nodo<Chiave>*) );
template< class T1, class T2 > void visitaDFS(const Albero< T1 > &tree, std::vector< T1 > *tour, bool closest = false, const GrafoNonOrientatoBetaMetrico< T2 > *grafo = static_cast< const GrafoNonOrientatoBetaMetrico< T2 > * >(0));

template<class Chiave> void visitaDFSRicorsiva_preordine(nodo<Chiave>* r, void (*visita)(nodo<Chiave>*) );

template<class Chiave> void visitaDFSRicorsiva_postordine(nodo<Chiave>* r, void (*visita)(nodo<Chiave>*) );

template<class Chiave> void visitaBFS(nodo<Chiave>* r, void (*visita)(nodo<Chiave>*) );



/*
Figura 3.13
Visita in profondita' iterativa (preordine) di un albero
rappresentato con una struttura collegata basata su liste di figli.
L'insieme dei nodi aperti S e' rappresentato mediante una Pila.
*/
template<class Chiave> void visitaDFS(nodo<Chiave>* r, void (*visita)(nodo<Chiave>*) )
{
    typedef typename asd::nodo<Chiave>::lista_figli_rev_iterator lista_figli_rev_iterator;

    nodo<Chiave> *u, *v;

    Pila<nodo<Chiave>*> S;
    S.push(r);
    while (!( S.isEmpty() )) {
        u = S.pop();
        if (u != 0) {
            (*visita)(u);
            for_each_rev_figlio(v,u) S.push(v);
        }
    }
}

template< class T1, class T2 > void visitaDFS(const Albero< T1 > &tree, std::vector< T1 > *tour, bool closest, const GrafoNonOrientatoBetaMetrico< T2 > *grafo) {
	nodo< T1 > *v = tree.padre(0);
	typename asd::nodo< T1 >::lista_figli_const_iterator son;
	Pila< nodo< T1 >* > S;

	S.push(v);
	while ( !S.isEmpty() ) {
		v = S.pop();
		if ( v != 0 ) {
			tour->push_back(v->getChiave());

			if ( closest ) {
				HeapFibonacci< nodo< T1 >*, T2 > coda;
				Pila< nodo< T1 >* > reverse;

				for ( son = v->lista_figli.begin(); son != v->lista_figli.end(); son++ ) {
					coda.insert(*son, grafo->getPesoArcoCompreso(v->getChiave(), (*son)->getChiave()));
				}

				while ( ! coda.isEmpty() ) {
					reverse.push(coda.deleteMin());
				}

				while ( ! reverse.isEmpty() ) {
					nodo< T1 > *nodo = reverse.pop();
					S.push(nodo);
				}
			}
			else {
				for ( son = v->lista_figli.begin(); son != v->lista_figli.end(); son++ ) {
					S.push(*son);
				}
			}
		}
	}
}

template< class T > void visitaDFSCC(const Albero< T > &tree, std::vector< T > *tour) {
	nodo< T > *v = tree.padre(0);
	typename asd::nodo< T >::lista_figli_const_iterator son;
	Pila< nodo< T >* > S;

	S.push(v);
	while ( !S.isEmpty() ) {
		v = S.pop();
		if ( v != 0 ) {
			tour->push_back(v->getChiave());
			for ( son = v->lista_figli.begin(); son != v->lista_figli.end(); son++ ) {
				S.push(*son);
			}
		}
	}
}

/*
Figura 3.14
Visita in profondita' ricorsiva (preordine) di un albero
rappresentato con una struttura collegata basata su liste di figli.
I nodi aperti vengono mantenuti sfruttando
la pila dei record di attivazione delle chiamate ricorsive.
*/
template<class Chiave>
void visitaDFSRicorsiva_preordine(nodo<Chiave>* r, void (*visita)(nodo<Chiave>*) )
{
    typedef typename asd::nodo<Chiave>::lista_figli_iterator lista_figli_iterator;

    if(r == 0) return;
    (*visita)(r);
    nodo<Chiave>* v;
    for_each_figlio(v,r) visitaDFSRicorsiva_preordine(v, visita);
}



/*
Figura 3.14
Visita in profondita' ricorsiva (postordine) di un albero
rappresentato con una struttura collegata basata su liste di figli.
I nodi aperti vengono mantenuti sfruttando
la pila dei record di attivazione delle chiamate ricorsive.
*/
template<class Chiave>
void visitaDFSRicorsiva_postordine(nodo<Chiave>* r, void (*visita)(nodo<Chiave>*) )
{
    typedef typename asd::nodo<Chiave>::lista_figli_iterator lista_figli_iterator;

    if(r == 0) return;
    nodo<Chiave>* v;
    for_each_figlio(v,r) visitaDFSRicorsiva_postordine(v, visita);
    (*visita)(r);
}



/*
Figura 3.15
Visita in ampiezza di un albero
rappresentato con una struttura collegata basata su liste di figli.
L'insieme dei nodi aperti C e' rappresentato mediante una Coda.
*/
template<class Chiave>
void visitaBFS(nodo<Chiave>* r, void (*visita)(nodo<Chiave>*) )
{
    typedef typename asd::nodo<Chiave>::lista_figli_iterator lista_figli_iterator;

    nodo<Chiave> *u, *v;

    Coda<nodo<Chiave>*> C;
    C.enqueue(r);
    while (!( C.isEmpty() )) {
        u = C.dequeue();
        if (u != 0) {
            (*visita)(u);
            for_each_figlio(v,u) C.enqueue(v);
        }
    }
}

}  // namespace asd


#endif /* _VISITA_ALBERO_H */



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
