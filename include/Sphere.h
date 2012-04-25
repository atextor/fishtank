/* Sphere.h
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

#ifndef SPHERE_H_
#define SPHERE_H_
#include <cstdlib>
#include <GL/glut.h>
#include "Object.h"
#define sphere new Sphere

/**
 * Represents a sphere as object node in the scene graph
 */
class Sphere : public Object {
private:
	/**
	 * The quadric object that stores the actual sphere
	 */
	GLUquadricObj *sph;

	/**
	 * Radius of the sphere
	 */
	double radius;

	/**
	 * Number of horizontal and vertical segments
	 */
	int detail;

public:
	/**
	 * Constructor for a sphere with a radius and an optional material
	 */
	Sphere(double radius, int detail, Material* mat = 0);

	/**
	 * Draw the sphere
	 */
	void draw();

	/**
	 * Default destructor
	 */
	virtual ~Sphere();
};

#endif /*SPHERE_H_*/
