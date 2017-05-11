// Victor Corsi
// Project 3
// 11/8/2013

#include <list>
#include <map>
#include "glut.h"
#include "HierarchicalObject.h"
#include "Material.h"
#include "MultiObj.h"
#include "Pyramid.h"
#include "Cube.h"
#include "Cone.h"
#include "Cylinder.h"
#include <string>
using namespace std;
/*
 *Used the format of the main program that was used for
 *the lab.
*/

list<HierarchicalObject *> baseObjects;
map<string, Material *> materialList;
void init();
void display();
void reshape(int, int);
void idle(int timer);
void initMaterials();

/*
 * initMaterials initializes the myMaterials map to contain some easy
 * materials for later use.
 */
void initMaterials() {
	/*
	 * Add Materials
	 */
	
	materialList.insert(
		pair<string,Material*>(
			string("black plastic"), 
			new Material(0.0, 0.0, 0.0, 
			         0.01, 0.01, 0.01, 
					 0.5, 0.5, 0.5, 
					 32.0)));
	materialList.insert(
		pair<string,Material*>(
			"cyan plastic", 
			new Material(0.0, 0.1, 0.06, 
			         0.0, 0.50980392, 0.50980392, 
					 0.50196078, 0.50196078, 0.50196078, 
					 32.0)));
	materialList.insert(
		pair<string,Material*>(
			"green plastic", 
			new Material(0.0, 0.0, 0.0, 
			         0.1, 0.35, 0.1, 
					 0.45, 0.55, 0.45, 
					 32.0)));
	materialList.insert(
		pair<string,Material*>(
			"cyan rubber", 
			new Material(0.0, 0.05, 0.05, 
			         0.4, 0.5, 0.5, 
					 0.04, 0.7, 0.04, 
					 10.0)));
	materialList.insert(
		pair<string,Material*>(
			"light violet",
			new Material(0.01476, 0.081665, 0.243105, 
			         0.65636, 0.442251, 0.591028, 
					 0.315168, 0.298329, 0.366683, 
					 28.0)));
	materialList.insert(
		pair<string,Material*>(
			"Custom",
			new Material(0.12076, 0.451665, 0.293105, 
			         0.894118*2, 0.819608*2, 0.427451*2, 
					 0.315168, 0.438329, 0.521683, 
					 90.0)));

	materialList.insert (
		pair<string, Material*>(
		"pearl", new Material(0.25, 0.20725, 0.20725, 
		                      1.0, 0.829, 0.829, 
							  0.296648, 0.296648, 0.29648,
							  0.088*128)));
	materialList.insert(
		pair<string, Material*> (
		"brass", new Material(0.32912, 0.223529, 0.027451,
		                      0.780392, 0.568627, 0.113725, 
							  0.027451, 0.113725, 0.807843, 
							  27.8974)));
	materialList.insert(
		pair<string, Material*>(
		"gold", new Material(0.24725, 0.1995, 0.0745, 0.75165, 0.60648, 0.22648, 0.628281, 0.555802, 0.366065, 51.2)));
	materialList.insert(
		pair<string, Material*>(
		"polished sliver", new Material(0.23125, 0.23125, 0.23125,
									    0.2775, 0.2775, 0.2775, 0.7739911, 0.7739911, 0.7739911, 89.6)));
	materialList.insert(
		pair<string, Material*>(
		"brown", new Material(0.095625/2, 0.03675/2, 0.01125/2, 0.3519/2, 0.13524/2, 0.0414/2, 0.1283885/2, 0.068811/2, 0.043007/2, 3.2)));
	materialList.insert(
		pair<string, Material*>(
		"emerald", new Material(0.215, 0.1745, 0.0215, 0.07568, 0.61424, 0.07568, 0.633, 0.727811, 0.633, 76.8)));

	return;
}

