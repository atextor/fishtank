/* Text.h
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

#ifndef TEXT_H_
#define TEXT_H_
#include <list>
#include <string>
#include <cstdlib>
#include <GL/glut.h>
#include "Textures.h"
using std::list;
using std::string;

/**
 * Text object that has a text, a scaling and a 2d position
 */
class Text {
private:
	/**
	 * x coordinate
	 */
	int x;

	/**
	 * y coordinate
	 */
	int y;

	/**
	 * Text to display
	 */
	string text;

	/**
	 * Scaling (font size)
	 */
	float scale;

	/**
	 * Should this text be drawn?
	 */
	bool enabled;

	/**
	 * Static list of all text objects
	 */
	static list<Text*> texts;

public:
	/**
	 * Constructor with coordinates, text and optional scaling
	 */
	Text(int x, int y, string text, float scale = 1.0);

	/**
	 * Constructor with text and optional scaling
	 */
	Text(string text, float scale = 1.0);

	/**
	 * Change coordinates
	 */
	void setCoords(int x, int y);

	/**
	 * Switches the text on or off 
	 */
	void setEnabled(bool enabled);

	/**
	 * Change text
	 */
	void setText(string text);

	/**
	 * Draw all text objects
	 */
	static void drawAll();

	/**
	 * Draw this text object
	 */
	void draw();

	/**
	 * Default destructor
	 */
	virtual ~Text();
};

#endif /*TEXT_H_*/
