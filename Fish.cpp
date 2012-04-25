/* Fish.cpp
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

#include "Fish.h"

list<Fish*> Fish::fishList;
int Fish::unfriendlies = 0;

struct Fish::Data Fish::data[35] = {
	{{4, 4.8, 2},	{0.0, 0.0, 1.0}},
	{{7, 7.6, 0},	{0.5, 1.0, 0.0}},
	{{5, 8, 0},		{0.0, 1.0, 0.0}},
	{{1.9, 6.2, 0},	{-0.5, 0.5, 0.0}},
	{{0.5, 4.1, 0},	{-1.0, -0.25, 0.0}},
	{{1, 2.8, 0},	{-0.5, -0.5, 0.0}},
	{{4, 1, 0},		{0.0, -1.0, 0.0}},

	{{4, 4.8, 2},	{0.0, 0.0, 1.0}},
	{{4, 1, 0},		{0.0, -1.0, 0.0}},
	{{14.2, 4, 0},	{1.0, -1.0, 0.0}},
	{{11, 4.8, 1},	{0.5, 1.0, -0.5}},

	{{14.2, 4, 0},	{1.0, -1.0, 0.0}},
	{{14.8, 5.5, 0},{1.0, 1.0, 0.0}},

	{{11, 4.8, 1},	{0.5, 1.0, 0.0}},
	{{14.8, 5.5, 0},{1.0, 1.0, 0.0}},
	{{7, 7.6, 0},	{0.25, 1.0, 0.0}},
	{{4, 4.8, 2},	{0.0, 0.0, 1.0}},

	//
	{{4, 4.8, -2},	{0.0, 0.0, -1.0}},
	{{4, 1, 0},		{0.0, -1.0, 0.0}},
	{{1, 2.8, 0},	{-0.5, -0.5, 0.0}},
	{{0.5, 4.1, 0},	{-1.0, -0.25, 0.0}},
	{{1.9, 6.2, 0},	{-0.5, 0.5, 0.0}},
	{{5, 8, 0},		{0.0, 1.0, 0.0}},
	{{7, 7.6, 0},	{0.25, 1.0, 0.0}},

	{{11, 4.8, -1},	{0.5, 1.0, 0.5}},
	{{14.2, 4, 0},	{1.0, -1.0, 0.0}},
	{{4, 1, 0},		{0.0, -1.0, 0.0}},
	{{4, 4.8, -2},	{0.0, 0.0, -1.0}},

	{{14.8, 5.5, 0},{1.0, 1.0, 0.0}},
	{{14.2, 4, 0},	{1.0, -1.0, 0.0}},
	{{11, 4.8, -1},	{0.5, 1.0, 0.5}},

	{{4, 4.8, -2},	{0.0, 0.0, -1.0}},
	{{7, 7.6, 0},	{0.25, 1.0, 0.0}},
	{{14.8, 5.5, 0},{1.0, 1.0, 0.0}},
	{{11, 4.8, -1},	{0.5, 1.0, 0.5}}
};

Fish* Fish::getFirst() {
	return fishList.size() > 0 ? fishList.front() : NULL;
}

bool Fish::getFriendly() {
	return friendly;
}

Vector* Fish::getPosition() {
	return position;
}

bool Fish::moveAll() {
	for (list<Fish*>::iterator it = fishList.begin(); it != fishList.end(); it++) {
		if (!(*it)->move()) {
			return false;
		}
	}
	return true;
}

bool Fish::move() {
	// Calculate turning direction
	Vector d = *position - *lastPosition;
	d.norm();
	d *= 50.0;

	Vector dir = d % Vector::e2;

	angle = (int)(Vector::e1.angle2dxz(dir));
	// Don't turn too jerky
	if (abs(angle - lastAngle) > 9) {
		if (angle < lastAngle) {
			angle = lastAngle - 9;
		} else {
			angle = lastAngle + 9;
		}
	}

	*lastPosition = *position;
	lastAngle = angle;

	// Find swarm
	list<Fish*> swarm;
	for (list<Fish*>::iterator it = fishList.begin(); it != fishList.end(); it++) {
		if ((*it != this) && ((*it)->friendly == true)) {
			Vector distance = *position - *((*it)->position);
			if (distance.length() <= 60.0) {
				swarm.push_back(*it);
			}
		}
	}

	// Rule 1: Separation
	Vector separationDirection(0, 0, 0);
	Vector septmp(0, 0, 0);
	for (list<Fish*>::iterator it = swarm.begin(); it != swarm.end(); it++) {
		septmp = *position - *((*it)->position);
		septmp.norm();
		separationDirection += septmp;

	}
	separationDirection.norm();
	separationDirection *= 1.5;

	// Rule 2: Alignment
	Vector alignmentDirection = *destination;
	for (list<Fish*>::iterator it = swarm.begin(); it != swarm.end(); it++) {
		alignmentDirection += *((*it)->destination);
	}
	alignmentDirection.norm();
	alignmentDirection *= 2.5;

	// Rule 3: Cohesion
	Vector swarmCenter(0, 0, 0);
	if (swarm.size() > 0) {
		for (list<Fish*>::iterator it = swarm.begin(); it != swarm.end(); it++) {
			swarmCenter += *((*it)->position);
		}
		swarmCenter *= (1.0 / swarm.size());
		swarmCenter = swarmCenter - *position;
		swarmCenter *= 0.04;
	}

	// Rule 4: Away from sharks
	Vector sharkCenter(0, 0, 0);
	if (unfriendlies > 0) {
		for (list<Fish*>::iterator it = fishList.begin(); it != fishList.end(); it++) {
			if ((*it)->friendly == false) {
				sharkCenter += *((*it)->position);
			}
			sharkCenter = sharkCenter - *position;
			sharkCenter.norm();
			sharkCenter *= -1;
		}
	}

	*destination = separationDirection + alignmentDirection;
	*destination += swarmCenter;
	*destination += sharkCenter;


	Vector tmp = *position + *destination;
	// Away from walls
	if (tmp.x < -(tankWidth - 180) / 2) {
		destination->x += 1.0;
	}
	if (tmp.x > (tankWidth - 180) / 2) {
		destination->x -= 1.0;
	}

	// Away from surface of water and bottom
	if (tmp.y < -(tankHeight - 40) / 2) {
		destination->y += 1.0;
	}
	if (tmp.y > (tankHeight - 40) / 2) {
		destination->y -= 1.0;
	}

	// If arrived there nevertheless, turn
	if ((tmp.x < -(tankWidth - 30) / 2) || (tmp.x > (tankWidth - 30) / 2)) {
		destination->x *= -1;
	}
	if ((tmp.y < -tankHeight / 2) || (tmp.y > tankHeight / 2)) {
		destination->y *= -1;
	}
	if ((tmp.z < -tankDepth / 2) || (tmp.z > tankDepth / 2)) {
		destination->z *= -1;
	}
	*position += *destination;

	// Just to be sure: If out of tank, get back in
	if (position->x < (-(tankWidth - 30) / 2)) {
		position->x = (-(tankWidth - 30)/ 2);
		destination->x += 100.0;
	}
	if (position->x > (tankWidth / 2)) {
		position->x = (tankWidth / 2);
		destination->x -= 100.0;
	}
	if (position->y < (-tankHeight / 2)) {
		position->y = (-tankHeight / 2);
	}
	if (position->y > (tankHeight / 2)) {
		position->y = (tankHeight / 2);
	}
	if (position->z < (-tankDepth / 2)) {
		position->z = (-tankDepth / 2);
	}
	if (position->z > (tankDepth / 2)) {
		position->z = (tankDepth / 2);
	}

	return true;
}

void Fish::draw() {
	// Position and turning
	glTranslated(position->x, position->y, position->z);
	glRotated((angle + 270) % 360, 0, 1, 0);

	// Select material
	mat->select();

	// Update name position
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

Fish::Fish(Material* mat, Text* name, Vector* position, Vector* direction):
		Object(mat, name),position(position),destination(direction) {
	fishList.push_back(this);
	constructParts();
	lastPosition = new Vector(0, 0, 0);
	lastAngle = 0;
	friendly = true;
}

void Fish::constructParts() {
	fishParts = children(
		// tail fin
		translation(
			13.5, 0, 0,
			tail = rotation(
				0.0, 0.0, 1.0, 0.0,
				polygon(
					mat,
					0.8, 5.5, 0.0,
					0.2, 4.0, 0.0,
					2.5, 2.5, 0.0,
					8.0, 1.0, 0.0,
					7.0, 3.0, 0.0,
					4.0, 5.0, 0.0,
					6.5, 8.5, 0.0,
					6.5, 10.3, 0.0,
					POLY_END
				)
			)
		),

		// back fin
		polygon(
			mat,
			5.0, 8.0, 0.0,
			11.5, 6.2, 0.0,
			11.0, 8.0, 0.0,
			6.2, 9.0, 0.0,
			POLY_END
		),

		// left eye
		translation(
			4.2, 4.8, 1.5,
			sphere(0.7, 6)
		),

		// right eye
		translation(
			4.2, 4.8, -1.5,
			sphere(0.7, 6)
		),

		translation(
			0.0, 4.0, 0.0,
			children(
				// left fin
				leftFin = rotation(
					0.0, 1.0, 0.0, 0.0,
					polygon(
						mat,
						6.5, 4.0, 0.0,
						5.5, 2.0, 0.0,
						7.8, 0.8, 0.0,
						10.5, 4.0, 0.0,
						POLY_END
					)
				),

				// right fin
				rightFin = rotation(
					0.0, 1.0, 0.0, 0.0,
					polygon(
						mat,
						6.5, 4.0, 0.0,
						5.5, 2.0, 0.0,
						7.8, 0.8, 0.0,
						10.5, 4.0, 0.0,
						POLY_END
					)
				)
			)
		)
	);

	// Sinusoidal animation, 1.5 as period, 20 as amplitued
	// 0x8 = field mask for 1st component (= angle in rotation node)
	new Animation(tail, Animation::ANI_SINUSOIDAL, 1.5, 20, 0.0, 0x8);

	// Period 2.0, amplitude 12, displacement 120 degrees
	new Animation(leftFin, Animation::ANI_SINUSOIDAL, 2.0, 12, 120.0, 0x8);
	new Animation(rightFin, Animation::ANI_SINUSOIDAL, 2.0, 12, -120.0, 0x8);
}

Fish::~Fish() {
	// Tell animation that we're gone
	Animation::remove(tail);
	Animation::remove(leftFin);
	Animation::remove(rightFin);

	delete fishParts;
	delete position;
	delete destination;
	delete lastPosition;

	// And the list of fish as well
	list<Fish*>::iterator it2;
	for (list<Fish*>::iterator it = fishList.begin(); it != fishList.end(); it++) {
		if ((*it) == this) {
			it2 = it;
			break;
		}
	}
	fishList.erase(it2);
}
