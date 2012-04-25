/* Fish.h
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

#ifndef FISH_H_
#define FISH_H_
#include <list>
#include "Object.h"
#include "Children.h"
#include "Animation.h"
#include "Translation.h"
#include "Rotation.h"
#include "Polygon.h"
#include "Sphere.h"
#include "Vector.h"
#include "config.h"
using std::list;

/**
 * The Fish class has a static list that is used for the swarm movement. Each
 * Fish object is an object node (draw() method).
 */
class Fish : public Object {
protected:
	/**
	 * Point data. Could be complemented by texture or similar
	 */
	struct Data {
		GLfloat vertex[3];
		GLfloat normal[3];
	};

	/**
	 * Position vector
	 */
	Vector* position;

	/**
	 * Vector of destination point
	 */
	Vector* destination;

	/**
	 * Last position is used to calculate the turning
	 */
	Vector* lastPosition;

	/**
	 * Last angle is used to prevent floundering (no pun intended)
	 */
	int lastAngle;

	/**
	 * Current angle of the fish
	 */
	int angle;

	/**
	 * List of all fish, for swarm behaviour
	 */
	static list<Fish*> fishList;

	/**
	 * Is the fish friendly towards other fish? (shark = no)
	 */
	bool friendly;

	/**
	 * Scene graph node for the tail
	 */
	Transform* tail;

	/**
	 * Scene graph node for the left fin
	 */
	Transform* leftFin;

	/**
	 * Scene graph node for the right fin
	 */
	Transform* rightFin;

	/**
	 * Scene graph nodes for fins and eyes
	 */
	Children* fishParts;

	/**
	 * Number of unfriendly fishes
	 */
	static int unfriendlies;

	/**
	 * Vertex data of the fish mesh
	 */
	static struct Data data[35];

	/**
	 * Is called once to construct the parts of the fish other than the torso
	 */
	void constructParts();

	/**
	 * Move the fish
	 */
	virtual bool move();

public:
	/**
	 * Moves all fish in their swarm behaviour
	 */
	static bool moveAll();

	/**
	 * Returns the first fish
	 */
	static Fish* getFirst();

	/**
	 * Returns the position of the fish
	 */
	Vector* getPosition();

	/**
	 * Constructor: Fish with material and name
	 */
	Fish(Material* mat, Text* name, Vector* position, Vector* direction);

	/**
	 * Returns the friendly  attribute of the fish
	 */
	bool getFriendly();

	/**
	 * Draw the object
	 */
	virtual void draw();

	/**
	 * Default destructor
	 */
	virtual ~Fish();
};

#endif /*FISH_H_*/
