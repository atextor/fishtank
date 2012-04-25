/* Shark.cpp
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

#include "Shark.h"

Shark::Shark(Material* mat, Text* name, Vector* position, Vector* direction):
		Fish(mat, name, position, direction) {
	friendly = false;
	lastAngle = 0;
	angle = 0;
	unfriendlies++;
	nextTarget();
}

void Shark::nextTarget() {
	target = 0;
	for (list<Fish*>::iterator it = fishList.end(); it != fishList.begin();) {
		it--;
		if (*it == fishList.front()) {
			return;
		}
		if ((*it)->getFriendly() == true) {
			target = *it;
			return;
		}
	}
}

bool Shark::move() {
	bool result = true;

	// Calculate turning
	Vector d = *position - *lastPosition;
	d.norm();
	d *= 50.0;
	Vector dir = d % Vector::e2;

	// Move the center if no fish are left
	if (target == 0) {
		Vector center(0, 0, 0);
		center = center - *position;
		if (center.length() >= 1) {
			angle = (int)(Vector::e1.angle2dxz(dir));
		}
	} else {
		angle = (int)(Vector::e1.angle2dxz(dir));
	}

	// Don't turn too jerky
	if (abs(angle - lastAngle) > 20) {
		if (angle < lastAngle) {
			angle = lastAngle - 20;
		} else {
			angle = lastAngle + 20;
		}
	}

	*lastPosition = *position;
	lastAngle = angle;

	// Arrived at target?
	if (target != 0) {
		Vector dist = *(target->getPosition()) - *position;
		if (dist.length() < 15.0) {
			// Eat
			result = false;
		}
	}

	// Target: next fish
	Vector nextFish(0, 0, 0);
	if (target == 0) {
		nextFish = nextFish - *position;
	} else {
		nextFish = *(target->getPosition()) - *position;
	}
	if (nextFish.length() > 5.0) {
		nextFish.norm();
		nextFish *= 5.0;
	}
	*position += nextFish;

	return result;
}

void Shark::draw() {
	// Position and turning
	glTranslated(position->x, position->y, position->z);
	glRotated((angle + 270) % 360, 0, 1, 0);
	glTranslated(-40, 0, 0);
	glScaled(5.0, 5.0, 5.0);

	// Select material
	mat->select();

	// Update position of name
	glGetDoublev(GL_MODELVIEW_MATRIX, mm);
	glGetDoublev(GL_PROJECTION_MATRIX, pm);
	glGetIntegerv(GL_VIEWPORT, viewport);
	gluProject(10.0, 5.0, 0.0, mm, pm, viewport, &x, &y, &z);
	name->setCoords((int)x, int(y));

	// Draw torso
    glEnable(GL_NORMALIZE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(struct Data), data[0].vertex);
	glNormalPointer(GL_FLOAT, sizeof(struct Data), data[0].normal);

	glDrawArrays(GL_TRIANGLE_FAN, 0, 7);
	glDrawArrays(GL_QUADS, 7, 4);
	glDrawArrays(GL_POLYGON, 10, 3);
	glDrawArrays(GL_QUADS, 13, 4);
	glDrawArrays(GL_TRIANGLE_FAN, 17, 7);
	glDrawArrays(GL_QUADS, 24, 4);
	glDrawArrays(GL_POLYGON, 28, 3);
	glDrawArrays(GL_QUADS, 31, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisable(GL_NORMALIZE);

	// Draw other parts
	fishParts->work();
}

Shark::~Shark() {
	unfriendlies--;
}
