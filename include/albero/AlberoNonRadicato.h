/******************************************************************************\
*
* File:          AlberoNonRadicato.h
* Creation date: September 16, 2005
* Author:        Francesco Iovine
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef _ALBERONONRADICATO_H
#define _ALBERONONRADICATO_H

#include <list>


#define for_each_nodo_nr(v,T)                                           \
        v = *((T.lista_nodi).begin());                                  \
        for (nodo_nr_const_iterator it = (T.lista_nodi).begin();     \
             it != (T.lista_nodi).end();                                \
             ++it, v = *it)

#define for_each_arco_nr(v,T)                                           \
        v = *((T.lista_archi).begin());                                 \
        for (arco_nr_const_iterator it = (T.lista_archi).begin();   \
             it != (T.lista_archi).end();                               \
             ++it, v = *it)

#define for_each_nodo_nr_adiacente(v,u)                                \
        v = *((u->adj_list).begin());                                  \
        for (adj_list_const_iterator it = (u->adj_list).begin();       \
             it != (u->adj_list).end();                                \
             ++it, v = *it)


namespace asd {

/*
Nodo di un albero non radicato rappresentato con liste di adiacenza.
*/
template<class Chiave>
class nodo_nr
{
  private:
    Chiave chiave;

  public:
    std::list< nodo_nr* > adj_list;  // lista di adiacenza

    nodo_nr(const Chiave& chiave_ = Chiave())
        : chiave(chiave_)
    {}

    nodo_nr(const nodo_nr& v)
        : chiave(v.chiave)
        , adj_list(v.adj_list)
    {}

    ~nodo_nr()
    {}

    inline Chiave getChiave() const { return chiave; }

    typedef typename std::list<nodo_nr<Chiave>*>::iterator adj_list_iterator;
    typedef typename std::list<nodo_nr<Chiave>*>::const_iterator adj_list_const_iterator;
    typedef typename std::list<nodo_nr<Chiave>*>::reverse_iterator adj_list_rev_iterator;
    typedef typename std::list<nodo_nr<Chiave>*>::const_reverse_iterator adj_list_const_rev_iterator;
};



/*
Arco di un albero non radicato rappresentato con liste di adiacenza.
*/
template<class Chiave>
class arco_nr
{
  public:
    nodo_nr<Chiave>* sorg;
    nodo_nr<Chiave>* dest;

    arco_nr(nodo_nr<Chiave>* sorg_ = 0, nodo_nr<Chiave>* dest_ = 0)
        : sorg(sorg_)
        , dest(dest_)
    {}

    arco_nr(const arco_nr& e)
        : sorg(e.sorg)
        , dest(e.dest)
    {}

    ~arco_nr()
    {}
};



/*
Rappresentazione di un albero non radicato con liste di adiacenza.
*/
template<class Chiave>
class AlberoNonRadicato
{
  private:  // dati private
    unsigned nodeCount;
    unsigned edgeCount;

  public:  // dati public
    std::list< nodo_nr<Chiave>* > lista_nodi;
    std::list< arco_nr<Chiave>* > lista_archi;

  public:  // operazioni
    AlberoNonRadicato();
    AlberoNonRadicato(const AlberoNonRadicato& T);
    ~AlberoNonRadicato();

    unsigned numNodi() const;
    unsigned numArchi() const;
    unsigned grado(nodo_nr<Chiave>* v) const;
    nodo_nr<Chiave>* estremi(arco_nr<Chiave>* e) const;
    nodo_nr<Chiave>* opposto(nodo_nr<Chiave>* x, arco_nr<Chiave>* e) const;
    bool sonoAdiacenti(nodo_nr<Chiave>* x, nodo_nr<Chiave>* y) const;
    nodo_nr<Chiave>* aggiungiNodo(const Chiave& k);
    arco_nr<Chiave>* aggiungiArco(nodo_nr<Chiave>* x, nodo_nr<Chiave>* y);

    void clear();

  public:  // typedefs
    typedef typename nodo_nr<Chiave>::adj_list_iterator adj_list_iterator;
    typedef typename nodo_nr<Chiave>::adj_list_const_iterator adj_list_const_iterator;
    typedef typename nodo_nr<Chiave>::adj_list_rev_iterator adj_list_rev_iterator;
    typedef typename nodo_nr<Chiave>::adj_list_const_rev_iterator adj_list_const_rev_iterator;
    typedef typename std::list< nodo_nr<Chiave>* >::iterator nodo_nr_iterator;
    typedef typename std::list< nodo_nr<Chiave>* >::const_iterator nodo_nr_const_iterator;
    typedef typename std::list< nodo_nr<Chiave>* >::reverse_iterator nodo_nr_rev_iterator;
    typedef typename std::list< nodo_nr<Chiave>* >::const_reverse_iterator nodo_nr_const_rev_iterator;
    typedef typename std::list< arco_nr<Chiave>* >::iterator arco_nr_iterator;
    typedef typename std::list< arco_nr<Chiave>* >::const_iterator arco_nr_const_iterator;
    typedef typename std::list< arco_nr<Chiave>* >::reverse_iterator arco_nr_rev_iterator;
    typedef typename std::list< arco_nr<Chiave>* >::const_reverse_iterator arco_nr_const_rev_iterator;
};



