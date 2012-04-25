/* Transform.h
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

#ifndef TRANSFORM_H_
#define TRANSFORM_H_
#include <cstdlib>
#include <GL/glut.h>
#include "Node.h"
#include "Vector.h"

/**
 * Abstract scene graph node that transforms child nodes
 */
class Transform : public Node {
protected:
	/**
	 * Vector that stores the transformation data
	 */
	Vector* transformation;

public:
	/**
	 * Default constructor
	 */
	Transform();

	/**
	 * Constructor with a transformation data vector
	 */
	Transform(Vector* transformation);

	/**
	 * Constructor with four double values for the transformation data
	 */
	Transform(double a, double b = 0.0, double c = 0.0, double d = 0.0);

	/**
	 * Constructor with a transformation data vector and an optional child
	 * node
	 */
	Transform(Vector* transformation, Node* child);

	/**
	 * Constructor with four double values for the transformation data and an
	 * optional child node
	 */
	Transform(double a, double b, double c, double d, Node* child);

	/**
	 * Returns the current transformation data vector
	 */
	Vector* getTransformation();

	/**
	 * Abstract method for the actual transformation
	 */
	void work() = 0;

	/**
	 * Default destructor
	 */
	virtual ~Transform();
};

#endif /*TRANSFORM_H_*/
