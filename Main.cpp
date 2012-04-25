/* Main.cpp
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

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Scene.h"
#include "Fish.h"
#include "Shark.h"
#include "Box.h"
#include "Material.h"
#include "Children.h"
#include "config.h"
using std::cout;
using std::endl;
using std::ostringstream;

static Scene* scene = 0;

int main(int argc, char *argv[]) {
	scene = Scene::init(width, height, "Fishtank");
	Textures::init();

	// Materials
	// -----------------------------------------------------------------------
	Material* glow = material();
	glow->setEmissiveColor(color(1.0, 1.0, 1.0));
	glow->setDiffuseColor(color(1.0, 1.0, 1.0));

	Material* wood = material();
	wood->setTexture(Textures::WOOD1);
	wood->setDiffuseColor(color(0.8, 0.5, 0.3));

	Material* wood2 = material();
	wood2->setTexture(Textures::WOOD2);
	wood2->setDiffuseColor(color(0.8, 0.5, 0.3));

	Material* glass = material();
	glass->setDiffuseColor(color(0.0, 0.58, 1.0, 0.1));

	Material* sand = material();
	sand->setTexture(Textures::SAND);
	sand->setDiffuseColor(color(1.0, 1.0, 1.0));

	Material* plant = material();
	plant->setTexture(Textures::PLANT);
	plant->setDiffuseColor(color(1.0, 1.0, 1.0));

	Material* lamp = material();
	lamp->setTexture(Textures::ENVMAP);
	lamp->setDiffuseColor(color(1.0, 1.0, 1.0));

	// Fish
	// -----------------------------------------------------------------------
	int fishCount = 20;
	srand((unsigned)time(0));
	for (int i = 1; i <= fishCount; i++) {
		Material* mat;
		if (i == 1) {
			mat = glow;
		} else {
			mat = material();
			*mat = *Material::getFishMaterial();
		}
		ostringstream name;
		name << "Fish " << i;
		int x = (rand() % ((int)tankWidth - 50))-((int)tankWidth/2);
		int y = (rand() % ((int)tankHeight - 50))-((int)tankHeight/2);
		int z = (rand() % ((int)tankDepth - 10))-((int)tankDepth/2);
		scene->addFish(new Fish(mat, new Text(name.str(), 1.2),
			new Vector(x, y, z), new Vector(-i, 0, 0)));
	}
	Material *sharkmat = material();
	sharkmat->setDiffuseColor(color(0.3, 0.3, 0.3));
	scene->addShark(new Shark(sharkmat, new Text("Shark", 1.2),
		new Vector(1, 0, 0), new Vector(-1, 0, 0)));

	// Table
	// -----------------------------------------------------------------------
	Box* leg = box(40.0, 600.0, 40.0, wood);
	Node* table =
	translation(
		0, -120, 0,
		children(
			box(1000.0, 20.0, 500.0, wood),
			translation(
				0.0, -20.0, 0.0,
				box(920.0, 20.0, 420.0, wood)
			),
			translation(
				-440, -330, 190,
				leg
			),
			translation(
				440, -330, -190,
				leg
			),
			translation(
				-440, -330, -190,
				leg
			),
			translation(
				440, -330, 190,
				leg
			)
		)
	);

	// Fish tank
	// -----------------------------------------------------------------------
	Box* pillar = box(15.0, 240.0, 15.0, wood2);
	Box* topVBar = box(tankWidth - 15.0, 15.0, 15.0, wood2);
	Box* topHBar = box(15.0, 15.0, tankDepth - 15.0, wood2);
	Node* fishtank =
	children(
		// floor
		translation(
			0, -103, 0,
			box(tankWidth + 60.0, 15.0, tankDepth + 40.0, wood2)
		),
		// pillar
		translation(
			-tankWidth / 2, 10, -tankDepth / 2,
			pillar
		),
		translation(
			tankWidth / 2, 10, -tankDepth / 2,
			pillar
		),
		translation(
			-tankWidth / 2, 10, tankDepth / 2,
			pillar
		),
		translation(
			tankWidth / 2, 10, tankDepth / 2,
			pillar
		),
		// upper edges
		translation(
			0, 122, -tankDepth / 2,
			topVBar
		),
		translation(
			0, 122, tankDepth / 2,
			topVBar
		),
		translation(
			-tankWidth / 2, 122, 0,
			topHBar
		),
		translation(
			tankWidth / 2, 122, 0,
			topHBar
		),
		// glowing sphere
		translation(
			0, 200, 0,
			sphere(50, 20, lamp)
		),
		// plant picture
		translation(
			0, 0, -tankDepth / 2 - 10,
			box(tankWidth, 230.0, 1, plant)
		),
		// sand floor
		translation(
			0, -95, 0,
			box(tankWidth, 1.0, tankDepth, sand)
		),
		// water
		translation(
			0, 0, 0,
			box(tankWidth, 200.0, tankDepth, glass)
		)
	);

	// Add objects to scene
	// -----------------------------------------------------------------------
	scene->addNode(table);
	scene->addNode(fishtank);

	scene->run();
	return 0;
}
