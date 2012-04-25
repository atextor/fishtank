/* Scene.h
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

#ifndef SCENE_H_
#define SCENE_H_
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <iomanip>
#include <cstdlib>
#include <GL/glut.h>
#include "Object.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"
#include "Children.h"
#include "Material.h"
#include "Vector.h"
#include "Animation.h"
#include "Text.h"
#include "Fish.h"
#include "Shark.h"
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::list;
using std::ostringstream;
using std::setw;
using std::setfill;

/**
 * Represents the scene. Initialises the graphic output, registers callback
 * functions and regularly draws the scene graph
 */
class Scene {
public:
	static Object* namedObject;

	/**
	 * Method to start the graphics system
	 */
	static Scene* init(int width, int height, string title, bool fullscreen = false);

	/**
	 * Add new node to the scene graph
	 */
	void addNode(Node* nde);

	/**
	 * Add new fish to the scene graph
	 */
	void addFish(Fish* nde);

	/**
	 * Add new shark to the scene graph
	 */
	void addShark(Shark* nde);

	/**
	 * Starts the glutMainLoop
	 */
	virtual void run();

	/**
	 * Default destructor. If the screen resolution was switch, the native
	 * resolution is restored here.
	 */
	virtual ~Scene();

private:
	/**
	 * Writes a screen show file with consecutive file name
	 */
	static void screenshot();

	/**
	 * Is the scene running in full screen?
	 */
	bool fullscreen;

	/**
	 * Should fish names be drawn?
	 */
	static bool drawNames;

	/**
	 * Should the help be drawn?
	 */
	static bool drawHelp;

	/**
	 * Should TGA files be written?
	 */
	static bool tgaWriter;

	/**
	 * Is the maximum number of fish being calculated right now?
	 */
	static bool calculateFishCount;

	/**
	 * Is the scene paused?
	 */
	static bool paused;

	/**
	 * Maxiumum number of fish before the FPS drop below 10
	 */
	static int maxFishCount;

	/**
	 * Text object for FPS display
	 */
	static Text* fpsDisplay;

	/**
	 * Text object for display of help text
	 */
	static list<Text*> helpDisplay;

	/**
	 * Counts number of frames
	 */
	static int frames;

	/**
	 * The currently selected camera
	 */
	static int activeCam;

	/**
	 * Attenuation for the glowing fish
	 */
	static float attenuation;

	/**
	 * Is the top light switched on?
	 */
	static bool topLight;

	/**
	 * Stores static camera positions
	 */
	static Vector* camPos[4];

	/**
	 * The singleton instance
	 */
	static Scene* singleton;

	/**
	 * The scene graph
	 */
	static Children* graph;

	/**
	 * The list of fish in the scene graph.
	 */
	static Children* fishList;

	/**
	 * The list of sharks in the scene graph
	 */
	static Children* sharkList;

	/**
	 * Constructor for the singleton object
	 */
	Scene(int width, int height, string title, bool fullscreen = false);

	/**
	 * Switches to the next camera
	 */
	static void nextCam();

	/**
	 * Callback method for glutTimerFunc
	 */
	static void timer(int id);

	/**
	 * Callback method for counting FPS
	 */
	static void fpsTimer(int id);

	/**
	 * Callback method for glutDisplayFunc
	 */
	static void display();

	/**
	 * Callback methode for glutReshapeFunc
	 */
	static void reshapeHandler(int w, int h);

	/**
	 * Callback method for glutKeyboardFunc
	 */
	static void keyboardDownHandler(unsigned char key, int x, int y);

	/**
	 * Callback method for glutKeyboardUpFunc
	 */
	static void keyboardUpHandler(unsigned char key, int x, int y);

	/**
	 * Callback method for glutMouseFunc
	 */
	static void mouseHandler(int button, int state, int u, int v);
};

#endif /*SCENE_H_*/
