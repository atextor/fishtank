/* Node.h
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

#ifndef NODE_H_
#define NODE_H_
#include <cstdlib>
#include <GL/glut.h>

/**
 * Abstract base class for scene graph nodes. A node has a child node and
 * a work() method for graph traversal
 */
class Node {
protected:
	/**
	 * The child node
	 */
	Node* child;

	/**
	 * Default constructor
	 */
	Node();

	/**
	 * Construktor with a child node
	 */
	Node(Node* child);

public:
	/**
	 * Abstract method for tree traversal
	 */
	virtual void work() = 0;

	/**
	 * Default destructor
	 */
	virtual ~Node();
};

#endif /*NODE_H_*/
