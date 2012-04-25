/* Textures.h
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

#ifndef TEXTURES_H_
#define TEXTURES_H_
#include <string>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <GL/glut.h>
#include "config.h"
using std::string;
using std::cout;
using std::cerr;

#define NUMTEX 6

/**
 * Class for loading and managing textures, and drawing text.
 */
class Textures {
private:
	/**
	 * Display list for font output
	 */
	static GLuint fontbase;

	/**
	 * Texture array
	 */
	static GLuint tex[NUMTEX];

	/**
	 * Loads a texture in .bmp format into a number of the texture array
	 */
	static void loadTexture(string &filename, int number);

	/**
	 * Builds the display list for font output from the texture
	 */
	static void buildFont();

	/**
	 * Draw text. Coordinates and scaling are relative to the resolution set
	 * in config.h The lower left corner has coordinates (0, 0), the uppper
	 * right corner has (800, 600).
	 */
	static void glPrint(GLint x, GLint y, const char* string, float scale);

	/**
	 * Private default constructor: All actual functions are class methods
	 */
	Textures();

public:
	/**
	 * Texture constant
	 */
	static int FONT;

	/**
	 * Texture constant
	 */
	static int WOOD1;

	/**
	 * Texture constant
	 */
	static int WOOD2;

	/**
	 * Texture constant
	 */
	static int SAND;

	/**
	 * Texture constant
	 */
	static int PLANT;

	/**
	 * Texture constant
	 */
	static int ENVMAP;

	/**
	 * Load textures and build font
	 */
	static void init();

	/**
	 * Activate a texture from the array
	 */
	static void select(int t);

	/**
	 * Wrapper method for text output: Automatically draw the text shadow as
	 * well
	 */
	static void print(GLint x, GLint y, const char* string, float scale);

	/**
	 * Default destructor
	 */
	virtual ~Textures();
};

#endif /*TEXTURES_H_*/
