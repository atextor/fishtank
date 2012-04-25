/* Scene.cpp
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

#include "Scene.h"

Scene* Scene::singleton = 0;
Children* Scene::graph = 0;
Children* Scene::fishList = 0;
Children* Scene::sharkList = 0;
Vector* Scene::camPos[4] = {
	new Vector(0.0, 100.0, 200.0),
	new Vector(0.0, 500.0, 1000.0),
	new Vector(0.0, 500.0, 0.1),
	new Vector(0.0, 100.0, 600.0)
};
int Scene::activeCam = 0;
int Scene::frames = 0;
Object* Scene::namedObject = 0;
Text* Scene::fpsDisplay = 0;
list<Text*> Scene::helpDisplay;
bool Scene::drawNames = false;
bool Scene::drawHelp = false;
bool Scene::calculateFishCount = false;
bool Scene::paused = false;
bool Scene::tgaWriter = false;
int Scene::maxFishCount = 0;
float Scene::attenuation = 0.0f;
bool Scene::topLight = true;

void Scene::display() {
	// Clear screen, initialise culling
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Select model view matrix
	glMatrixMode(GL_MODELVIEW);

	// Draw solid bodies
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glLoadIdentity();

	Fish* f = Fish::getFirst();
	Vector* v = f->getPosition();
	GLfloat lightPos[] = { static_cast<GLfloat>(v->x),
		static_cast<GLfloat>(v->y - 10), static_cast<GLfloat>(v->z), 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// args 1-3: viewer coordinates,
	// args 4-5: point looked at,
	// args 7-9: "up" vector
	gluLookAt(
		camPos[activeCam]->x, camPos[activeCam]->y, camPos[activeCam]->z,
		0.0, 20.0, 0.0,
		0.0, 1.0, 0.0);

	// Draw scene graph
	fishList->work();
	if (!calculateFishCount) {
		sharkList->work();
	}
	graph->work();

	if (drawNames) {
		Text::drawAll();
	} else {
		fpsDisplay->draw();
		for (list<Text*>::iterator it = helpDisplay.begin(); it != helpDisplay.end(); it++) {
			(*it)->draw();
		}
	}

	glFlush();
	glutSwapBuffers();

	if (calculateFishCount) {
		glutPostRedisplay();
	}
	frames++;
}

void Scene::timer(int id) {
	static unsigned long ticks = -1;
	ticks++;
	if (!paused) {
		Animation::nextTick(ticks);
		if (!Fish::moveAll()) {
			fishList->removeNode();
			for (int i = 0; i < sharkList->size(); i++) {
				((Shark*)sharkList->getNode(i))->nextTarget();
			}
		}

		if (!calculateFishCount) {
			glutPostRedisplay();
		}
	}

	if (tgaWriter) {
		screenshot();
	}

	// Reset timer
	glutTimerFunc(40, timer, 1);
}

void Scene::fpsTimer(int d) {
	ostringstream out;
	ostringstream name;
	out << "FPS: " << frames << "  Max. fish: ";
	if (calculateFishCount) {
		if (frames > 10) {
			for (int i = 1; i <= 15; i++) {
				maxFishCount++;
				name << "Fish " << maxFishCount;
				int x = (rand() % ((int)tankWidth - 50))-((int)tankWidth/2);
				int y = (rand() % ((int)tankHeight - 50))-((int)tankHeight/2);
				int z = (rand() % ((int)tankDepth - 10))-((int)tankDepth/2);
				fishList->addNode(new Fish(Material::getFishMaterial(),
					new Text(name.str(), 1.2), new Vector(x, y, z), new Vector(-i, 0, 0)));
			}
			out << "calculating... (" << maxFishCount << " Fish)";
		} else {
			calculateFishCount = false;
			while (fishList->size() > 7) {
				fishList->removeNode();
			}
			out << maxFishCount;
		}
	} else {
		if (maxFishCount == 0) {
			out << "(unknown)";
		} else {
			out << maxFishCount;
		}
	}
	fpsDisplay->setText(out.str());
	glutTimerFunc(1000, fpsTimer, 1);
	frames = 0;
}


void Scene::reshapeHandler(int w, int h) {
	GLint x = 0;
	GLint y = 0;
	// Set perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, w / h, 0.1, 10000.0);
	glViewport(x, y, w, h);
}

void Scene::nextCam() {
	activeCam++;
	if (activeCam == 4)
		activeCam = 0;
}

void Scene::keyboardDownHandler(unsigned char key, int x, int y) {
	Material* m;
	double a;
	switch ((int)key) {
		case 32: // Space - next camera
			nextCam();
			break;
		case 27: // Escape - Quit
			exit(EXIT_SUCCESS);
		case 43: // + - Glowing fish lighter
			if (attenuation >= -0.1) {
				attenuation -= 0.1;
			    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, attenuation);
			    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
				glLighti(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
			}
			m = Fish::getFirst()->getMaterial();
			a = 1 - (attenuation / 3.0);
			m->getEmissiveColor()->set(a, a, a);
			break;
		case 45: // - - Glowing fish darker
			if (attenuation <= 2.9) {
				attenuation += 0.1;
			    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, attenuation);
			    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
				glLighti(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
			}
			m = Fish::getFirst()->getMaterial();
			a = 1 - (attenuation / 3.0);
			m->getEmissiveColor()->set(a, a, a);
			break;
		case 102: // f - Start max fish count test
			if (!calculateFishCount) {
				calculateFishCount = true;
				maxFishCount = fishList->size();
				while (sharkList->size() > 0) {
					sharkList->removeNode();
				}
				glutPostRedisplay();
			}
			break;
		case 110: // n - Toggle names
			drawNames = !drawNames;
			break;
		case 104: // h - Toggle help
			drawHelp = !drawHelp;
			for (list<Text*>::iterator it = helpDisplay.begin(); it != helpDisplay.end(); it++) {
				(*it)->setEnabled(drawHelp);
			}
			break;
		case 111: // o - Move camera z up
			camPos[activeCam]->y += 5.0;
			break;
		case 108: // l - Move camera z down
			camPos[activeCam]->y -= 5.0;
			break;
		case 116: // t - Toggle top light
			topLight = !topLight;
			if (topLight) {
				glEnable(GL_LIGHT1);
			} else {
				glDisable(GL_LIGHT1);
			}
			break;
		case 49: {  // 1 - Add fish
			ostringstream name;
			name << "Fish";
			int x = (rand() % ((int)tankWidth - 50))-((int)tankWidth/2);
			int y = (rand() % ((int)tankHeight - 50))-((int)tankHeight/2);
			int z = (rand() % ((int)tankDepth - 10))-((int)tankDepth/2);
			Material* mat = material();
			*mat = *Material::getFishMaterial();
			fishList->addNode(new Fish(mat, new Text(name.str(), 1.2),
				new Vector(x, y, z), new Vector(1, 0, 0)));
			for (int i = 0; i < sharkList->size(); i++) {
				((Shark*)sharkList->getNode(i))->nextTarget();
			}
			break;
		}
		case 50:  // 2 - Remove fish
			if (fishList->size() > 1) {
				fishList->removeNode();
				for (int i = 0; i < sharkList->size(); i++) {
					((Shark*)sharkList->getNode(i))->nextTarget();
				}
			}
			break;
		case 51: { // 3 - Add shark
			Material *sharkmat = material();
			sharkmat->setDiffuseColor(color(0.3, 0.3, 0.3));
			sharkList->addNode(new Shark(sharkmat, new Text("Shark", 1.2),
				new Vector(1, 0, 0), new Vector(-1, 0, 0)));
			break;
		}
		case 52:  // 4 - Remove shark
			sharkList->removeNode();
			break;
		case 112: // p - Pause
			paused = !paused;
			break;
		case 120: // x - Write TGAs
			tgaWriter = !tgaWriter;
			break;
		default:
			cout << "Key: " << (int)key << "\n";
			break;
	}
}

void Scene::keyboardUpHandler(unsigned char key, int x, int y) {
	switch ((int)key) {
		case 27:
			exit(EXIT_SUCCESS);
		default:
			break;
	}
}

void Scene::mouseHandler(int button, int state, int u, int v) {
	if(GLUT_LEFT == button && GLUT_DOWN == state) {
		nextCam();
	}
}

void Scene::run() {
	// Give control to GLUT
	glutMainLoop();

}

Scene *Scene::init(int width, int height, string title, bool fullscreen) {
	if (singleton == 0) {
		singleton = new Scene(width, height, title, fullscreen);
	} else {
		cerr << "Scene is already initialized!\n";
	}
	return singleton;
}

Scene::Scene(int width, int height, string title, bool fullscreen) {
	int dummyArgc = 1;
	this->fullscreen = fullscreen;
	graph = new Children;
	fishList = new Children;
	sharkList = new Children;

	// Start calls
	glutInit(&dummyArgc, NULL);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	if (fullscreen) {
		ostringstream mode;
		mode << width << "x" << height << ":16@60";
		glutGameModeString(mode.str().c_str());
		glutEnterGameMode();    } else {
	    glutInitWindowSize(width, height);
	    glutInitWindowPosition(100,0);
	    glutCreateWindow(title.c_str());
	}

	fpsDisplay = new Text(3, 3, "FPS:", 1.3);

	string helpText[] = {
		"Keys:",
		"H         - Toggle help",
		"Space     - Next camera",
		"Escape    - Quit",
		"P         - Pause",
		"X         - Write TGAs",
		"+         - Increase light of glowing fish",
		"-         - Decrease light of glowing fish",
		"F         - Calculate maximum number of fish",
		"N         - Toggle names",
		"O         - Move camera up",
		"L         - Move camera down",
		"T         - Toggle lamp",
		"1         - Add fish",
		"2         - Remove fish",
		"3         - Add shark",
		"4         - Remove shark"
	};
	for (int i = 0; i < 17; i++) {
	    helpDisplay.push_front(new Text(50, 360 - (18 * i), helpText[i], 1.1));
	    helpDisplay.front()->setEnabled(drawHelp);
	}

	// Register callbacks
	glutDisplayFunc(display);
	glutMouseFunc(mouseHandler);
	glutKeyboardFunc(keyboardDownHandler);
	glutKeyboardUpFunc(keyboardUpHandler);
	glutReshapeFunc(reshapeHandler);
	glutIdleFunc(NULL);

	// Visibility settings etc.
	glClearColor(0.4, 0.4, 0.4, 1.0);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);    // Kind of depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	// Light 0: Moving fish light
	GLfloat lightDiffuse[]= {1.0f, 1.0f, 1.0f};
	GLfloat light0Pos[] = {0.0f, 0.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.9f);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, attenuation);
	glEnable(GL_LIGHT0);

	// Light 2: Spot light
	GLfloat lightAmbient[]= {0.5f, 0.5f, 0.5f};
	GLfloat	lightPos[] = {0.0f, 250.0f, 0.0f, 1.0f};
	GLfloat spotDir[] = {0.0f, -100.0f, 0.0f};
	//GLfloat cutoff = 90.0f;
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
	//glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, &cutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1);
	if (topLight) {
	    glEnable(GL_LIGHT1);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 0.1f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLineWidth(2.5f);

	// Count FPS
	frames = 0;
	glutTimerFunc(1000, fpsTimer, 1);

	// Animation timer
	glutTimerFunc(40, timer, 1);
}

void Scene::addNode(Node* nde) {
	graph->addNode(nde);
}

void Scene::addFish(Fish* nde) {
	fishList->addNode(nde);
}

void Scene::addShark(Shark* nde) {
	sharkList->addNode(nde);
}

void Scene::screenshot() {
	static int num = 0;

	unsigned char* pixels;
	FILE * shot;
	int screenStats[4];

	glGetIntegerv(GL_VIEWPORT, screenStats);

	pixels = new unsigned char[screenStats[2] * screenStats[3] * 3];
	glReadPixels(0, 0, screenStats[2], screenStats[3], GL_BGR, GL_UNSIGNED_BYTE, pixels);

	ostringstream filename;
	filename << "shot" << setw(5) << setfill('0') << num << ".tga";
	if ((shot = fopen(filename.str().c_str(), "wb")) == NULL) {
		return;
	}

	// TGA Header
	unsigned char TGAheader[12]={0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// header[1]*256+header[0] - width
	// header[3]*256+header[2] - height
	// header[4] - bits per pixel
	// header[5] - ?
	unsigned char header[6] = {
		static_cast<unsigned char>((int)(screenStats[2] % 256)),
		static_cast<unsigned char>((int)(screenStats[2] / 256)),
		static_cast<unsigned char>((int)(screenStats[3] % 256)),
		static_cast<unsigned char>((int)(screenStats[3] / 256)), 24, 0
	};

	fwrite(TGAheader, sizeof(unsigned char), 12, shot);
	fwrite(header, sizeof(unsigned char), 6, shot);
	fwrite(pixels, sizeof(unsigned char), screenStats[2] * screenStats[3] * 3, shot);

	fclose(shot);
	delete [] pixels;
	num++;
}

Scene::~Scene() {
	// Quit fullscreen
	if (fullscreen) {
		glutLeaveGameMode();
	}
}
