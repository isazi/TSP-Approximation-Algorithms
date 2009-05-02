/******************************************************************************\
*
* File:          tsp_approssimato.h
* Creation date: September 5, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef TSP_APPROSSIMATO_H_
#define TSP_APPROSSIMATO_H_

#include <albero/Albero.h>
#include <algoritmi/matching.h>
#include <algoritmi/minimo_albero_ricoprente.h>
#include <algoritmi/visita_Albero.h>
#include <algoritmi/cammino_euleriano.h>
#include <algoritmi/copertura_cicli.h>
#include <algoritmi/common.h>
#include <grafo/GrafoNonOrientatoBetaMetrico.h>
#include <grafo/GrafoNonOrientato_ListaArchi.h>
#include <Coda.h>
#include <Pila.h>

#include <vector>
#include <map>

namespace asd {

/* Algoritmi approssimati per la risoluzione del TSP */

template< class T > void doubleMST(const GrafoNonOrientatoBetaMetrico< T > *grafo, std::vector< vertice* > *sol, bool refined = false);
template< class T > void christofides(const GrafoNonOrientatoBetaMetrico< T > *grafo, std::vector< vertice* > *sol);
template< class T > void cycleCover(const GrafoNonOrientatoBetaMetrico< T > *grafo, std::vector< vertice* > *sol);

/* Funzioni accessorie e di uso interno */

template< class T > void grafoAusiliario(const GrafoNonOrientatoBetaMetrico< T > &grafo, GrafoNonOrientato< T > *ausiliario, std::map< arco< T > *, std::vector< arco< T > * > * > *e_ausi);

/* Algoritmi Double MST e Refined Double MST */

template< class T > void doubleMST(const GrafoNonOrientatoBetaMetrico< T > *grafo, std::vector< vertice* > *sol, bool refined) {
	Albero< vertice* > tree;

	sol->clear();

	/* Costruzione dell'albero ricoprente di costo minimo del grafo */
	Prim< T >(*grafo, tree);
	/* Visita in profondita' dell'albero ricoprente */
	if ( refined ) {
		visitaDFS< vertice*, T >(tree, sol, true, grafo);
	}
	else {
		visitaDFS< vertice*, T >(tree, sol);
	}
}

/* Algoritmo di Christofides */

template< class T > void christofides(const GrafoNonOrientatoBetaMetrico< T > *grafo, std::vector< vertice* > *sol) {
	unsigned int counter = 0;
	Albero< vertice * > tree;
	/* Grafo composto dai vertici di grado dispari dell'MST */
	GrafoNonOrientato_ListaArchi< T > oddGrafo;
	Coda< nodo< vertice * > * > queue;
	Pila< arco< T > * > *pila = 0;
	nodo< vertice * > *temp;
	/* Mappatura tra i vertici di oddGrafo e quelli di grafo */
	std::map<vertice *, vertice *> vtov;
	std::map< vertice *, bool > *found = 0;
	std::vector< arco< T > * > matching, eulerian, *multigrafo, sacrifice;
	std::vector< vertice * > *newSol = 0;

	sol->clear();

	/* Costruzione dell'albero ricoprente di costo minimo del grafo */
	Prim< T >(*grafo, tree);

	/* Calcolare il matching perfetto di peso minimo del grafo che comprende solo i nodi di grado dispari dell'albero */
	queue.enqueue(tree.padre());

	while ( ! queue.isEmpty() ) {
		unsigned int grado = 0;
		vertice *tempVertice;

		temp = queue.dequeue();

		if ( temp->getChiave() == (tree.padre())->getChiave() ) {
			grado = tree.grado(temp);
		}
		else {
			grado = tree.grado(temp) + 1;
		}

		if ( grado % 2 == 1 ) {
			tempVertice = oddGrafo.aggiungiVertice();
			tempVertice->setKey(counter++);
			vtov[tempVertice] = temp->getChiave();
		}

		for ( nodo< vertice * >::lista_figli_const_iterator v = temp->lista_figli.begin(); v != temp->lista_figli.end(); v++ ) {
			queue.enqueue(*v);
		}
	}

	for ( typename Grafo< T >::vertice_const_iterator v = oddGrafo.lista_vertici.begin(); v != --(oddGrafo.lista_vertici.end()); v++ ) {
		typename Grafo< T >::vertice_const_iterator temp = v;
		for ( typename Grafo< T >::vertice_const_iterator u = ++temp; u != oddGrafo.lista_vertici.end(); u++ ) {
			if ( grafo->getPesoArcoCompreso(vtov[*v], vtov[*u]) != INFINITO ) {
				oddGrafo.aggiungiArco(*v, *u, grafo->getPesoArcoCompreso(vtov[*v], vtov[*u]));
			}
		}
	}

	minCostPerfectMatching(&oddGrafo, &matching);

	/* Mettere assieme gli archi di matching e tree per formare un multigrafo */
	multigrafo = new std::vector< arco< T > * >;
	queue.enqueue(tree.padre());

	while ( ! queue.isEmpty() ) {
		temp = queue.dequeue();

		for ( nodo< vertice * >::lista_figli_const_iterator v = temp->lista_figli.begin(); v != temp->lista_figli.end(); v++ ) {
			multigrafo->push_back(grafo->getArcoCompreso(temp->getChiave(), (*v)->getChiave()));
			queue.enqueue(*v);
		}
	}

	/* Riporto il matching calcolato su oddGrafo nello "spazio" del grafo originale e sposto gli archi nel multigrafo */
	for ( typename std::vector< arco< T > * >::const_iterator exArco = matching.begin(); exArco != matching.end(); exArco++ ) {
		multigrafo->push_back(grafo->getArcoCompreso(vtov[(*exArco)->sorg], vtov[(*exArco)->dest]));
	}

	tree.clear();
	matching.clear();
	oddGrafo.clear();

	/* Calcolare un percorso euleriano sull'ipergrafo creato */
	pila = new Pila< arco< T > * >;
	sacrifice = *multigrafo;
	eulerianCycle((multigrafo->at(0))->sorg, pila, sacrifice);

	while ( ! pila->isEmpty() ) {
		eulerian.push_back(pila->pop());
	}

	delete multigrafo;
	sacrifice.clear();

	/* Calcolare un ciclo hamiltoniano a partire dal percorso euleriano */
	for ( typename std::vector< arco< T > * >::const_iterator e = eulerian.begin(); e < eulerian.end(); e++ ) {
		if ( e == eulerian.begin() ) {
			sol->push_back((*e)->sorg);
			sol->push_back((*e)->dest);
		}
		else {
			if ( sol->at(sol->size()-1) == (*e)->sorg ) {
				sol->push_back((*e)->dest);
			}
			else {
				sol->push_back((*e)->sorg);
			}
		}
	}

	eulerian.clear();

	found = new std::map< vertice *, bool >;
	newSol = new std::vector< vertice * >;

	for ( std::vector< vertice * >::const_iterator v = sol->begin(); v != sol->end(); v++ ) {
		if ( found->find((*v)) == found->end() ) {
			newSol->push_back(*v);
			found->insert(std::pair< vertice *, bool >(*v, true));
		}
	}

	sol->clear();

	*sol = *newSol;
}


