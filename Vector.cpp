/* Vector.cpp
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

#include "Vector.h"

Vector Vector::e1(1, 0, 0);
Vector Vector::e2(0, 1, 0);
Vector Vector::e3(0, 0, 1);

void Vector::set(int a, int b, int c, int d) {
	x = (double)a;
	y = (double)b;
	z = (double)c;
	w = (double)d;
}

void Vector::set(double a, double b, double c, double d) {
	x = a;
	y = b;
	z = c;
	w = d;
}

const double Vector::angle2dxz(const Vector& v) {
	double phi;
	double cosphi = (x*v.x + z*v.z) / (sqrt(x*x + z*z) * sqrt(v.x*v.x + v.z*v.z));
	if (cosphi > 1) {
		cosphi = 1;
	}
	phi = acos(cosphi);
	
	double kpz = x * v.z - z * v.x;
	if (kpz > 0) {
		phi *= -1;
	}
	return (180.0 / M_PI) * phi;
}

const double Vector::dot(const Vector& v) {
	return x * v.x + y * v.y + z * v.z;	
}

const Vector Vector::operator*(const GLfloat& v) {
	return Vector(x * v, y * v, z * v, w * v);
}

const void Vector::operator*=(const GLfloat& v) {
	x *= v;
	y *= v;
	z *= v;
	w *= v;
}
	
const Vector Vector::operator+(const Vector& v) {
	return Vector(x + v.x, y + v.y, z + v.z, w + v.w);
}

const void Vector::operator+=(const Vector& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}

const Vector Vector::operator%(const Vector& v) {
	return Vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x, 0.0);	
}

const Vector Vector::operator-(const Vector& v) {
	return Vector(x - v.x, y - v.y, z - v.z, w - v.w);
}

const void Vector::operator-=(const Vector& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
}

const double Vector::length() const {
	return sqrt(x*x + y*y + z*z);	
}

ostream& operator<<(ostream& o, Vector& v) {
	o << "[" << v.x << "," << v.y << "," << v.z << "," << v.w << "]";
	return o;
}

void Vector::norm() {
	double len = length();
	if (len > 0.0) {	
		*this *= 1.0/len;	
	}
}

	
Vector::Vector(double a, double b, double c, double d):x(a),y(b),z(c),w(d) {
}

Vector::Vector(int a, int b, int c, int d) {
	set(a, b, c, d);
}	

Vector::~Vector() {
}
