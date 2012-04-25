/* Material.h
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

#ifndef MATERIAL_H_
#define MATERIAL_H_
#include <iostream>
#include <cstdlib>
#include <GL/glut.h>
#include "Textures.h"
#include "Vector.h"
using std::cout;
#define material new Material

/**
 * Represents a material. This is used by objects. A class variable stores the
 * last used material to only select/activate it when necessary.
 */
class Material {
private:
	/**
	 * Default material: black/matte
	 */
	static Material* defaultMat;

	/**
	 * Fish material
	 */
	static Material* fishMat;

	/**
	 * Stores the last used material to prevent unnecessary select calls
	 */
	static Material* lastUsed;

	/**
	 * Controls if materials should be used
	 */
	static bool enabled;

	/**
	 * Diffuse color of the material
	 */
	Color* diffuseColor;

	/**
	 * Ambient color of the material
	 */
	Color* ambientColor;

	/**
	 * Emissive color of the material
	 */
	Color* emissiveColor;

	/**
	 * Specular color of the material
	 */
	Color* specularColor;

	/**
	 * Shininess of the material
	 */
	double shininess;

	/**
	 * Number of the texture. -1 for no texture
	 */
	int texture;

	/**
	 * Creates the standard material
	 */
	static Material* createDefaultMaterial();

	/**
	 * Creates the fish material
	 */
	static Material* createFishMaterial();

public:
	/**
	 * Default constructor
	 */
	Material();

	/**
	 * Returns the default material
	 */
	static Material* getDefaultMaterial();

	/**
	 * Returns the fish material
	 */
	static Material* getFishMaterial();

	/**
	 * Should materials be selectable?
	 */
	static void setEnabled(bool enabled);

	/**
	 * Returns the ambient color
	 */
	Color* getAmbientColor();

	/**
	 * Returns the diffuse color
	 */
	Color* getDiffuseColor();

	/**
	 * Returns the emissive color
	 */
	Color* getEmissiveColor();

	/**
	 * Sets the diffuse color
	 */
	virtual void setDiffuseColor(Color* c);

	/**
	 * Sets the ambient color
	 */
	virtual void setAmbientColor(Color* c);

	/**
	 * Sets the emissive color
	 */
	virtual void setEmissiveColor(Color* c);

	/**
	 * Sets the specular color
	 */
	virtual void setspecularColor(Color* c);

	/**
	 * Sets the shininess value
	 */
	virtual void setShininess(double d);

	/**
	 * Sets the texture number. -1 for no texture
	 */
	virtual void setTexture(int t);

	/**
	 * Activates the material
	 */
	virtual void select();

	/**
	 * Default destructor
	 */
	virtual ~Material();
};

#endif /*MATERIAL_H_*/
