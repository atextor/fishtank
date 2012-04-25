/* Children.h
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

#ifndef CHILDREN_H_
#define CHILDREN_H_
#include <cstdarg>
#include <iostream>
#include <list>
#include <cstdlib>
#include "GL/glut.h"
#include "Node.h"
using std::cout;
using std::list;
#define children new Children

/**
 * Scene graph node that acts as T-junction and can have more than one child
 * node
 */
class Children : public Node {
private:
	/**
	 * List of child nodes
	 */
	list<Node*> children_;

public:
	/**
	 * Returns the n-th node
	 */
	Node* getNode(int index);

	/**
	 * Adds a new child node
	 */
	void addNode(Node* nde);

	/**
	 * Removes the last node
	 */
	void removeNode();

	/**
	 * Traverse the tree: Call work() methods of all child nodes
	 */
	void work();

	/**
	 * Returns the number of child nodes
	 */
	int size();

	/**
	 * Default constructor: When children are added later
	 */
	Children();

	/**
	 * Constructor for up to 15 child nodes. Slightly unelegant, but in
	 * contraast to a solution using stdarg, no counting argument or sentinel
	 * are needed.
	 */
	Children(Node* n1, Node* n2 = 0, Node* n3 = 0, Node* n4 = 0, Node* n5 = 0,
			Node* n6 = 0, Node* n7 = 0, Node* n8 = 0, Node* n9 = 0, Node* n10 = 0,
			Node* n11 = 0, Node* n12 = 0, Node* n13 = 0, Node* n14 = 0, Node* n15 = 0);

	/**
	 * Default destructor
	 */
	virtual ~Children();
};

#endif /*CHILDREN_H_*/
