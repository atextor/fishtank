/* Object.h
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

#ifndef OBJECT_H_
#define OBJECT_H_
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include "Vector.h"
#include "Node.h"
#include "Material.h"
#include "Text.h"
using std::cout;

/**
 * Abstract object node, which acts as leaf in the scene graph. These are
 * the actual objects that are drawn on the screen
 */
class Object : public Node {
protected:
	/**
	 * The material is an attribute of the node rather than a parent node in
	 * the scene graph, even though OpenGL "switches" on material properties
	 * bevor drawing
	 */
	Material* mat;

	/**
	 * Optional text object for the name
	 */
	Text* name;

	/**
	 * Used to convert 3d coordinates into 2d coordinates
	 */
	GLdouble x;

	/**
	 * Used to convert 3d coordinates into 2d coordinates
	 */
	GLdouble y;

	/**
	 * Used to convert 3d coordinates into 2d coordinates
	 */
	GLdouble z;

	/**
	 * Model view matrix
	 */
	GLdouble mm[16];

	/**
	 * Projection matrix
	 */
	GLdouble pm[16];

	/**
	 * Viewport
	 */
	GLint viewport[4];

public:
	/**
	 * Constructor with optional material
	 */
	Object(Material* mat = 0);

	/**
	 * Constructor with material and name
	 */
	Object(Material* mat, Text* name);

	/**
	 * Returns the material
	 */
	Material* getMaterial();

	/**
	 * Calls the actuall drawing routine
	 */
	virtual void work();

	/**
	 * Abstract method that draws the object
	 */
	virtual void draw() = 0;

	/**
	 * Default destructor
	 */
	virtual ~Object();
};

#endif /*OBJECT_H_*/
