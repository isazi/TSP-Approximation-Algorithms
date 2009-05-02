/******************************************************************************\
*
* File:          Space.h
* Creation date: February 28, 2009.
* Author:        Alessio Sclocco
*
* License:       See the end of this file for license information
*
\******************************************************************************/

#ifndef SPACE_H_
#define SPACE_H_

#include <Point.h>
#include <map>
#include <cmath>

using std::map;
using std::pair;

namespace asd {

template< class T > class Space {
public:
	Space();
	~Space();

	/* Adding and deleting a point */
	Point *addPoint(T x, T y);
	void removePoint(Point *p);

	/* Getting coordinates of a point */
	T getX(Point *p);
	T getY(Point *p);

	/* Checking if a point is occupied */
	bool isOccupied(T x, T y);

	/* Moving a point */
	bool moveUp(Point *p, T x);
	bool moveRight(Point *p, T x);
	bool moveDown(Point *p, T x);
	bool moveLeft(Point *p, T x);

	/* Calculating distances between points */
	double l1Distance(Point *p, Point *q);
	double l2Distance(Point *p, Point *q);
	double lInfDistance(Point *p, Point *q);

private:
	map< Point *, pair< T, T > > pointToCoord;
	map< pair< T, T >, Point * > coordToPoint;
};

template< class T > Space< T >::Space() {
}

template< class T > Space< T >::~Space() {
}

template< class T > Point *Space< T >::addPoint(T x, T y) {
	if ( this->isOccupied(x, y) ) {
		return 0;
	}
	else {
		Point *newPoint = new Point();
		pointToCoord[newPoint] = pair< T, T >(x, y);
		coordToPoint[pair< T, T >(x, y)] = newPoint;
		return newPoint;
	}
}

template< class T > void Space< T >::removePoint(Point *p) {
	pair< T, T > tempCoord = pointToCoord[p];
	pointToCoord.erase(p);
	coordToPoint.erase(tempCoord);
	delete p;
}

template< class T > T Space< T >::getX(Point *p) {
	pair< T, T > tempCoord = pointToCoord[p];

	return tempCoord.first;
}

template< class T > T Space< T >::getY(Point *p) {
	pair< T, T > tempCoord = pointToCoord[p];

	return tempCoord.second;
}

template< class T > bool Space< T >::isOccupied(T x, T y) {
	if ( coordToPoint.find(pair< T, T >(x, y)) != coordToPoint.end() ) {
		return true;
	}
	else {
		return false;
	}
}

template< class T > bool Space< T >::moveUp(Point *p, T x) {
	if ( ! isOccupied(this->getX(p), this->getY(p) + x) ) {
		pair< T, T > newCoord = pair< T, T >(this->getX(p), this->getY(p) + x);
		coordToPoint.erase(this->getX(p), this->getY(p));
		coordToPoint[newCoord] = p;
		coordToPoint[p] = newCoord;

		return true;
	}
	else {
		return false;
	}
}

template< class T > bool Space< T >::moveRight(Point *p, T x) {
	if ( ! isOccupied(this->getX(p) + x, this->getY(p)) ) {
		pair< T, T > newCoord = pair< T, T >(this->getX(p) + x, this->getY(p));
		coordToPoint.erase(this->getX(p), this->getY(p));
		coordToPoint[newCoord] = p;
		coordToPoint[p] = newCoord;

		return true;
	}
	else {
		return false;
	}
}

template< class T > bool Space< T >::moveDown(Point *p, T x) {
	if ( ! isOccupied(this->getX(p), this->getY(p) - x) ) {
		pair< T, T > newCoord = pair< T, T >(this->getX(p), this->getY(p) - x);
		coordToPoint.erase(this->getX(p), this->getY(p));
		coordToPoint[newCoord] = p;
		coordToPoint[p] = newCoord;

		return true;
	}
	else {
		return false;
	}
}

template< class T > bool Space< T >::moveLeft(Point *p, T x) {
	if ( ! isOccupied(this->getX(p) - x, this->getY(p)) ) {
		pair< T, T > newCoord = pair< T, T >(this->getX(p) - x, this->getY(p));
		coordToPoint.erase(this->getX(p), this->getY(p));
		coordToPoint[newCoord] = p;
		coordToPoint[p] = newCoord;

		return true;
	}
	else {
		return false;
	}
}

template< class T > double Space< T >::l1Distance(Point *p, Point *q) {
	return static_cast< double >(fabs(this->getX(p) - this->getX(q)) + fabs(this->getY(p) - this->getY(q)));
}

template< class T > double Space< T >::l2Distance(Point *p, Point *q) {
	return static_cast< double >(sqrt(pow(fabs(this->getX(p) - this->getX(q)), 2.0) + pow(fabs(this->getY(p) - this->getY(q)), 2.0)));
}

template< class T > double Space< T >::lInfDistance(Point *p, Point *q) {
	double x = fabs(this->getX(p) - this->getX(q)), y = fabs(this->getY(p) - this->getY(q));
	if ( x > y ) {
		return x;
	}
	else {
		return y;
	}
}

} // namespace asd

#endif /* SPACE_H_ */

/******************************************************************************\
 * Copyright (C) 2009 Alessio Sclocco <alessio@sclocco.eu>

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
