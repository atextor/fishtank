/* Scale.h
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

#ifndef SCALE_H_
#define SCALE_H_
#include "Transform.h"
#define scale new Scale

/**
 * Scala is a transformation node in the scene graph and executes a glScale,
 * bevor it further traverses the scene graph and calls work() on its child
 * node
 */
class Scale : public Transform  {
public:
	/**
	 * Constructor: x, y and z of the vector define the scaling, w is ignored
	 */
	Scale(Vector* transformation, Node* child = 0);
	
	/**
	 * Constructor for double values: a, b and c define the scaling
	 */
	Scale(double a, double b, double c, Node* child = 0);
	
	/**
	 * Further traverse the scene graph, i.e. call work() on child node
	 */
	void work();
	
	/**
	 * Default destructor
	 */
	virtual ~Scale();
};

#endif /*SCALE_H_*/
