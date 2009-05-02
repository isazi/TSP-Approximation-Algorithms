/*
 * SpaceGenerator.cpp
 *
 *  Created on: Mar 2, 2009
 *      Author: isazi
 */

#include <arcoTipo.h>
#include <Space.h>
#include <Point.h>
#include <grafo/GrafoNonOrientatoBetaMetrico_ListaArchi.h>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace asd;
using std::vector;
using std::map;
using std::pair;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;

template< class T > void distribuzionePesi(const Grafo< T > &grafo, map< double, double > *distribuzione);

int main(void) {
	unsigned int nodi = 100;
	double beta = 1.0;
	w_type min = std::numeric_limits< w_type >::max(), max = std::numeric_limits< w_type >::min();
	vector< Point * > punti;
	map< vertice *, Point * > verticeToPoint;
	map< double, double > *distribuzione = new map< double, double >();
	Space< w_type > spazio;
	GrafoNonOrientatoBetaMetrico_ListaArchi< w_type > grafo;

	srand(time(NULL));

	for ( unsigned int i(0); i < nodi; i++ ) {
		vertice *temp = grafo.aggiungiVertice();
		temp->setKey(i);
		punti.push_back(spazio.addPoint(static_cast< w_type >(rand() % nodi), static_cast< w_type >(rand() % nodi)));
		verticeToPoint[temp] = punti.back();
	}

	for ( Grafo< w_type >::vertice_iterator v = grafo.lista_vertici.begin(); v != --(grafo.lista_vertici.end()); v++ ) {
		Grafo< w_type >::vertice_iterator temp = v;
		for ( Grafo< w_type >::vertice_iterator u = ++temp; u != grafo.lista_vertici.end(); u++ ) {
			arco< w_type > *temp = grafo.aggiungiArco(*v, *u, static_cast< w_type >(spazio.l1Distance(verticeToPoint[*v], verticeToPoint[*u])));
			if ( temp->costo < min ) {
				min = temp->costo;
			}
			if ( temp->costo > max ) {
				max = temp->costo;
			}
		}
	}

	grafo.setBeta(beta);
	/*grafo.generaRandom(nodi);*/

	if ( grafo.verifyBetaMetric() ) {
		cout << "Il grafo è " << beta << "-metrico." << endl;
	}
	else {
		cout << "Il grafo non è " << beta << "-metrico." << endl;
	}
	cout << "Il peso minimo di un arco e' " << min << ", il peso massimo " << max << "." << endl;

	distribuzionePesi(grafo, distribuzione);

	cout << endl;
	for ( map< double, double >::iterator i = (distribuzione->begin())++; i != --(distribuzione->end()); i++ ) {
		cout << fixed << setprecision (2) << "Da " << (*(--i)).first << " a " << (*(++i)).first << ": " << (*i).second << "%" << endl;
	}
	cout << endl;

	return 0;
}

template< class T > void distribuzionePesi(const Grafo< T > &grafo, map< double, double > *distribuzione) {
	unsigned int k = 10;
	double dimBlocco = 0;
	map< double, unsigned int > occorrenze;
	T min = std::numeric_limits< T >::max(), max = std::numeric_limits< T >::min();

	for ( typename Grafo< T >::arco_const_iterator e = grafo.lista_archi.begin(); e != grafo.lista_archi.end(); e++ ) {
		if ( (*e)->costo < min ) {
			min = (*e)->costo;
		}

		if ( (*e)->costo > max ) {
			max = (*e)->costo;
		}
	}

	dimBlocco = (max - min) / static_cast< double >(k);

	for ( unsigned int i(0); i <= k; i++ ) {
		occorrenze.insert(pair< double, unsigned int >(min + (i * dimBlocco), 0));
	}

	for ( typename Grafo< T >::arco_const_iterator e = grafo.lista_archi.begin(); e != grafo.lista_archi.end(); e++ ) {
		for ( unsigned int i(1); i <= k; i++ ) {
			if ( min + (i * dimBlocco) > (*e)->costo ) {
				((occorrenze.find(min + ((i - 1) * dimBlocco)))->second)++;
				break;
			}
		}
	}

	for ( map< double, unsigned int >::iterator i = (occorrenze.begin())++; i != occorrenze.end(); i++ ) {
		distribuzione->insert(pair< double, double >((*i).first, static_cast< double >(((*i).second * 100)) / grafo.numArchi()));
	}
}
