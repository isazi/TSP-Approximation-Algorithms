/******************************************************************************\
*
* File:          cammini_minimi.h
* Creation date: September 16, 2005
* Author:        Francesco Iovine
*
* Purpose:       Fig.13.4, Fig.13.6, Fig.13.7, Fig.13.11, Fig.13.12
*
* License:       See the end of this file for license information
*
* Modifications:
*   1)  Modificato per compatibilita' con la nuova struttura dati Grafo.
*       April 20, 2006. Francesco Iovine && Massimiliano Macchia
* 	2)  Reso possibile il supporto ai nuovi grafi parametrici.
* 		June 23, 2008. Alessio Sclocco
* 	3)	Modificata la funzione FloydWarshall per renderla piu' veloce; a causa
* 		delle modifiche la funzione lavora solo con i grafi non orientati.
* 		February 2, 2009. Alessio Sclocco
*
\******************************************************************************/
#ifndef _CAMMINIMINIMI_H
#define _CAMMINIMINIMI_H

#include <grafo/Grafo.h>
#include <albero/Albero.h>
#include <codapriorita/HeapFibonacci.h>
#include <Coda.h>

#include <list>
#include <map>


#define for_each_vertice_in_ordinamento_topologico(u,ord)                                  \
        u = *(ord.begin());                                                                \
        for (std::list< vertice* >::iterator it = ord.begin(); it != ord.end(); ++it, u = *it)


