/******************************************************************************\
*
* File:          Grafo.h
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
* 	2) Modificata la classe vertice per rendere piu' agevole la stampa di questi.
* 	   September 8, 2008. Alessio Sclocco
* 	3) Aggiunti il metodo virtuale getArcoCompreso ed i metodi getPesoArcoCompreso
* 	   e getPesoArco alla classe Grafo.
* 	   October 26, 2008. Alessio Sclocco
* 	4) Aggiunto il metodo virtuale sonoArchiAdiacenti alla classe Grafo.
* 	   January 15, 2009. Alessio Sclocco
*
\******************************************************************************/

#ifndef _GRAFO_H
#define _GRAFO_H

#include <ext/hash_map>
#include <list>
#include <vector>
#include <limits>
#include <cstdlib>
#include <cassert>


#define INFINITO std::numeric_limits< T >::max()

#define for_each_vertice(v,G)                                                        \
        v = *((G.lista_vertici).begin());                                            \
        if(G.numVertici())                                                           \
        for ( typename asd::Grafo< T >::vertice_const_iterator it = (G.lista_vertici).begin(); \
             it != (G.lista_vertici).end();                                          \
             ++it, v = *it)

#define for_each_rev_vertice(v,G)                                                    \
        v = *((G.lista_vertici).rbegin());                                           \
        if(G.numVertici())                                                           \
        for ( typename asd::Grafo< T >::vertice_const_rev_iterator it = (G.lista_vertici).rbegin(); \
             it != (G.lista_vertici).rend();                                         \
             ++it, v = *it)

#define for_each_arco(e,G)                                                           \
        e = *((G.lista_archi).begin());                                              \
        if(G.numArchi())                                                             \
        for ( typename asd::Grafo< T >::arco_const_iterator it = (G.lista_archi).begin();           \
             it != (G.lista_archi).end();                                            \
             ++it, e = *it)

#define for_each_rev_arco(e,G)                                                       \
        e = *((G.lista_archi).rbegin());                                             \
        if(G.numArchi())                                                             \
        for ( typename asd::Grafo< T >::arco_const_rev_iterator it = (G.lista_archi).rbegin();      \
             it != (G.lista_archi).rend();                                           \
             ++it, e = *it)

#define for_each_vertice_adiacente(v,u,G)                                            \
        std::vector< vertice* > __vettore__;                                           \
        G.verticiAdiacenti(u,__vettore__);                                           \
        if(__vettore__.size()) v = *(__vettore__.begin());                           \
        for( std::vector< vertice* >::const_iterator it = __vettore__.begin();          \
            it != __vettore__.end();                                                 \
            ++it, v=*it)

#define for_each_rev_vertice_adiacente(v,u,G)                                        \
        std::vector< vertice* > __vettore__;                                           \
        G.verticiAdiacenti(u,__vettore__);                                           \
        if(__vettore__.size()) v=*(__vettore__.rbegin());                            \
        for(std::vector< vertice* >::const_reverse_iterator it = __vettore__.rbegin(); \
            it != __vettore__.rend();                                                \
            ++it, v=*it)

#define for_each_arco_incidente(e,f,G)                                               \
        typename std::vector< arco< T >* > __vettore__;                                              \
        G.verticiAdiacenti(f,__vettore__);                                           \
        if(__vettore__.size()) e=*(__vettore__.begin());                             \
        for( typename std::vector< arco< T >* >::const_iterator it = __vettore__.begin();             \
            it!=__vettore__.end();                                                   \
            ++it, e=*it)

#define for_each_rev_arco_incidente(e,f,G)                                           \
        typename std::vector< arco< T >* > __vettore__;                                              \
        G.verticiAdiacenti(f,__vettore__);                                           \
        if(__vettore__.size()) e=*(__vettore__.rbegin());                            \
        for( typename std::vector< arco< T >* >::const_reverse_iterator it = __vettore__.rbegin();    \
            it!=__vettore__.rend();                                                  \
            ++it, e=*it)

