/******************************************************************************\
*
* File:          TSPReader.h
* Creation date: July 9, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
* Modifications:
* 	1)	Modificata la lettura mediante coordinate per sfruttare la classe
* 		Space< T >.
* 		March 4, 2009. Alessio Sclocco
*
\******************************************************************************/

#ifndef TSPREADER_H_
#define TSPREADER_H_

#include <tsp/TSPInstance.h>
#include <grafo/GrafoNonOrientatoBetaMetrico_ListaArchi.h>
#include <Space.h>
#include <fstream>
#include <string>
#include <map>
#include <cmath>
#include <vector>
#include <cstdlib>

namespace asd {

template< class T = int > class TSPReader {
public:
	/* Costruttore */
	TSPReader(TSPInstance< T > *problema);
	/* Distruttore di default */
	~TSPReader();

	/* Imposta il file da cui leggere l'istanza */
	void setInputFile(std::string infile);

	/* Restituisce il file da cui leggere l'istanza */
	inline std::string getInputFile() const;

	/* Legge l'istanza del problema e l'eventuale tour ottimo */
	bool read();

private:
	bool read_coord(std::ifstream &infile, unsigned int dimension);
	bool read_explicit(std::ifstream &infile, unsigned int dimension);

	TSPInstance< T > *problema;
	std::string infile;
};

template< class T > TSPReader< T >::TSPReader(TSPInstance< T > *problema) {
	this->problema = problema;
}

template< class T > TSPReader< T >::~TSPReader() {}

template< class T > void TSPReader< T >::setInputFile(std::string infile) {
	this->infile = infile;
}

template< class T > inline std::string TSPReader< T >::getInputFile() const {
	return this->infile;
}

template< class T > bool TSPReader< T >::read() {
	unsigned int dimension = 0;
	std::size_t found = std::string::npos;
	std::string buffer, temp;
	std::ifstream infile(this->infile.c_str()), tourfile;

	while ( !infile.eof() &&  infile.good() ) {
		getline(infile, buffer);

		if ( (found = buffer.find("EDGE_WEIGHT_TYPE")) != std::string::npos ) {
			temp = buffer.substr((buffer.find_first_of(':')+2), (buffer.find_last_not_of(' ') - buffer.find_first_of(' ')));
			this->problema->setEdgeWType(temp);
			continue;
		}
		else if ( (found = buffer.find("TYPE")) != std::string::npos ) {
			temp = buffer.substr((buffer.find_first_of(':')+2), (buffer.find_last_not_of(' ') - buffer.find_first_of(' ')));
			this->problema->setProblemType(temp);
			continue;
		}
		else if ( (found = buffer.find("DIMENSION")) != std::string::npos ) {
			temp = buffer.substr((buffer.find_first_of(':')+2), (buffer.find_last_not_of(' ') - buffer.find_first_of(' ')));
			dimension = atoi(temp.c_str());
			continue;
		}
		else if ( (found = buffer.find("EDGE_WEIGHT_FORMAT")) != std::string::npos ) {
			temp = buffer.substr((buffer.find_first_of(':')+2), (buffer.find_last_not_of(' ') - buffer.find_first_of(' ')));
			this->problema->setEdgeWFormat(temp);
			continue;
		}
		else if ( (found = buffer.find("NODE_COORD_SECTION")) != std::string::npos ) {
			if ( ! this->read_coord(infile, dimension) ) {
				infile.close();
				return false;
			}
		}
		else if ( (found = buffer.find("EDGE_WEIGHT_SECTION")) != std::string::npos ) {
			if ( ! this->read_explicit(infile, dimension) ) {
				infile.close();
				return false;
			}
		}
		else {
			continue;
		}
	}

	temp = this->infile;
	found = this->infile.find(".tsp");
	temp.replace(found, 9, ".opt.tour");
	tourfile.open(temp.c_str());

	if ( tourfile.good() ) {
		int nodo;
		std::vector< unsigned int > *tour = new std::vector< unsigned int >();

		do {
			getline(tourfile, temp);
		} while ( temp != "TOUR_SECTION" );

		while ( tourfile.good() && !tourfile.eof() ) {
			tourfile >> nodo;

			if ( nodo != -1 ) {
				tour->push_back(static_cast< unsigned int >(nodo));
			}
		}

		this->problema->setOptTour(*tour);
		tourfile.close();
	}

	infile.close();

	return true;
}

template< class T > bool TSPReader< T >::read_coord(std::ifstream &infile, unsigned int dimension) {
	unsigned int nodo;
	double x, y;
	GrafoNonOrientatoBetaMetrico_ListaArchi< T > *grafo = new GrafoNonOrientatoBetaMetrico_ListaArchi< T >();
	Space< double > piano;
	std::map< vertice *, Point * > verticeToPoint;

	if ( this->problema->getEdgeWType() == "GEO" ) {
		return false;
	}

	for ( unsigned int i(0); i < dimension; i++ ) {
		infile >> nodo;
		infile >> x;
		infile >> y;

		vertice *temp = grafo->aggiungiVertice();
		temp->setKey(i);
		verticeToPoint[temp] = piano.addPoint(x, y);
	}

	for ( typename asd::Grafo< T >::vertice_iterator v = grafo->lista_vertici.begin(); v != --(grafo->lista_vertici.end()); v++ ) {
		typename asd::Grafo< T >::vertice_iterator temp = v;
		for ( typename asd::Grafo< T >::vertice_iterator u = ++temp; u != grafo->lista_vertici.end(); u++ ) {
			if ( this->problema->getEdgeWType() == "EUC_2D" ) {
				grafo->aggiungiArco(*v, *u, static_cast< T >(piano.l2Distance(verticeToPoint[*v], verticeToPoint[*u])));
			}
			else if ( this->problema->getEdgeWType() == "CEIL_2D" ) {
				grafo->aggiungiArco(*v, *u, static_cast< T >(ceil(piano.l2Distance(verticeToPoint[*v], verticeToPoint[*u]))));
			}
			else {
				return false;
			}
		}
	}

	this->problema->setGrafo(grafo);
	return true;
}

template< class T > bool TSPReader< T >::read_explicit(std::ifstream &infile, unsigned int dimension) {
	int peso;
	GrafoNonOrientatoBetaMetrico_ListaArchi< T > *grafo = new GrafoNonOrientatoBetaMetrico_ListaArchi< T >();

	for ( unsigned int i(0); i < dimension; i++ ) {
		(grafo->aggiungiVertice())->setKey(i);
	}

	if ( this->problema->getEdgeWFormat() == "FULL_MATRIX" ) {
		for ( typename asd::Grafo< T >::vertice_iterator v = grafo->lista_vertici.begin(); v != --(grafo->lista_vertici.end()); v++ ) {
			for ( typename asd::Grafo< T >::vertice_iterator u = grafo->lista_vertici.begin(); u != grafo->lista_vertici.end(); u++ ) {
				infile >> peso;
				if ( *u <= *v ) {
					continue;
				}
				else {
					grafo->aggiungiArco(*v, *u, static_cast< T >(peso));
				}
			}
		}
	}
	else if ( this->problema->getEdgeWFormat() == "UPPER_ROW" ) {
		for ( typename asd::Grafo< T >::vertice_iterator v = grafo->lista_vertici.begin(); v != --(grafo->lista_vertici.end()); v++ ) {
			typename asd::Grafo< T >::vertice_iterator temp = v;
			for ( typename asd::Grafo< T >::vertice_iterator u = ++temp; u != grafo->lista_vertici.end(); u++ ) {
				infile >> peso;
				grafo->aggiungiArco(*v, *u, static_cast< T >(peso));
			}
		}
	}
	else if ( this->problema->getEdgeWFormat() == "UPPER_DIAG_ROW" ) {
		for ( typename asd::Grafo< T >::vertice_iterator v = grafo->lista_vertici.begin(); v != --(grafo->lista_vertici.end()); v++ ) {
			for ( typename asd::Grafo< T >::vertice_iterator u = v; u != grafo->lista_vertici.end(); u++ ) {
				infile >> peso;
				if ( *u == *v ) {
					continue;
				}
				else {
					grafo->aggiungiArco(*v, *u, static_cast< T >(peso));
				}
			}
		}
	}
	else if ( this->problema->getEdgeWFormat() == "LOWER_DIAG_ROW" ) {
		for ( typename asd::Grafo< T >::vertice_iterator v = grafo->lista_vertici.begin(); v != --(grafo->lista_vertici.end()); v++ ) {
			for ( typename asd::Grafo< T >::vertice_iterator u = grafo->lista_vertici.begin(); *u <= *v; u++ ) {
				infile >> peso;
				if ( *u == *v ) {
					continue;
				}
				else {
					grafo->aggiungiArco(*v, *u, static_cast< T >(peso));
				}
			}
		}
	}
	else {
		return false;
	}

	this->problema->setGrafo(grafo);
	return true;
}

} // namespace asd

#endif /* TSPREADER_H_ */

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
