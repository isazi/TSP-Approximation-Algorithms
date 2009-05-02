/******************************************************************************\
*
* File:          GrafoNonOrientatoBetaMetrico.h
* Creation date: June 28, 2008
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef GRAFONONORIENTATOBETAMETRICO_H_
#define GRAFONONORIENTATOBETAMETRICO_H_

#include <grafo/GrafoNonOrientato.h>

namespace asd {

template< class T > class GrafoNonOrientatoBetaMetrico : virtual public GrafoNonOrientato< T > {
public:
	GrafoNonOrientatoBetaMetrico();
	virtual ~GrafoNonOrientatoBetaMetrico();
	/* Imposta la beta del grafo  */
	bool setBeta(double beta = 1.0);
	/* Restituisce la beta del grafo */
	inline double getBeta() const;
	/* Genera un grafo completo beta metrico di n vertici con pesi casuali */
	void generaRandom(unsigned int nodi);
	/* Verifica che il grafo rispetti la b-disuguaglianza triangolare */
	virtual bool verifyBetaMetric(bool correct = false) = 0;

private:
	double beta;
};

template< class T > GrafoNonOrientatoBetaMetrico< T >::GrafoNonOrientatoBetaMetrico() {
	this->setBeta();
}

template< class T > GrafoNonOrientatoBetaMetrico< T >::~GrafoNonOrientatoBetaMetrico() {
}

template< class T > bool GrafoNonOrientatoBetaMetrico< T >::setBeta(double beta) {
	if ( beta >= 0.5 ) {
		this->beta = beta;
		return true;
	}
	else {
		this->beta = 1.0;
		return false;
	}
}

template< class T > inline double GrafoNonOrientatoBetaMetrico< T >::getBeta() const {
	return this->beta;
}

} // namespace asd

#endif /* GRAFONONORIENTATOBETAMETRICO_H_ */

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
