/* Children.cpp
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

#include "Children.h"

Children::Children() {
}

/*
Children::Children(Node *n1, ...) {
	int count = 0;
	Node *n = 0;
	va_list parameter;
	va_start(parameter, n1);

	do {
		count++;
		n = va_arg(parameter, Node*);
		children.push_back(n);
	} while(n != 0);
	va_end(parameter);
	cout << "parameter: " << count << "\n";
}
*/

void Children::work() {
	for (list<Node*>::iterator it = children_.begin();
			it != children_.end(); it++) {
		glPushMatrix();
		(*it)->work();
		glPopMatrix();
	}
}

void Children::removeNode() {
	if (children_.size() >= 1) {
		Node* back = children_.back();
		children_.pop_back();
		delete back;
	}
}

int Children::size() {
	return children_.size();
}

Node* Children::getNode(int index) {
	int i = 0;
	for (list<Node*>::iterator it = children_.begin(); it != children_.end(); it++) {
		if (i == index) {
			return *it;
		}
		i++;
	}	
	return NULL;
}

Children::Children(Node* n1, Node* n2, Node* n3, Node* n4, Node* n5, Node* n6,
		Node* n7, Node* n8, Node* n9, Node* n10, Node* n11, Node* n12, Node* n13,
		Node* n14, Node* n15) {
	children_.push_back(n1);
	if (n2 != 0) children_.push_back(n2);
	if (n3 != 0) children_.push_back(n3);
	if (n4 != 0) children_.push_back(n4);
	if (n5 != 0) children_.push_back(n5);
	if (n6 != 0) children_.push_back(n6);
	if (n7 != 0) children_.push_back(n7);
	if (n8 != 0) children_.push_back(n8);
	if (n9 != 0) children_.push_back(n9);
	if (n10 != 0) children_.push_back(n10);
	if (n11 != 0) children_.push_back(n11);
	if (n12 != 0) children_.push_back(n12);
	if (n13 != 0) children_.push_back(n13);
	if (n14 != 0) children_.push_back(n14);
	if (n15 != 0) children_.push_back(n15);
}

void Children::addNode(Node* nde) {
	children_.push_back(nde);
}

Children::~Children() {
	// Destroy child brachnes of node as well
	for (list<Node*>::iterator it = children_.begin();
			children_.size() > 0; it = children_.begin()) {
		delete(*it);
		children_.erase(it);
	}
}
