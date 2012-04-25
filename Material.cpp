/* Material.cpp
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

#include "Material.h"


Material* Material::lastUsed = 0;
Material* Material::defaultMat = createDefaultMaterial();
Material* Material::fishMat = createFishMaterial();
bool Material::enabled = true;

Material* Material::createDefaultMaterial() {
	Material* result = material();
	result->setTexture(-1);
	result->setDiffuseColor(color(0.0, 0.0, 0.0));
	return result;
}

Material* Material::getDefaultMaterial() {
	return defaultMat;
}

Material* Material::createFishMaterial() {
	Material* result = material();
	result->setTexture(-1);
	result->setDiffuseColor(color(0.0, 0.58, 1.0));
	return result;
}

Material* Material::getFishMaterial() {
	return fishMat;
}

void Material::select() {
	if (!enabled) {
		return;
	}

	if (lastUsed != this) {
		lastUsed = this;
		if (texture >= 0) {
		    glEnable(GL_TEXTURE_2D);
			Textures::select(texture);
		} else {
		    glDisable(GL_TEXTURE_2D);
		}
		if (diffuseColor != 0) {
			glColor4d(diffuseColor->x, diffuseColor->y,
					diffuseColor->z, diffuseColor->w);
			GLfloat tmp[] = {
				static_cast<GLfloat>(diffuseColor->x),
				static_cast<GLfloat>(diffuseColor->y),
				static_cast<GLfloat>(diffuseColor->z), 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tmp);
			if (diffuseColor->w != 1.0) {
				glEnable(GL_BLEND);
			} else {
				glDisable(GL_BLEND);
			}
		} else {
			glColor4d(1.0, 1.0, 1.0, 1.0);
		}

		if (emissiveColor != 0) {
			GLfloat tmp[] = {
				static_cast<GLfloat>(emissiveColor->x),
				static_cast<GLfloat>(emissiveColor->y),
				static_cast<GLfloat>(emissiveColor->z), 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, tmp);
		} else {
			GLfloat tmp[] = {0.0, 0.0, 0.0, 1.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, tmp);
		}

	}
}

void Material::setEnabled(bool enabled) {
	Material::enabled = enabled;
}

void Material::setDiffuseColor(Color* c) {
	diffuseColor = c;
}

void Material::setAmbientColor(Color* c) {
	ambientColor = c;
}

void Material::setEmissiveColor(Color* c) {
	emissiveColor = c;
}

void Material::setspecularColor(Color* c) {
	specularColor = c;
}

void Material::setShininess(double d) {
	shininess = d;
}

void Material::setTexture(int t) {
	texture = t;
}

Color* Material::getDiffuseColor() {
	return diffuseColor;
}

Color* Material::getAmbientColor() {
	return ambientColor;
}

Color* Material::getEmissiveColor() {
	return emissiveColor;
}

Material::Material() {
	diffuseColor = 0;
	ambientColor = 0;
	emissiveColor = 0;
	specularColor = 0;
	shininess = 0;
	texture = -1;
}

Material::~Material() {
	delete defaultMat;
	delete fishMat;
	if (lastUsed == this) {
		lastUsed = 0;
	}
}
