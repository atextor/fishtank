/* Textures.cpp
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

#include "Textures.h"

static string filenames[NUMTEX] = {
	"font.bmp",
	"table.bmp",
	"fishtank.bmp",
	"sand.bmp",
	"plant.bmp",
	"envmap.bmp"
};
GLuint Textures::tex[NUMTEX];
GLuint Textures::fontbase;

int Textures::FONT = 0;
int Textures::WOOD1 = 1;
int Textures::WOOD2 = 2;
int Textures::SAND = 3;
int Textures::PLANT = 4;
int Textures::ENVMAP = 5;

void Textures::loadTexture(string &filename, int number) {
#ifdef WIN32
	errno_t err;
#endif
	FILE *file;
	// Image size in byte
	unsigned long size;
	size_t i;
	unsigned short int planes;
	unsigned short int bpp;
	// Dimensions in pixels
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
	char temp;

	// Open file
#ifdef WIN32
	if ((err = fopen_s(&file, filename.c_str(), "rb"))) {
#else
	if ((file = fopen(filename.c_str(), "rb")) == NULL) {
#endif
		cerr << "loadTexture: File not found: " << filename << "\n";
		return;
	}

	// Seed width/height in bitmap header
	fseek(file, 18, SEEK_CUR);

	// Read width
	if ((i = fread(&sizeX, 4, 1, file)) != 1) {
		cerr << "loadTexture: Could not read width: " << filename << "\n";
		return;
	}

	// Read height
	if ((i = fread(&sizeY, 4, 1, file)) != 1) {
		cerr << "loadTexture: Could not read height: " << filename << "\n";
		return;
	}

	// Calculate size: 3bpp
	size = sizeX * sizeY * 3;

	// Read planes (must be 1)
	if (((fread(&planes, 2, 1, file)) != 1) || (planes != 1)) {
		cerr << "loadTexture: Error when reading planes: " << filename << "\n";
		return;
	}

	// Read Bpp (must be 24)
	if (((i = fread(&bpp, 2, 1, file)) != 1) || (bpp != 24)) {
		cerr << "loadTexture: Error when reading BPP: " << filename << "\n";
		return;
	}

	// Skip rest of header
	fseek(file, 24, SEEK_CUR);

	// Read pixel data
	if ((data = (char*)malloc(size)) == NULL) {
		cerr << "loadTexture: Not enough memory\n";
		return;
	}
	if ((i = fread(data, size, 1, file)) != 1) {
		cerr << "loadTexture: Error while reading data" << filename << "\n";
		return;
	}

	// Reverse: BMP is bgr, but we need rgb
	for (i = 0; i < size; i += 3) {
		temp = data[i];
		data[i] = data[i+2];
		data[i+2] = temp;
	}

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

	// Create texture
	glGenTextures(1, &tex[number]);
	glBindTexture(GL_TEXTURE_2D, tex[number]);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Texture size small -> bilinear filtering of fitting mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// Texture size big -> bilinear filtering of first mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Repeat textures
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Build mipmap: 3 color components, size, rgb, unsigned bytes and data
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, sizeX, sizeY, GL_RGB, GL_UNSIGNED_BYTE, data);

	// Don't need it any more
	free(data);
}

void Textures::select(int t) {
	glBindTexture(GL_TEXTURE_2D, tex[t]);
}

void Textures::init() {
	for (int i = 0; i < NUMTEX; i++) {
		loadTexture(filenames[i], i);
	}
	buildFont();
}

void Textures::buildFont() {
	double cx;
	double cy;
	double cinc = 0.0625;

	fontbase = glGenLists(256);
	glBindTexture(GL_TEXTURE_2D, tex[Textures::FONT]);
	for(GLuint loop = 0; loop < 256; loop++) {
		cx = (float)(loop % 16) / 16.0f;
		cy = (float)(loop / 16) / 16.0f;

		glNewList(fontbase + loop,GL_COMPILE);
			glBegin(GL_QUADS);
				glTexCoord2f(cx, 1 - cy - cinc);
				glVertex2i(0, 0);
				glTexCoord2f(cx + cinc, 1 - cy - cinc);
				glVertex2i(16, 0);
				glTexCoord2f(cx + cinc, 1 - cy);
				glVertex2i(16, 16);
				glTexCoord2f(cx, 1 - cy);
				glVertex2i(0, 16);
			glEnd();
			glTranslated(10, 0, 0);
		glEndList();
	}
}

void Textures::print (GLint x, GLint y, const char *string, float scale) {
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
	glPrint(x + (int)(2 * scale), y - (int)(2 * scale), string, scale);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glPrint(x, y, string, scale);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
}

void Textures::glPrint(GLint x, GLint y, const char *string, float scale) {
	int set = 0;

	scale = 1 / scale;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, (GLint)(width * scale), 0, (GLint)(height * scale), -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslated((GLint)(x * scale), (GLint)(y * scale), 0);
	glListBase(fontbase - 32 + (128 * set));
	glCallLists((GLsizei)strlen(string), GL_BYTE, string);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_BLEND);
}

Textures::Textures() {
}

Textures::~Textures() {
}
