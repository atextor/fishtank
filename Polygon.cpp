/* Polygon.cpp
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

#include "Polygon.h"

Polygon::Polygon(Material* mat, ...):Object(mat) {
	int count = 0;
	double n = 0;
	va_list parameter;
	va_start(parameter, mat);

	do {
		count++;
		n = va_arg(parameter, double);
		if (n <= 999.0) {
			coords.push_back(n);
		}
	} while(n <= 999.0);
	va_end(parameter);
}

Polygon::Polygon(double n1, ...):Object() {
	coords.push_back(n1);
	int count = 0;
	double n = 0;
	va_list parameter;
	va_start(parameter, n1);

	do {
		count++;
		n = va_arg(parameter, double);
		if (n <= 999.0) {
			coords.push_back(n);
		}
	} while(n <= 999.0);
	va_end(parameter);
}

Polygon::~Polygon() {
}

void Polygon::draw() {
	mat->select();

	list<double>::iterator it2;
	list<double>::iterator it3;
	glBegin(GL_POLYGON);
	for (list<double>::iterator it = coords.begin();
			it != coords.end(); it++,it++,it++) {
		it2 = it; it2++;
		it3 = it2; it3++;
		glVertex3d(*it, *it2, *it3);
	}
	glEnd();
}

