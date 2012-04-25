/* Polygon.h
 *
 * fishtank - fish swarm simulation
 * by Andreas Textor <textor.andreas@googlemail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef FACESET_H_
#define FACESET_H_
#include <list>
#include <iostream>
#include <cstdarg>
#include "Object.h"
#include "Vector.h"
using std::list;
using std::cout;
#define polygon new Polygon
#define POLY_END 1000.0

/**
 * Concrete object node that draws a polygon. The coordinates of the polygon
 * are given as a list of double values in the constructor, which reads a
 * variable number of arguments. The number must be x+1 with (x % 3)==0 and
 * the (x+1)th element must be POLY_END (sentinel for variable argument count)
 */
class Polygon : public Object { 
private:
	/**
	 * List of coordinates
	 */
	list<double> coords;
public:
	/**
	 * Constructor for polygon with material
	 */
	Polygon(Material* mat, ...);
	
	/**
	 * Constructor for polygon without material
	 */
	Polygon(double n1, ...);
	
	/** 
	 * Method that draws the polygon
	 */
	void draw();
	
	/**
	 * Default destructor
	 */
	virtual ~Polygon();
};

#endif /*FACESET_H_*/
