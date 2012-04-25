/* Vector.h
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

#ifndef COORD3D_H_
#define COORD3D_H_
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
using std::cout;
using std::ostream;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define vector new Vector
#define color new Vector

/**
 * Class for a four element vector
 */
class Vector {
public:
	/**
	 * x component
	 */
	double x;

	/**
	 * y component
	 */
	double y;

	/**
	 * z component
	 */
	double z;

	/**
	 * w component
	 */
	double w;

	/**
	 * Vector for the x axis
	 */
	static Vector e1;

	/**
	 * Vector for the y axis
	 */
	static Vector e2;

	/**
	 * Vector for the z axis
	 */
	static Vector e3;

	/**
	 * Constructor with four int values
	 */
	Vector(int a, int b = 0, int c = 0, int d = 1);

	/**
	 * Constructor with four double values
	 */
	Vector(double a = 0.0, double b = 0.0, double c = 0.0, double d = 1.0);

	/**
	 * Ouput as output stream
	 */
	friend ostream& operator<<(ostream& o, Vector& v);

	/**
	 * Calculates the angle of two vectors from top view
	 */
	const double angle2dxz(const Vector& v);

	/**
	 * Cartesian product
	 */
	const Vector operator%(const Vector& v);

	/**
	 * Vector multiplication
	 */
	const void operator*=(const GLfloat& v);

	/**
	 * Vector multiplication
	 */
	const Vector operator*(const GLfloat& v);

	/**
	 * Vector addition
	 */
	const Vector operator+(const Vector& v);

	/**
	 * Vector addition
	 */
	const void operator+=(const Vector& v);

	/**
	 * Vector subtraction
	 */
	const Vector operator-(const Vector& v);

	/**
	 * Vector subtraction
	 */
	const void operator-=(const Vector& v);

	/**
	 * Length of the vector
	 */
	const double length() const;

	/**
	 * Scalar product
	 */
	const double dot(const Vector& v);

	/**
	 * Norm the vector (keep direction, make length 1)
	 */
	void norm();

	/**
	 * Set values
	 */
	void set(int a, int b, int c, int d = 1);

	/**
	 * Set values
	 */
	void set(double a, double b, double c, double d = 1.0);

	/**
	 * Default destructor
	 */
	virtual ~Vector();
};

#define Color Vector

#endif /*COORD3D_H_*/
