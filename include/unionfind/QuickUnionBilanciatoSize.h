/******************************************************************************\
*
* File:          QuickUnionBilanciatoSize.h
* Creation date: September 16, 2005
* Author:        Francesco Iovine
*
* Purpose:       Fig.9.12
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef _QUICKUNIONBILANCIATOSIZE_H
#define _QUICKUNIONBILANCIATOSIZE_H

#include <unionfind/UnionFind.h>

#include <list>
#include <cassert>


#define for_each_nodoQUBS(v)                               \
        v = *(lista_nodi.begin());                         \
        for (nodoQUBS_iterator it = lista_nodi.begin();    \
             it != lista_nodi.end();                       \
             ++it, v = *it)


namespace asd {

template<class Elem>
class QuickUnionBilanciatoSize;

/*
Nodo di una struttura QuickUnionBilanciatoSize (QUBS).
*/
template<class Elem>
class nodoQUBS
{
  private:
    Elem elem;
    nodoQUBS* padre;
    unsigned size;

  public:
    nodoQUBS(Elem elem_ = Elem(), nodoQUBS<Elem>* padre_ = 0)
        : elem(elem_)
        , padre(padre_)
        , size(1)
    {}

    nodoQUBS(const nodoQUBS<Elem>& n)
        : elem(n.elem)
        , padre(n.padre)
        , size(n.size)
    {}

    ~nodoQUBS()
    {}

    inline Elem getElem() const { return elem; }

  friend class QuickUnionBilanciatoSize<Elem>;
};



/*
Figura 9.12
Realizzazione delle operazioni makeSet, union e find
mediante alberi QuickUnion bilanciati in cardinalita'.
*/
template<class Elem>
class QuickUnionBilanciatoSize
    : public UnionFind<Elem>
{
  private:  // dati
    unsigned setCount;
    std::list< nodoQUBS<Elem>* > lista_nodi;

  public:  // operazioni
    QuickUnionBilanciatoSize();
    ~QuickUnionBilanciatoSize();

    nodoQUBS<Elem>* makeSet(const Elem& e);
    void union_(nodoQUBS<Elem>* a, nodoQUBS<Elem>* b);
    nodoQUBS<Elem>* find(nodoQUBS<Elem>* v) const;

    unsigned getSetCount() const;
    bool isEmpty() const;

  private:  // typedefs
    typedef typename std::list< nodoQUBS<Elem>* >::iterator nodoQUBS_iterator;
};



/* PUBLIC */

/*
Costruttore di default.
*/
template<class Elem>
QuickUnionBilanciatoSize<Elem>::QuickUnionBilanciatoSize()
    : setCount(0)
{}



/*
Distruttore.
*/
template<class Elem>
QuickUnionBilanciatoSize<Elem>::~QuickUnionBilanciatoSize()
{
    nodoQUBS<Elem>* n;
    for_each_nodoQUBS(n) delete n;
}



/*
Crea un nuovo insieme, contenente un nuovo elemento 'e'.
Il nome dell'insieme e' l'indirizzo in cui e' memorizzata la radice dell'albero.
*/
template<class Elem>
nodoQUBS<Elem>* QuickUnionBilanciatoSize<Elem>::makeSet(const Elem& e)
{
    /* Crea un nuovo albero, composto da un unico nodo x.
       Memorizza 'e' in tale nodo, come valore.
       Il nome del nodo e' l'indirizzo di memoria in cui esso risiede.
       Inizializza size(x) = q (la cardinalita' del nuovo albero e' 1),
       memorizzando nel nodo x anche tale valore di size. */

    nodoQUBS<Elem>* x = new nodoQUBS<Elem>(e);

    lista_nodi.push_back(x);
    ++setCount;

    return x;
}



/*
Unisce due radici in un unico insieme.
*/
template<class Elem>
void QuickUnionBilanciatoSize<Elem>::union_(nodoQUBS<Elem>* a,
                                            nodoQUBS<Elem>* b)
{
    /* Considera l'albero A corrispondente all'insieme di nome 'a',
       e l'albero B corrispondente all'insieme di nome 'b'. */
    assert(a != b);

    /* Confronta rank(A) e rank(B), distinguendo tre casi: */
    if (b->size < a->size) {  // caso 1
        b->padre = a;
        a->size += b->size;
    }
    else if (a->size < b->size) {  // caso 2
        a->padre = b;
        b->size += a->size;
    }
    else /* if (a->size == b->size) */ {  // caso 3
        b->padre = a;
        a->size += b->size;
    }

    --setCount;
}



/*
Dato un elemento, restituisce il nome dell'insieme che lo contiene.
*/
template<class Elem>
nodoQUBS<Elem>* QuickUnionBilanciatoSize<Elem>::find(nodoQUBS<Elem>* v) const
{
    /* Accede al nodo x corrispondente all'elemento 'e'.
       Partendo da tale nodo, segue ripetutamente il puntatore al padre
       fino a raggiungere la radice dell'albero. */
    nodoQUBS<Elem>* x = v;
    while (x->padre != 0) { x = x->padre; }

    /* Restituisce il nome memorizzato in tale radice,
       ovvero l'indirizzo di memoria del nodo */
    return x;
}



/*
Restituisce il numero di insiemi nella struttura UnionFind.
*/
template<class Elem>
unsigned QuickUnionBilanciatoSize<Elem>::getSetCount() const
{
    return setCount;
}



/*
Verifica in tempo costante se una struttura UnionFind e' vuota.
*/
template<class Elem>
bool QuickUnionBilanciatoSize<Elem>::isEmpty() const
{
    return (setCount == 0);
}

}  // namespace asd


#endif /* _QUICKUNIONBILANCIATOSIZE_H */



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