void init() {
	glClearColor(0.2, 0.4, 0.7, 0.7);
	glClearDepth(1.0);

	MultiObj* conePtr = new MultiObj(1.0);
	Cube* cubePtr = new Cube(3.0);
	Cylinder* cylinderPtr = new Cylinder(3.0);
	Pyramid* pyramidPtr =new Pyramid(3.0);

	string materialNames[]={"brown", "emerald","polished sliver","gold","brass","light violet","Custom"};
	int currentMaterial = 0;
	Material * currentMaterialPtr;

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	float position[]={0.0, 10.0, 15.0, 1.0};
	float ambient[] = {0.8, 0.3, 0.3, 1.0};
	float diffuse[] = {0.7, 0.8, 0.9, 1.0};
	float specular[] = {1.1, 1.5, 1.2, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);

	initMaterials();
	
	for(float x = -14.0;x<10.0; x+=4){
		cylinderPtr =new Cylinder(3.0);
		cylinderPtr->setColor((-x+9.0)/20.0, (0.7*x), (2-x)/20.0);
		cylinderPtr->translate(5,0,0);
		cylinderPtr->translate(-x,(x+3),0);
		cylinderPtr->setPolygonMode(GL_FILL);
		currentMaterialPtr = materialList[materialNames[0]];
		cylinderPtr->setMaterial(*currentMaterialPtr);
		baseObjects.push_back((HierarchicalObject *)cylinderPtr);
		cylinderPtr->rotate(82.0, (2*x), (-3.0/x), 6.0);
	}
	for(float x = -9.0;x<10.0; x+=19.0){
		conePtr =new MultiObj(1.0);
		conePtr->setColor((-x+9.0)/20.0, 0.7, (2-x)/20.0);
		conePtr->translate(5.0,0.0,0.0);
		conePtr->translate(0.0,0.0,(-x));
		conePtr->setPolygonMode(GL_FILL);
		currentMaterialPtr = materialList[materialNames[5]];
		conePtr->setMaterial(*currentMaterialPtr);
		baseObjects.push_back((HierarchicalObject *)conePtr);
	}
	for(float x = -180.0;x<180.0; x+=0.6){
		cubePtr =new Cube(3.0);
		cubePtr->setColor((-x+9.0)/20.0, (0.7*x), (2-x)/20.0);
		cubePtr->translate(x-(x*5),x*5,0.0);
		cubePtr->translate(cos(x),0.0,(x+20));
		cubePtr->setPolygonMode(GL_FILL);
		currentMaterialPtr = materialList[materialNames[6]];
		cubePtr->setMaterial(*currentMaterialPtr);
		baseObjects.push_back((HierarchicalObject *)cubePtr);
	}
	for(float x = -9.0;x<10.0; x+=3.0){
		pyramidPtr =new Pyramid(3.0);
		pyramidPtr->setColor((x+9.0)/20.0, 0.1, (10-x)/20.0);
		pyramidPtr->translate(x/2,0.0,(20.0/x-1));
		pyramidPtr->translate(0.0,(x+5)/1.5,20.0);
		pyramidPtr->setPolygonMode(GL_FILL);
		currentMaterialPtr = materialList[materialNames[currentMaterial]];
		currentMaterial++;
		pyramidPtr->setMaterial(*currentMaterialPtr);
		baseObjects.push_back((HierarchicalObject *)pyramidPtr);
	}
}

void display(){
	/*
	* Display all the items in the base list and let each object take care
	* of any of its own descendents.
	*/

	list<HierarchicalObject *>::iterator current;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (baseObjects.size() > 0) {
		for (current = baseObjects.begin(); 
			 current != baseObjects.end(); 
			 current++) {
				(*current)->draw();
		}
	}
	glutSwapBuffers();
	return;
}

void reshape(int width, int height){
    double aspectRatio;
    const double windowSize = 9.8;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	/*
	 * Compute the aspect ratio -- width/height
	 */
    aspectRatio = static_cast<double>(width) / static_cast<double>(height);
    
    if (width <= height) {
		glOrtho(-windowSize, windowSize, 
			-0.5 * windowSize, 1.5 * windowSize/aspectRatio, 
			-100.0, 100.0);
    } else {
		glOrtho(-windowSize*aspectRatio, windowSize*aspectRatio,
			-0.5*windowSize, 1.5*windowSize,
			-100.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

/*
 * The only one currently recognized is 'Q' or 'q' for quit.
 * Will be used in project 3 for moving and rotating view.
 */
void keypress(unsigned char key, int x, int y) {
	if (key == '+') {
		// Will be for looking up
	}
	else if (key == '-') {
		// Will be for looking down
	}
	else if (key == '[') {
		// Will be for looking left
	}
	else if (key == ']') {
		// Will be for looking right
	}
	else if (key == '8') {
		// Will be for moving forward
	}
	else if (key == '4') {
		// Will be for moving left
	}
	else if (key == '6') {
		// Will be for moving right
	}
	else if (key == '2'){
		// Will be for moving back
	}
	else if (key == 'q' || key == 'Q') {
		exit(0);
	}
}

int main (int argCount, char * argValues[]){

    glutInit(&argCount, argValues);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(900,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Project2: Cylinder, Cone, Cube, Pyramid");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keypress);
    glutMainLoop();
    return 0;
}
