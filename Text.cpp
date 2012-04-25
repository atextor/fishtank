/* Text.cpp
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

#include "Text.h"

list<Text*> Text::texts;

Text::Text(int x, int y, string text, float scale):x(x),y(y),text(text),scale(scale) {
	texts.push_back(this);
	enabled = true;
}

Text::Text(string text, float scale):x(0),y(0),text(text),scale(scale) {
	texts.push_back(this);
	enabled = true;
}

void Text::drawAll() {
	glLoadIdentity();
	for (list<Text*>::iterator it = texts.begin(); it != texts.end(); it++) {
		if ((*it)->enabled) {
			Textures::print((*it)->x, (*it)->y, (*it)->text.c_str(), (*it)->scale);
		}
	}
}

void Text::draw() {
	if (enabled) {
		Textures::print(x, y, text.c_str(), scale);
	}
}

void Text::setEnabled(bool enabled) {
	this->enabled = enabled;
}

void Text::setCoords(int x, int y) {
	this->x = x;
	this->y = y;
}

void Text::setText(string text) {
	this->text = text;
}

Text::~Text() {
	list<Text*>::iterator it2;
	for (list<Text*>::iterator it = texts.begin(); it != texts.end(); it++) {
		if ((*it) == this) {
			it2 = it;
			break;
		}
	}
	texts.erase(it2);
}
