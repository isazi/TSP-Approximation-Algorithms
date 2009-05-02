/*
 * spostamentoMetricoTest.cpp
 *
 *  Created on: Feb 19, 2009
 *      Author: isazi
 */

#include <arcoTipo.h>
#include <grafo/GrafoNonOrientatoBetaMetrico_ListaArchi.h>

#include <iostream>
#include <limits>

using namespace asd;
using std::cout;
using std::endl;

int main(void) {
	unsigned int counter = 0;
	int base = 100000;
	w_type min = std::numeric_limits< w_type >::max();
	unsigned int nodi = 300;
	GrafoNonOrientatoBetaMetrico_ListaArchi< w_type > grafo;

	cout << endl;

	grafo.generaFW(nodi);

	cout << "Il grafo è stato generato, troviamo adesso il peso dell'arco di peso minimo." << endl;
	cout << endl;

	for ( Grafo< w_type >::arco_const_iterator e = grafo.lista_archi.begin(); e != grafo.lista_archi.end(); e++ ) {
		if ( (*e)->costo < min ) {
			min = (*e)->costo;
		}
	}

	for ( Grafo< w_type >::arco_const_iterator e = grafo.lista_archi.begin(); e != grafo.lista_archi.end(); e++ ) {
		(*e)->costo = (base * (*e)->costo) / min;
		if ( (*e)->costo > 2 * base ) {
			counter++;
		}
	}

	cout << "Ci sono " << counter << " valori che non rientrano nell'intervallo previsto." << endl;
	cout << endl;

	return 0;
}
