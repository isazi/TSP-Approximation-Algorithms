/******************************************************************************\
*
* File:          TSPWriter.h
* Creation date: July 9, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef TSPWRITER_H_
#define TSPWRITER_H_

#include <tsp/TSPInstance.h>
#include <grafo/GrafoNonOrientatoBetaMetrico.h>
#include <fstream>
#include <string>

namespace asd {

template< class T  = int > class TSPWriter {
public:
	/* Costruttore di default */
	TSPWriter(TSPInstance< T > *problema);
	/* Distruttore di default */
	~TSPWriter();

	/* Imposta il file su cui scrivere l'istanza */
	void setOutputFile(std::string outfile );
	/* Restituisce il file su cui scrivere l'istanza */
	inline std::string getOutputFile() const;

	/* Scrive l'istanza su file */
	bool write();

private:
	TSPInstance< T > *problema;
	std::string outfile;
};

template< class T > TSPWriter< T >::TSPWriter(TSPInstance< T > *problema) {
	this->problema = problema;
}

template< class T > TSPWriter< T >::~TSPWriter() {}

template< class T > void TSPWriter< T >::setOutputFile(std::string outfile) {
	this->outfile = outfile;
}

template< class T > inline std::string TSPWriter< T >::getOutputFile() const {
	return this->outfile;
}

template< class T > bool TSPWriter< T >::write() {
	GrafoNonOrientatoBetaMetrico< T > *grafo = problema->getGrafo();
	std::ofstream output(this->outfile.c_str(), std::ios_base::out|std::ios_base::trunc);

	if ( ! output.is_open() ) {
		return false;
	}

	output << "NAME : " << this->outfile << std::endl;
	output << "TYPE : " << problema->getProblemType() <<  std::endl;
	output << "DIMENSION : " << grafo->numVertici() << std::endl;
	output << "EDGE_WEIGHT_TYPE : " << problema->getEdgeWType() << std::endl;
	output << "EDGE_WEIGHT_FORMAT : " << problema->getEdgeWFormat() << std::endl;
	output << "EDGE_WEIGHT_SECTION" << std::endl;

	for ( typename asd::Grafo< T >::vertice_iterator x = grafo->lista_vertici.begin(); x != --(grafo->lista_vertici.end()); x++ ) {
		typename asd::Grafo< T >::vertice_iterator temp = x;
		for ( typename asd::Grafo< T >::vertice_iterator y = ++temp; y != grafo->lista_vertici.end(); y++ ) {
			output << grafo->getPesoArcoCompreso(*x, *y) << " ";
		}
		output << std::endl;
	}

	output << "EOF";
	output.close();

	return true;
}

} // namespace asd

#endif /* TSPWRITER_H_ */

/******************************************************************************\
 * Copyright (C) 2008 Alessio Sclocco

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