/* Algoritmo Cycle Cover */

template< class T > void cycleCover(const GrafoNonOrientatoBetaMetrico< T > *grafo, std::vector< vertice* > *sol) {
	sol->clear();

	/* Costruire il grafo ausiliario e calcolarne il matching perfetto di peso minimo */

	/* Grafo ausiliario */
	GrafoNonOrientato_ListaArchi< T > *ausiliario = new GrafoNonOrientato_ListaArchi< T >;
	/* Rappresentazione del matching come vettore di archi */
	std::vector< arco< T > * > *matching = new std::vector< arco< T > * >;
	/* Mappatura tra gli archi del grafo originario e quelli del grafo ausiliario */
	std::map< arco< T > *, std::vector< arco< T > * > * > *e_ausi = new std::map< arco< T > *, std::vector< arco< T > * > * >;

	grafoAusiliario(*grafo, ausiliario, e_ausi);
	minCostPerfectMatching(ausiliario, matching);

	/* Riportiamo il matching calcolato sul grafo ausiliario nello spazio del grafo originale */

	/* Vettore di archi tra cui evidenziare i cicli */
	std::vector< arco< T > * > *archiDelCiclo = new std::vector< arco< T > * >;

	for ( typename std::map< arco< T > *, std::vector< arco< T > * > * >::const_iterator row = e_ausi->begin(); row != e_ausi->end(); row++ ) {
		unsigned int counter = 0;
		for ( typename std::vector< arco< T > * >::const_iterator e = (*row).second->begin(); e != (*row).second->end(); e++ ) {
			counter += static_cast< unsigned int >(contaOccorrenze(*e, matching));
		}
		if ( counter == 2 ) {
			archiDelCiclo->push_back((*row).first);
		}
	}

	/* matching, e_ausi ed ausiliario non servono piu' */
	delete matching;
	delete e_ausi;
	delete ausiliario;

	/* Costruire una copertura di cicli sul grafo originario */

	/* Matrice che rappresenta i diversi cicli che coprono il grafo originario */
	std::vector< std::vector< arco< T > * > * > *cycles = new std::vector< std::vector< arco< T > * > * >;

	cover(archiDelCiclo, cycles);

	/* Trovare l'arco meno costoso di ogni ciclo, eliminarlo e connettere i suoi estremi ad altri cicli */
	for ( typename std::vector< std::vector< arco< T > * > * >::iterator i = cycles->begin(); i != cycles->end(); i++ ) {
		/* cycleEndPoint rappresenta l'ultimo vertice del ciclo aperto eliminando l'arco di costo minimo */
		vertice *cycleEndPoint = 0;
		/* minArco rappresenta l'arco di peso minimo di un ciclo */
		arco< T > *minArco = 0;
		arco< T > *tempArco = 0;

		for ( typename std::vector< arco< T > * >::iterator e = (*i)->begin(); e != (*i)->end(); e++ ) {
			if ( minArco == 0 || (*e)->costo < minArco->costo ) {
				minArco = *e;
			}
		}

		sol->push_back(minArco->sorg);
		cycleEndPoint = minArco->dest;

		int j;
		while ( (j = findNextArco(*(*i), sol->at(sol->size()-1))) != -1 ) {
			if ( static_cast< unsigned int >(j) != ((*i)->size() - 1) ) {
				tempArco = (*i)->at((*i)->size()-1);
				(*i)->at((*i)->size()-1) = (*i)->at(j);
				(*i)->at(j) = tempArco;
			}
			tempArco = (*i)->at((*i)->size()-1);
			(*i)->pop_back();

			if ( tempArco != minArco ) {
				if ( sol->at(sol->size()-1) == tempArco->sorg ) {
					sol->push_back(tempArco->dest);
				}
				else {
					sol->push_back(tempArco->sorg);
				}
			}
		}
		if ( sol->at(sol->size()-1) != cycleEndPoint ) {
			sol->push_back(cycleEndPoint);
		}
	}
}

