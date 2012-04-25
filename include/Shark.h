/* Shark.h
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

#ifndef SHARK_H_
#define SHARK_H_

#include "Fish.h"

/**
 * Shark inherits from Fish, uses its properites and vertex- and normals
 * definitions and moves towards the fish swarm
 */
class Shark : public Fish {
private:
	/**
	 * Which fish is currently pursued
	 */
	Fish* target;
	
public:
	/**
	 * Constructor with material, name, position and direction
	 */
	Shark(Material* mat, Text* name, Vector* position, Vector* direction);
	
	/**
	 * Draw the shark
	 */
	virtual void draw();
	
	/**
	 * Move the shark. Returns true, if no fish was eaten and false, when the
	 * last fish in the list of fish was eaten
	 */
	virtual bool move();
	
	/**
	 * Find the next target: The last fish from the list of fish, but not the
	 * glowing fish
	 */
	void nextTarget();
	
	/**
	 * Default destructor
	 */
	virtual ~Shark();
};

#endif /*SHARK_H_*/
