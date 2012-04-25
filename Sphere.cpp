/* Sphere.cpp
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

#include "Sphere.h"

void Sphere::draw() {
	mat->select();
	glEnable(GL_TEXTURE_2D);
	Textures::select(Textures::ENVMAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPolygonMode(GL_FRONT, GL_FILL);
	gluSphere(sph, radius, detail, detail);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

Sphere::Sphere(double radius, int detail, Material* mat):Object(mat),radius(radius),
		detail(detail) {
	sph = gluNewQuadric();
	gluQuadricNormals(sph, GLU_SMOOTH);
}

Sphere::~Sphere()
{
}