/* Funzioni accessorie e di uso interno */

template< class T > void grafoAusiliario(const GrafoNonOrientatoBetaMetrico< T > &grafo, GrafoNonOrientato< T > *ausiliario, std::map< arco< T > *, std::vector< arco< T > * > * > *e_ausi) {
	unsigned int counter = 0;
	std::map< vertice *, std::vector< vertice * > * > *v_ausi = new std::map< vertice *, std::vector< vertice * > * >;
	std::map< arco< T > *, std::vector< vertice *> * > *ausi_e = new std::map< arco< T > *, std::vector< vertice *> * >;

	ausiliario->clear();
	e_ausi->clear();

	for ( typename Grafo< T >::arco_const_iterator e = grafo.lista_archi.begin(); e != grafo.lista_archi.end(); e++ ) {
		vertice *tempVertice;
		std::vector< vertice * > *e_temp = new std::vector< vertice * >;
		typename std::vector< arco< T > * > *temp_e = new std::vector< arco< T > * >;

		if ( v_ausi->find((*e)->sorg) == v_ausi->end() ) {
			std::vector< vertice * > *temp_v = new std::vector< vertice * >;

			for ( unsigned int i(0); i < 2; i++ ) {
				tempVertice = ausiliario->aggiungiVertice();
				tempVertice->setKey(counter++);
				temp_v->push_back(tempVertice);
			}

			v_ausi->insert(std::pair< vertice *, std::vector< vertice * > * >((*e)->sorg, temp_v));
		}

		if ( v_ausi->find((*e)->dest) == v_ausi->end() ) {
			std::vector< vertice * > *temp_v = new std::vector< vertice * >;

			for ( unsigned int i(0); i < 2; i++ ) {
				tempVertice = ausiliario->aggiungiVertice();
				tempVertice->setKey(counter++);
				temp_v->push_back(tempVertice);
			}

			v_ausi->insert(std::pair< vertice *, std::vector< vertice * > * >((*e)->dest, temp_v));
		}

		for ( unsigned int i(0); i < 2; i++ ) {
			tempVertice = ausiliario->aggiungiVertice();
			tempVertice->setKey(counter++);
			e_temp->push_back(tempVertice);
		}

		ausi_e->insert(std::pair< arco< T > *, std::vector< vertice * > * >(*e, e_temp));

		temp_e->push_back(ausiliario->aggiungiArco(&(*(ausi_e->find(*e))->second->at(0)), &(*(ausi_e->find(*e))->second->at(1)), 0));
		temp_e->push_back(ausiliario->aggiungiArco(&(*(ausi_e->find(*e))->second->at(0)), &(*(v_ausi->find((*e)->sorg))->second->at(0)), (*e)->costo));
		temp_e->push_back(ausiliario->aggiungiArco(&(*(ausi_e->find(*e))->second->at(0)), &(*(v_ausi->find((*e)->sorg))->second->at(1)), (*e)->costo));
		temp_e->push_back(ausiliario->aggiungiArco(&(*(ausi_e->find(*e))->second->at(1)), &(*(v_ausi->find((*e)->dest))->second->at(0)), (*e)->costo));
		temp_e->push_back(ausiliario->aggiungiArco(&(*(ausi_e->find(*e))->second->at(1)), &(*(v_ausi->find((*e)->dest))->second->at(1)), (*e)->costo));

		e_ausi->insert(std::pair< arco< T > *, std::vector< arco< T > * > * >(*e, temp_e));
	}
	delete ausi_e;
	delete v_ausi;
}

} // namespace asd

#endif /* TSP_APPROSSIMATO_H_ */

/******************************************************************************\
 * Copyright (C) 2008 Alessio Sclocco <alessio@sclocco.eu>

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
\******************************************************************************/