#define for_each_vertice_adiacente_a_distanza(v,u,w,G)                               \
        typename std::vector< adiacente< T > > __vettore__;                                          \
        G.verticiAdiacenti(u,__vettore__);                                           \
        if(__vettore__.size()) {                                                     \
            v=(*(__vettore__.begin())).vertex;                                       \
            w=(*(__vettore__.begin())).costo;                                        \
        }                                                                            \
        for( typename std::vector< adiacente< T > >::const_iterator it = __vettore__.begin();         \
            it!=__vettore__.end();                                                   \
			++it, v=(*it).vertex, w=(*it).costo)

#define for_each_rev_vertice_adiacente_a_distanza(v,u,w,G)                           \
        typename std::vector< adiacente< T > > __vettore__;                                          \
        G.verticiAdiacenti(u,__vettore__);                                           \
        if(__vettore__.size()) {                                                     \
            v=(*(__vettore__.rbegin())).vertex;                                      \
            w=(*(__vettore__.rbegin())).costo;                                       \
        }                                                                            \
        for( typename std::vector< adiacente< T > >::const_reverse_iterator it = __vettore__.rbegin();\
            it!=__vettore__.rend();                                                  \
            ++it, v=(*it).vertex, w=(*it).costo)



namespace asd {




class vertice;
template<class T> class arco;
template<class T> class hash_v;
template<class T> class vertice_array;
template<class T> class arco_array;
template<class T> class adiacente;
template<class T> class Grafo;



/*
Vertice di un grafo
*/
class vertice
{
    public:
        vertice()
        {}

        ~vertice()
        {}

        /* Metodo per impostare la chiave di un vertice */
        void setKey(unsigned int key);
        /* Metodo per recuperare la chiave di un vertice */
        unsigned int getKey();

