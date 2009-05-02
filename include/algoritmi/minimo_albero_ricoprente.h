/******************************************************************************\
*
* File:          minimo_albero_ricoprente.h
* Creation date: September 16, 2005
* Author:        Francesco Iovine
*
* Purpose:       Fig.12.4, Fig.12.7
*
* License:       See the end of this file for license information
*
* Modifications:
*   1)  Modificato per compatibilita' con la nuova struttura dati Grafo.
*       April 20, 2006. Francesco Iovine && Massimiliano Macchia
*   2)  Modificato per compatibilita' con i nuovi grafici parametrici.
*   	September 5, 2008. Alessio Sclocco
*
\******************************************************************************/

#ifndef _MINIMOALBERORICOPRENTE_H
#define _MINIMOALBERORICOPRENTE_H

#include <grafo/Grafo.h>
#include <albero/Albero.h>
#include <albero/AlberoNonRadicato.h>
#include <codapriorita/HeapFibonacci.h>
#include <unionfind/QuickUnionBilanciatoSize.h>

#include <list>


#define for_each_arco_in_ordine_non_decrescente_di_costo(e,archi)    \
        e = *(archi.begin());                                        \
        for (typename asd::Grafo< T >::arco_const_iterator it = archi.begin();     \
             it != archi.end();                                      \
             ++it, e = *it)


namespace asd {

/*
Algoritmi per trovare il minimo albero ricoprente di un grafo non orientato.
*/
template< class T > void Kruskal(const Grafo< T > &G, AlberoNonRadicato< vertice* > &Tree);
template< class T > void Prim(const Grafo< T > &G, Albero< vertice* > &Tree);

/*
Procedure interne.
*/
template< class T > bool confronta_archi(arco< T > *e1, arco< T > *e2) { return(e1->costo < e2->costo); }



/*
ALGORITMI PER TROVARE IL MINIMO ALBERO RICOPRENTE DI UN GRAFO NON ORIENTATO
*/

/*
Figura 12.4
Implementazione dell'algoritmo di Kruskal con strutture dati union-find.
*/
template < class T > void Kruskal(const Grafo< T > &G, AlberoNonRadicato< vertice* > &Tree)
{
    vertice *v, *x, *y;
    arco< T > *e;
    nodoQUBS< vertice* > *Tx, *Ty;
    vertice_array< nodo_nr< vertice* >* > nodi_albero;
    vertice_array< nodoQUBS< vertice* >* > nodi_unionfind;

    QuickUnionBilanciatoSize< vertice* > UF;  // UnionFind UF
    Tree.clear();  // T <- albero vuoto
    std::list< arco< T >* > archi = G.lista_archi;
    archi.sort(confronta_archi); //ordina gli archi di G=(V,E) secondo costi non decrescenti

    for_each_vertice(v,G) {
        nodi_unionfind[v] = UF.makeSet(v);
    }

    for_each_arco_in_ordine_non_decrescente_di_costo(e,archi) {
        x = e->sorg;  y = e->dest;  // e = (x,y)
        Tx = UF.find( nodi_unionfind[x] );
        Ty = UF.find( nodi_unionfind[y] );
        if (Tx != Ty) {
            UF.union_(Tx,Ty);
            /* aggiungi l'arco (x,y) a T */
            if (nodi_albero[x] == 0) nodi_albero[x] = Tree.aggiungiNodo(x);
            if (nodi_albero[y] == 0) nodi_albero[y] = Tree.aggiungiNodo(y);
            Tree.aggiungiArco(nodi_albero[x], nodi_albero[y]);
        }
    }
    // return T
}



/*
Figura 12.7
Algoritmo di Prim implementato con coda con priorita'.
*/
template< class T > void Prim(const Grafo< T > &G, Albero< vertice* > &Tree)
{
    vertice *s, *u, *v;
    T w;
    vertice_array< T > d;
    vertice_array< nodo< vertice* >* > nodi_albero;
    vertice_array< nodo_binomiale< vertice*, T>* > nodi_codapriorita;

    s = (G.lista_vertici).front();  // s = un vertice di G scelto arbitrariamente
    for_each_vertice(v,G) d[v] = INFINITO;

    /* Tree = albero formato da un solo nodo s */
    Tree.clear();
    nodi_albero[s] = Tree.aggiungiNodo(s);

    /* CodaPriorita S */
    HeapFibonacci< vertice*, T > S;
    d[s] = 0;
    nodi_codapriorita[s] = S.insert(s, 0);

    while ( !(S.isEmpty()) ) {
        u = S.deleteMin();
        for_each_vertice_adiacente_a_distanza(v,u,w,G) {  // for each ( arco (u,v) in G ) do
            if (d[v] == INFINITO) {
                nodi_codapriorita[v] = S.insert(v,w);
                d[v] = w;
                nodi_albero[v] = Tree.aggiungiNodo(v, nodi_albero[u]); //rendi u padre di v in T
            }
            else if (w < d[v]) {
                S.decreaseKey(nodi_codapriorita[v], d[v] - w);
                d[v] = w;
                Tree.spostaSottoalbero(nodi_albero[v], nodi_albero[u]); //rendi u nuovo padre di v in T
            }
        }
    }
    // return T
}

}  // namespace asd


#endif /* _MINIMOALBERORICOPRENTE_H */



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
