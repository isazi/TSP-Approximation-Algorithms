/*
 * getArcoCompresoTest.cpp
 *
 *  Created on: Jan 27, 2009
 *      Author: Alessio Sclocco <alessio@sclocco.eu>
 */

typedef unsigned int w_type;

#include <grafo/GrafoNonOrientato_ListaArchi.h>

#include <iostream>

using namespace asd;
using std::cout;
using std::endl;

int main(void) {
	w_type counter = 0;
	GrafoNonOrientato_ListaArchi< w_type > grafo;

	for ( unsigned int i(0); i < 3; i++ ) {
		vertice *temp = grafo.aggiungiVertice();
		temp->setKey(i);
	}

	for ( GrafoNonOrientato_ListaArchi< w_type >::vertice_iterator v = grafo.lista_vertici.begin(); v != grafo.lista_vertici.end(); v++ ) {
		GrafoNonOrientato_ListaArchi< w_type >::vertice_iterator temp = v;
		for ( GrafoNonOrientato_ListaArchi< w_type >::vertice_iterator u = ++temp; u != grafo.lista_vertici.end(); u++ ) {
			grafo.aggiungiArco(*v, *u, ++counter);
		}
	}

	for ( GrafoNonOrientato_ListaArchi< w_type >::vertice_const_iterator v = grafo.lista_vertici.begin(); v != grafo.lista_vertici.end(); v++ ) {
		GrafoNonOrientato_ListaArchi< w_type >::vertice_const_iterator temp = v;
		for ( GrafoNonOrientato_ListaArchi< w_type >::vertice_const_iterator u = ++temp; u != grafo.lista_vertici.end(); u++ ) {
			cout << "La distanza tra " << (*v)->getKey() << " e " << (*u)->getKey() << " è: " << grafo.getPesoArcoCompreso(*v, *u) << endl;
		}
	}
	cout << endl;

	for ( GrafoNonOrientato_ListaArchi< w_type >::vertice_const_iterator v = --(grafo.lista_vertici.end()); v != grafo.lista_vertici.begin(); v-- ) {
		GrafoNonOrientato_ListaArchi< w_type >::vertice_const_iterator temp = v;
		for ( GrafoNonOrientato_ListaArchi< w_type >::vertice_const_iterator u = --temp; u != grafo.lista_vertici.begin(); u-- ) {
			cout << "La distanza tra " << (*v)->getKey() << " e " << (*u)->getKey() << " è: " << grafo.getPesoArcoCompreso(*v, *u) << endl;
		}
	}
	cout << endl;

	return 0;
}