/* PUBLIC */

/*
Costruttore di default.
*/
template<class Chiave>
AlberoNonRadicato<Chiave>::AlberoNonRadicato()
    : nodeCount(0)
    , edgeCount(0)
{}



/*
Costruttore di copia.
*/
template<class Chiave>
AlberoNonRadicato<Chiave>::AlberoNonRadicato(const AlberoNonRadicato& T)
    : nodeCount(T.nodeCount)
    , edgeCount(T.edgeCount)
    , lista_nodi(T.lista_nodi)
    , lista_archi(T.lista_archi)
{}



/*
Distruttore.
*/
template<class Chiave>
AlberoNonRadicato<Chiave>::~AlberoNonRadicato()
{
    nodo_nr<Chiave>* v;
    for_each_nodo_nr(v,(*this)) delete(v);

    arco_nr<Chiave>* e;
    for_each_arco_nr(e,(*this)) delete(e);
}



/*
Restituisce il numero di nodi presenti nel albero non radicato.
*/
template<class Chiave>
unsigned AlberoNonRadicato<Chiave>::numNodi() const
{
    return nodeCount;
}



/*
Restituisce il numero di archi presenti nel albero non radicato.
*/
template<class Chiave>
unsigned AlberoNonRadicato<Chiave>::numArchi() const
{
    return edgeCount;
}



/*
Restituisce il numero di archi incidenti sul nodo_nr v.
*/
template<class Chiave>
unsigned AlberoNonRadicato<Chiave>::grado(nodo_nr<Chiave>* v) const
{
    return (v->adj_list).size();
}



/*
Restituisce gli estremi x e y dell'arco_nr e = (x, y).
*/
template<class Chiave>
nodo_nr<Chiave>* AlberoNonRadicato<Chiave>::estremi(arco_nr<Chiave>* e) const
{
    static bool prima_chiamata = true;

    if (prima_chiamata) {
        prima_chiamata = false;
        return e->sorg;
    }
    else {
        prima_chiamata = true;
        return e->dest;
    }
}



/*
Restituisce y, l'estremo dell'arco_nr e = (x, y) diverso da x.
*/
template<class Chiave>
nodo_nr<Chiave>* AlberoNonRadicato<Chiave>::opposto(nodo_nr<Chiave>* x, arco_nr<Chiave>* e) const
{
    if (e->dest != x) return e->dest;
    else return e->sorg;
}



/*
Restituisce true se esiste l'arco_nr (x, y), e false altrimenti.
*/
template<class Chiave>
bool AlberoNonRadicato<Chiave>::sonoAdiacenti(nodo_nr<Chiave>* x, nodo_nr<Chiave>* y) const
{
    /* per ogni nodo_nr 'v' adiacente ad 'x' a distanza 'w' */
    nodo_nr<Chiave> *v;
    for_each_nodo_nr_adiacente(v,x) {
        if (v == y) return true;
    }

    return false;
}



/*
Inserisce un nuovo nodo_nr v.
*/
template<class Chiave>
nodo_nr<Chiave>* AlberoNonRadicato<Chiave>::aggiungiNodo(const Chiave& k)
{
    nodo_nr<Chiave>* v = new nodo_nr<Chiave>(k);

    lista_nodi.push_back(v);
    ++nodeCount;

    return v;
}



/*
Inserisce un nuovo arco_nr tra i nodi x e y.
*/
template<class Chiave>
arco_nr<Chiave>* AlberoNonRadicato<Chiave>::aggiungiArco(nodo_nr<Chiave>* x, nodo_nr<Chiave>* y)
{
    arco_nr<Chiave>* e = new arco_nr<Chiave>(x, y);

    (x->adj_list).push_back(y);
    (y->adj_list).push_back(x);

    lista_archi.push_back(e);
    ++edgeCount;

    return e;
}



/*
Elimina tutti i nodi, rendendo l'albero vuoto.
*/
template<class Chiave>
void AlberoNonRadicato<Chiave>::clear()
{
    nodo_nr<Chiave>* v;
    for_each_nodo_nr(v,(*this)) delete(v);

    arco_nr<Chiave>* e;
    for_each_arco_nr(e,(*this)) delete(e);

    lista_nodi.clear();
    lista_archi.clear();

    nodeCount = 0;
    edgeCount = 0;
}

}  // namespace asd


#endif /* _ALBERONONRADICATO_H */



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
