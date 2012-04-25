/* Box.h
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

#ifndef BOX_H_
#define BOX_H_
#include "Object.h"
#define box new Box

/**
 * Represents a box with certain dimensions
 */
class Box : public Object {
private:
	/**
	 * Width of the box
	 */
	 
	double width;
	/**
	 * Height of the box
	 */
	 
	double height;
	/**
	 * Depth of the box
	 */
	double depth;
	
public:
	/**
	 * Constructor: Reads the necessary dimensions and optionally a material
	 */
	Box(double width, double height, double depth, Material* mat = 0);
	
	/**
	 * Draw the object
	 */
	void draw();
	
	/**
	 * Default destructor
	 */
	virtual ~Box();
};

#endif /*BOX_H_*/
