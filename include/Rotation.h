/* Rotation.h
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

#ifndef ROTATION_H_
#define ROTATION_H_
#include "Transform.h"
#define rotation new Rotation

/**
 * Rotation is a transformation node in the scene graph and executes a
 * glRotate before the graph is traversed further and work() on its child node
 * is called.
 */
class Rotation : public Transform {
public:
	/**
	 * Constrcutor with a coordinate vector and an optional child node.
	 * In the vector, X is the angle and Y, Z and W are the rotation axis
	 */
	Rotation(Vector* transformation, Node* child = 0);
	
	/**
	 * Constructor for four double values and an optional child node.
	 * a is the angle, b, c and d are the rotation axis
	 */
	Rotation(double a, double b, double c, double d, Node* child = 0);
	
	/**
	 * Traverse the scene graph further, i.e. call work() on child node
	 */
	void work();
	
	/**
	 * Default destructor
	 */
	virtual ~Rotation();
};

#endif /*ROTATION_H_*/
