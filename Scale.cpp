/* Scale.cpp
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

#include "Scale.h"

Scale::Scale(Vector* transformation, Node* child):Transform(transformation, child) {
}

Scale::Scale(double a, double b, double c, Node* child):Transform(a, b, c, 0, child) {
}

void Scale::work() {
	if (transformation != 0) {
		glScaled(transformation->x, transformation->y, transformation->z);	
	}
	if (child != 0) {
		child->work();
	}
}

Scale::~Scale() {
	if (transformation != 0) {
		delete transformation;
	}
}