    private:
    	unsigned int key;
};

void vertice::setKey(unsigned int key) {
	this->key = key;
}

unsigned int vertice::getKey() {
	return this->key;
}


/*
Arco di un grafo
*/
template<class T> class arco
{
    public:
        vertice* sorg;
        vertice* dest;
        T costo;

    public:
        arco(vertice* a = 0, vertice* b = 0, T costo = static_cast<T>(0))
            : sorg(a),
              dest(b),
              costo(costo)
        {}

        ~arco()
        {}

        vertice* opposto(vertice* v)
        {
            if(v == sorg) return dest;
            return sorg;
        }

        bool incideSu(vertice* v)
        {
            if(v==sorg || v==dest) return true;
            return false;
        }
};



template<class T> class hash_v: std::unary_function<vertice*,long>
{
	public: long operator()(vertice* x) const
	{
		return (long)x;
	}

	public: long operator()(arco<T>* x) const
	{
        return (long)x;
    }
};



/*
Contenitore associativo per vertici.
*/
template<class T>
class vertice_array
    : public __gnu_cxx::hash_map< vertice*, T, hash_v< T > >
{
  public:
    vertice_array()
        : __gnu_cxx::hash_map< vertice*, T, hash_v< T > >()
    {}

    ~vertice_array()
    {}
};



/*
Contenitore associativo per archi.
*/
template<class T>
class arco_array
    : public __gnu_cxx::hash_map< arco<T>*, T, hash_v<T> >
{
  public:
    arco_array()
        : __gnu_cxx::hash_map< arco<T>*, T, hash_v<T> >()
    {}

    ~arco_array()
    {}
};



template<class T> class adiacente
{
    public:
        vertice* vertex;
        T costo;

        adiacente(vertice* vert = 0, T c = static_cast<T>(0))
            : vertex(vert),
              costo(c)
        {}

        ~adiacente()
        {}
};



/*
Classe astratta che definisce una versione generica di grafo.
*/
template<class T> class Grafo
{
  protected:  // dati protected
    unsigned vertexCount;
    unsigned edgeCount;

  public:  // dati public
    std::list< vertice * > lista_vertici;
    std::list< arco<T> * > lista_archi;

  // metodi definiti
  public:  // operazioni
    Grafo();
    virtual ~Grafo();

    unsigned numVertici() const;
    unsigned numArchi() const;

    vertice* estremi(arco<T>* e) const;
    vertice* opposto(vertice* x, arco<T>* e) const;
    vertice* aggiungiVertice();
    arco<T>* aggiungiArco(vertice* x, vertice* y, T costo);
    void rimuoviVertice(vertice* v);
    void rimuoviArco(arco<T>* e);
    void clear();
    void genera_random(unsigned n, unsigned m, T costo_max, bool loopfree = false);

    T getPesoArcoCompreso(vertice *x, vertice *y) const;
    T getPesoArco(arco< T > *e) const;

  // metodi virtuali
  public:
    virtual unsigned grado(vertice* v) const;
    virtual void archiIncidenti(vertice* v, std::vector<arco<T>*> &vec) const;

  // metodi virtuali puri
  public:
    virtual void inserisciVertice(vertice* v) = 0;
    virtual void inserisciArco(arco<T>* e) = 0;
    virtual void eliminaVertice(vertice* v) = 0;
    virtual void eliminaArco(arco<T>* e) = 0;
    virtual void reset() = 0;
    virtual bool sonoAdiacenti(vertice* x, vertice* y) const = 0;
    virtual bool sonoArchiAdiacenti(arco< T > *e, arco< T > *l) const = 0;
    virtual bool diretto() const = 0;
    virtual void verticiAdiacenti(vertice* v, std::vector< vertice* > &vec) const = 0;
    virtual void verticiAdiacenti(vertice* v, std::vector< adiacente< T > > &vec) const = 0;
    virtual arco< T > *getArcoCompreso(vertice *x, vertice *y) const = 0;

  public:  // typedefs
    typedef std::list< vertice* >::iterator vertice_iterator;
    typedef std::list< vertice* >::const_iterator vertice_const_iterator;
    typedef std::list< vertice* >::reverse_iterator vertice_rev_iterator;
    typedef std::list< vertice* >::const_reverse_iterator vertice_const_rev_iterator;
    typedef typename std::list< arco< T > * >::iterator arco_iterator;
    typedef typename std::list< arco< T > * >::const_iterator arco_const_iterator;
    typedef typename std::list< arco< T > * >::reverse_iterator arco_rev_iterator;
    typedef typename std::list< arco< T > * >::const_reverse_iterator arco_const_rev_iterator;
};



/* PUBLIC */

/*
Costruttore.
*/
template<class T> Grafo<T>::Grafo()
    : vertexCount(0)
    , edgeCount(0)
{

}



/*
Distruttore.
*/
template<class T> Grafo<T>::~Grafo()
{
    vertice* v;
    for_each_vertice(v,(*this)) delete v;

    arco< T > *e;
    for_each_arco(e,(*this)) delete e;
}



/*
Restituisce il numero di vertici presenti nel grafo.
*/
template<class T> unsigned Grafo<T>::numVertici() const
{
    return vertexCount;
}



/*
Restituisce il numero di archi presenti nel grafo.
*/
template<class T> unsigned Grafo<T>::numArchi() const
{
    return edgeCount;
}



/*
Restituisce gli estremi x e y dell'arco e = (x, y).
*/
template<class T> vertice* Grafo<T>::estremi(arco<T>* e) const
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
Restituisce y, l'estremo dell'arco e = (x, y) diverso da x.
*/
template<class T> vertice* Grafo<T>::opposto(vertice* x, arco<T>* e) const
{
    if (e->dest != x) return e->dest;
    else return e->sorg;
}




/*
Inserisce un nuovo vertice v.
*/
template<class T> vertice* Grafo<T>::aggiungiVertice()
{
    vertice* v = new vertice();

    inserisciVertice(v);
    lista_vertici.push_back(v);
    ++vertexCount;

    return v;
}



/*
Inserisce un nuovo arco tra i vertici x e y.
*/
template<class T> arco<T>* Grafo<T>::aggiungiArco(vertice* x, vertice* y, T costo = static_cast<T>(1))
{
    arco<T>* e = new arco<T>(x, y, costo);

	lista_archi.push_back(e);
    inserisciArco(e);

    ++edgeCount;

    return e;
}



/*
Rimuove il vertice v dal grafo.
*/
template<class T> void Grafo<T>::rimuoviVertice(vertice* v)
{
    eliminaVertice(v);

    typename asd::Grafo< T >::arco_iterator i, j;

    for (i = lista_archi.begin(); i != lista_archi.end(); )
    {
        if ((*i)->sorg == v || (*i)->dest == v)
        {
            j = i;
            ++j;
            delete *i;
            lista_archi.erase(i);
            --edgeCount;
            i = j;
        }
        else ++i;
    }

    typename asd::Grafo< T >::vertice_iterator k;
	for (k = lista_vertici.begin(); *k != v; ++k) ;
    lista_vertici.erase(k);
    delete v;

    --vertexCount;
}



/*
Rimuove l'arco e dal grafo.
*/
template<class T> void Grafo<T>::rimuoviArco(arco<T>* e)
{
    eliminaArco(e);

    typename asd::Grafo< T >::arco_iterator i;

    for (i = lista_archi.begin(); *i != e; ++i) ;
    lista_archi.erase(i);
    delete e;

    --edgeCount;
}



/*
Elimina tutti i vertici e tutti gli archi, rendendo il grafo vuoto.
*/
template<class T> void Grafo<T>::clear()
{
    vertice* v;
    for_each_vertice(v,(*this)) delete(v);

    arco< T > *e;
    for_each_arco(e,(*this)) delete(e);

    reset();

    lista_vertici.clear();
    lista_archi.clear();

    vertexCount = 0;
    edgeCount = 0;
}



/*
Genera casualmente il grafo, con n vertici, m archi,
il cui costo e' nell'intervallo [1, costo_max].
La variabile booleana 'loopfree' si riferisce
alla presenza(false) o no(true) di self-loops.
*/
template<class T> void Grafo<T>::genera_random(unsigned n, unsigned m, T costo_max, bool loopfree)
{
    assert( !( n == 0 && m > 0 ) );
    assert( !( n == 1 && m > 0 && loopfree ) );

    std::vector<vertice*> V(n);
    std::vector<int> deg(n);
    unsigned i, j;
    int d;

    clear();

    for (i = 0; i < n; ++i) {
        V[i] = aggiungiVertice();
        deg[i] = 0;
    }
    for (i = 0; i < m; i++) {
        deg[rand() % n]++;
    }
    for (i = 0; i < n; i++) {
        vertice* v = V[i];
        d = deg[i];
        while ( d > 0 ) {
            j = rand() % n;
            if ( loopfree && j == i ) continue;
            aggiungiArco(v, V[j], static_cast< T >(1 + (rand() % costo_max)));
            d--;
        }
    }
}

template< class T > T Grafo< T >::getPesoArcoCompreso(vertice *x, vertice *y) const {
	return this->getPesoArco(this->getArcoCompreso(x, y));
}

template< class T > inline T Grafo< T >::getPesoArco(arco< T > *l) const {
	if ( l != 0 ) {
		return l->costo;
	}
	else {
		return INFINITO;
	}
}

/*
Restituisce il grado del vertice v
*/
template<class T> unsigned Grafo<T>::grado(vertice* v) const
{
    unsigned g = 0;

    arco<T>* e;
    for_each_arco(e,(*this))
      if(e->incideSu(v))
        ++g;

    return g;
}



/*
Riempie il vector vec con gli archi incidenti a v.
*/
template<class T> void Grafo<T>::archiIncidenti(vertice* v, std::vector<arco<T>*> &vec) const
{
    arco<T>* e;
    for_each_arco(e,(*this))
      if(e->incideSu(v))
        vec.push_back(e);
}




}  // namespace asd


#endif /* _GRAFO_H */



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
