/******************************************************************************\
*
* File:          TSPInstance.h
* Creation date: June 17, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef TSPINSTANCE_H_
#define TSPINSTANCE_H_

#include <grafo/GrafoNonOrientatoBetaMetrico.h>
#include <vector>
#include <string>


namespace asd {

template< class T = int > class TSPInstance {
public:
	/* Costruttore di default */
	TSPInstance();
	/* Distruttore di default */
	~TSPInstance();

	/* Pulisce l'istanza */
	void clear();

	/* Imposta la soluzione ottima */
	void setOptValue(T value);
	/* Restituisce la soluzione ottima */
	inline T getOptValue() const;

	/* Imposta il tour ottimo */
	void setOptTour(std::vector< unsigned int > tour);
	/* Restituisce il tour ottimo */
	std::vector< unsigned int > getOptTour() const;

	/* Imposta il grafo rappresentante l'istanza */
	void setGrafo(GrafoNonOrientatoBetaMetrico< T > *grafo);
	/* Restituisce il grafo rappresentante l'istanza */
	GrafoNonOrientatoBetaMetrico< T > *getGrafo();

	/* Imposta il tipo di problema */
	void setProblemType(std::string type);
	/* Restituisce il tipo di problema */
	inline std::string getProblemType() const;

	/* Imposta il formato del peso degli archi (caso esplicito) */
	void setEdgeWType(std::string type);
	/* Restituisce il tipo del peso degli archi (caso esplicito) */
	inline std::string getEdgeWType() const;

	/* Imposta il formato del peso degli archi (caso implicito) */
	void setEdgeWFormat(std::string format);
	/* Restituisce il formato del peso degli archi (caso implicito) */
	inline std::string getEdgeWFormat() const;

private:
	T optValue;
	std::vector< unsigned int > optTour;
	GrafoNonOrientatoBetaMetrico< T > *grafo;
	std::string pType, eType, eFormat;
};

template< class T > TSPInstance< T >::TSPInstance() {
	this->optValue = INFINITO;
	this->grafo = 0;
	this->pType = "";
	this->eType = "";
	this->eFormat = "";
}

template< class T > TSPInstance< T >::~TSPInstance() {}

template< class T > void TSPInstance< T >::clear() {
	this->optValue = INFINITO;
	this->grafo = 0;
	this->pType = "";
	this->eType = "";
	this->eFormat = "";
}

template< class T > void TSPInstance< T >::setOptValue(T value) {
	this->optValue = value;
}

template< class T > inline T TSPInstance< T >::getOptValue() const {
	return this->optValue;
}

template<class T > void TSPInstance< T >::setOptTour(std::vector< unsigned int > tour) {
	this->optTour = tour;
}

template< class T > std::vector< unsigned int > TSPInstance< T >::getOptTour() const {
	return this->optTour;
}

template< class T > void TSPInstance< T >::setGrafo(GrafoNonOrientatoBetaMetrico< T > *grafo) {
	GrafoNonOrientatoBetaMetrico< T > *temp = this->grafo;

	this->grafo = grafo;
	if ( temp != 0 ) {
		delete temp;
	}
}

template< class T > GrafoNonOrientatoBetaMetrico< T > *TSPInstance< T >::getGrafo() {
	return this->grafo;
}

template< class T > void TSPInstance< T >::setProblemType(std::string type) {
	this->pType = type;
}

template< class T > inline std::string TSPInstance< T >::getProblemType() const {
	return this->pType;
}

template< class T > void TSPInstance< T >::setEdgeWType(std::string type) {
	this->eType = type;
}

template< class T > inline std::string TSPInstance< T >::getEdgeWType() const {
	return this->eType;
}

template< class T > void TSPInstance< T >::setEdgeWFormat(std::string format) {
	this->eFormat = format;
}

template< class T > inline std::string TSPInstance< T >::getEdgeWFormat() const {
	return this->eFormat;
}

} // namespace asd

#endif /*TSPINSTANCE_H_*/

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