namespace asd {

/*
Algoritmi per trovare l'albero dei cammini minimi di un grafo orientato.
*/
template< class T > vertice_array< T > BellmanFord(const Grafo< T > &G, vertice* s);
template< class T > std::list< vertice* > ordinamentoTopologico(const Grafo< T > &G);
template< class T > vertice_array< T > distanzeAciclico(const Grafo< T > &G, vertice* s);
template< class T > vertice_array< T > Dijkstra(const Grafo< T > &G, vertice* s, Albero< vertice* >& Tree);
template< class T > std::map< std::pair<vertice*, vertice*>, T > FloydWarshall(const Grafo< T > &G);



/*
Figura 13.4
Algoritmo di Bellman e Ford per il calcolo delle distanze a partire da una sorgente s
in un grafo orientato G con n vertici ed m archi.
*/
template< class T > vertice_array< T > BellmanFord(const Grafo< T > &G, vertice* s)
{
    unsigned n = G.numVertici();
    vertice *v, *u;
    arco< T > *e;
    T w;

    /* inizializza D tale che Dsv = +infinito per v != s, e Dss = 0 */
    vertice_array< T > Ds;
    for_each_vertice(v,G) Ds[v] = INFINITO;
    Ds[s] = 0;

    for (unsigned i = 1; i <= n; ++i) {
        /* for each ( (u,v) in E ) do */
        for_each_arco(e,G) {
            u = e->sorg;  v = e->dest;  w = e->costo;  // e = (u,v) con costo w
            if (Ds[u] != INFINITO) {
                if (Ds[u] + w < Ds[v]) Ds[v] = Ds[u] + w;  // rilassamento
            }
        }
    }
    return Ds;
}



/*
Figura 13.6
Algoritmo per il calcolo di un ordinamento topologico del grafo orientato aciclico G.
*/
template< class T > std::list< vertice* > ordinamentoTopologico(const Grafo< T > &G)
{
    vertice *u, *v;

    /* (Gc <- G) implementata con una coda di puntatori ai vertici del grafo */
    vertice_array<unsigned> archi_entranti;
    Coda<vertice*> C;

    std::list<vertice*> ord;  // ord <- lista vuota di vertici

    /* while ( esiste un vertice u senza archi entranti in G) do */
    for_each_vertice(u,G) {
        archi_entranti[u] = 0;
    }
    for_each_vertice(u,G) {
        for_each_vertice_adiacente(v,u,G) ++(archi_entranti[v]);
    }
    for_each_vertice(u,G) {
        if (archi_entranti[u] == 0) C.enqueue(u);
    }
    while (!( C.isEmpty() )) {
            u = C.dequeue();
            ord.push_back(u);  // appendi u come ultimo elemento di ord
            for_each_vertice_adiacente(v,u,G) {
                --(archi_entranti[v]);
                if (archi_entranti[v] == 0) C.enqueue(v);
            }
    }

    return ord;
}



/*
Figura 13.7
Algoritmo per il calcolo delle distanze a partire da una sorgente s
in un grafo orientato aciclico G con n vertici ed m archi.
*/
template< class T > vertice_array< T > distanzeAciclico(const Grafo< T > &G, vertice* s)
{
    vertice *v, *u;
    arco< T > *e;
    T w;

    /* inizializza D tale che Dsv = +infinito per v != s, e Dss = 0 */
    vertice_array< T > Ds;
    for_each_vertice(v,G) Ds[v] = INFINITO;
    Ds[s] = 0;

    std::list<vertice*> ord = ordinamentoTopologico(G);

    for_each_vertice_in_ordinamento_topologico(u,ord) {
        for_each_arco(e,G) {  // for each ( (u,v) in E ) do
            u = e->sorg;  v = e->dest;  w = e->costo;  // e = (u,v) con costo w
            if (Ds[u] != INFINITO) {
                if (Ds[u] + w < Ds[v]) Ds[v] = Ds[u] + w;  // rilassamento
            }
        }
    }
    return Ds;
}



/*
Figura 13.11
Algoritmo di Dijkstra implementato con una coda con priorita'.
*/
template< class T > vertice_array< T > Dijkstra(const Grafo< T > &G, vertice* s, Albero< vertice* >& Tree)
{
    vertice *v, *u;
    T w;

    vertice_array< nodo< vertice* >* > nodi_albero;
    vertice_array< nodo_binomiale< vertice*, T>* > nodi_codapriorita;

    vertice_array< T > Ds;
    for_each_vertice(v,G) Ds[v] = INFINITO;

    /* T = albero formato da un solo nodo s */
    Tree.clear();
    nodi_albero[s] = Tree.aggiungiNodo(s);

    /* CodaPriorita S */
    HeapFibonacci< vertice*, T > S;
    Ds[s] = 0;
    nodi_codapriorita[s] = S.insert(s,0);

    while ( !(S.isEmpty()) ) {
        u = S.deleteMin();
        for_each_vertice_adiacente_a_distanza(v,u,w,G) {  // for each ( arco (u,v) in G ) do
            if (Ds[v] == INFINITO) {
                nodi_codapriorita[v] = S.insert(v, Ds[u] + w);
                Ds[v] = Ds[u] + w;
                nodi_albero[v] = Tree.aggiungiNodo(v, nodi_albero[u]); //rendi u padre di v in T
            }
            else if (Ds[u] + w < Ds[v]) {
                S.decreaseKey(nodi_codapriorita[v], Ds[v] - Ds[u] - w);
                Ds[v] = Ds[u] + w;
                Tree.spostaSottoalbero(nodi_albero[v], nodi_albero[u]); //rendi u nuovo padre di v in T
            }
        }
    }
    // return T

    return Ds;  // restituisce i cammini minimi dal vertice 's'
}



/*
Figura 13.12
Algoritmo di Floyd e Warshall per il calcolo delle distanze tra tutte le coppie di vertici.
*/
template< class T > std::map< std::pair<vertice*, vertice*>, T > FloydWarshall(const Grafo< T > &G) {
	std::map< std::pair<vertice*, vertice*>, T > D;
	vertice *x, *y, *v;
	std::pair<vertice*, vertice*> xy, xv, vy;

	/* inizializza D tale che Dxy = w(x,y) se (x,y) in E, e Dxy = +infinito altrimenti */
	for ( typename Grafo< T >::vertice_const_iterator v = G.lista_vertici.begin(); v != --(G.lista_vertici.end()); v++ ) {
		D[std::pair< vertice *, vertice * >(*v, *v)] = 0;
		typename Grafo< T >::vertice_const_iterator temp = v;
		for ( typename Grafo< T >::vertice_const_iterator u = ++temp; u != G.lista_vertici.end(); u++ ) {
			T value = G.getPesoArcoCompreso(*v, *u);
			D[std::pair< vertice *, vertice * >(*v, *u)] = value;
			D[std::pair< vertice *, vertice * >(*u, *v)] = value;
		}
	}

	for_each_vertice(v,G) {
		/* for each ((x,y) in V x V) do */
		for_each_vertice(x,G) {
			for_each_vertice(y,G) {
				xv.first = x;  xv.second = v;  // xv = (x,v)
				vy.first = v;  vy.second = y;  // vy = (v,y)
				xy.first = x;  xy.second = y;  // xy = (x,y)
				if (D[xv] != INFINITO && D[vy] != INFINITO) {
					if (D[xv] + D[vy] < D[xy])  D[xy] = D[xv] + D[vy];  // rilassamento
				}
			}
		}
	}

    return D;
}

}  // namespace asd


#endif /* _CAMMINIMINIMI_H */



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
