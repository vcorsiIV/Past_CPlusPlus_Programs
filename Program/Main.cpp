// Victor Corsi
// Project 3
// 11/8/2013

#include <list>
#include <map>
#include "freeglut\include\GL\freeglut.h"
#include "HierarchicalObject.h"
#include "Material.h"
#include "Plane.h"
#include "Pyramid.h"
#include "Cube.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Texture_Obj.h"
#include "imageloader.h"
#include "MultiObj.h"
#include <string>
using namespace std;
/*
 *Used the format of the main program that was used for
 *the lab.
*/

// Angle of the camera
float angle=0.0f;

// Vector representing camera's direction
float lensx=1.0f, lensy=0.0f, lensz=1.0f;
// Position of the camera
float Camx=0.0f, Camy=12.75f, Camz=-119.0f;

//Key states (variables will be zero when not pressed to stop)
float deltaAngle	= 0.0f;
float deltaAngle2	= 0.0f;
float deltaMove		= 0;
float deltaMove2	= 0;
int xOrigin			= -1;

int height, width;

// compute frames/seconds
int frame;
long time, timebase;
char s[50];


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
			"greenx", 
			new Material(0.01, 0.09, 0.2, 
			         0.25, 0.38, 0.222, 
					 0.395, 0.611, 0.452, 
					 21.0)));
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

	Plane* world = new Plane(1.0);
	Cone* conePtr = new Cone(3.0);
	Cube* cubePtr = new Cube(3.0);
	Cylinder* cylinderPtr = new Cylinder(3.0);
	Pyramid* pyramidPtr =new Pyramid(3.0);
	Texture_Obj* TextPtr = new Texture_Obj(2.0);
	MultiObj* Tree = new MultiObj(3);
	MultiObj* Tree2 = new MultiObj(3);

	string materialNames[]={"brown", "emerald","cyan rubber","gold","brass","light violet","Custom","greenx"};
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

	for(float x = 1.0;x<2.0; x+=4){
		world = new Plane(40.0);
		world->setColor(0.561, 0.820, 0.631);
		world->translate(0.0f,0,0.0f);
		world->setPolygonMode(GL_FILL);
		currentMaterialPtr = materialList[materialNames[1]];
		world->setMaterial(*currentMaterialPtr);
		baseObjects.push_back((HierarchicalObject *)world);
	}
	for(float x= 0; x<1; x++){
		TextPtr =new Texture_Obj(1);
		TextPtr->translate(5.0,0.0,0.0);
		TextPtr->translate(0.0,27.0,0.0);
		TextPtr->translate(0.0,0.0,23);
		TextPtr->setPolygonMode(GL_FILL);
		baseObjects.push_back((HierarchicalObject *)TextPtr);
		TextPtr->rotate(25.0, -1.0, 0.5, 0.0);
	}
	for(float x = 0;x<45; x+=1){
		Tree =new MultiObj(0.5);
		int i = 10;
		int plotRandAx = rand() % i;
		int negAx = 0 - plotRandAx;
		int plotRandAz = rand() % i;
		int negAz = 0 - plotRandAz;
		Tree->translate(negAx,0.0,0.0);
		Tree->translate(0.0f,19.0f,0.0);
		Tree->translate(0.0,0.0,negAz);
		Tree->setPolygonMode(GL_FILL);
		currentMaterialPtr = materialList[materialNames[7]];
		Tree->setMaterial(*currentMaterialPtr);
		baseObjects.push_back((HierarchicalObject *)Tree);
	}
	for(float x = 0;x<70; x+=1){
		Tree2 =new MultiObj(1.0);
		int i = 10;
		int plotRandBx = rand() % i;
		int plotRandBz = rand() % i;
		Tree2->translate(plotRandBx,0.0,0.0);
		Tree2->translate(0.0,19.0,0.0);
		Tree2->translate(0.0,0.0, plotRandBz);
		Tree2->setPolygonMode(GL_FILL);
		currentMaterialPtr = materialList[materialNames[7]];
		Tree2->setMaterial(*currentMaterialPtr);
		baseObjects.push_back((HierarchicalObject *)Tree2);
	}
	for(float x = -14.0;x<10.0; x+=4){
		cylinderPtr =new Cylinder(2.0);
		cylinderPtr->setColor((-x+9.0)/20.0, (0.7*x), (2-x)/20.0);
		cylinderPtr->translate(5,0,0);
		cylinderPtr->translate(0,19,0);
		cylinderPtr->translate(-x,(x+3),0);
		cylinderPtr->setPolygonMode(GL_FILL);
		currentMaterialPtr = materialList[materialNames[0]];
		cylinderPtr->setMaterial(*currentMaterialPtr);
		baseObjects.push_back((HierarchicalObject *)cylinderPtr);
		cylinderPtr->rotate(82.0, (2*x), (-3.0/x), 6.0);
	}
	for(float x = -9.0;x<10.0; x+=19.0){
		conePtr =new Cone(.25);
		conePtr->setColor((-x+9.0)/20.0, 0.7, (2-x)/20.0);
		conePtr->translate(5.0,20.0,0.0);
		conePtr->translate(0.0,0.0,-114);
		conePtr->setPolygonMode(GL_FILL);
		currentMaterialPtr = materialList[materialNames[5]];
		conePtr->setMaterial(*currentMaterialPtr);
		baseObjects.push_back((HierarchicalObject *)conePtr);
		conePtr->rotate(25.0, -1.0, 0.5, 0.0);
	}
	for(float x = -180.0;x<180.0; x+=0.6){
		cubePtr =new Cube(3.0);
		cubePtr->setColor((-x+9.0)/20.0, (0.7*x), (2-x)/20.0);
		cubePtr->translate(x-(x*5),x*5,0.0);
		cubePtr->translate(0.0,30,0.0);
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
		pyramidPtr->translate(0.0,19,20.0);
		pyramidPtr->setPolygonMode(GL_FILL);
		currentMaterialPtr = materialList[materialNames[currentMaterial]];
		currentMaterial++;
		pyramidPtr->setMaterial(*currentMaterialPtr);
		baseObjects.push_back((HierarchicalObject *)pyramidPtr);
	}

}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(
		float x,
		float y,
		float z,
		void *font,
		char *string) {

	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
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

	gluLookAt(Camx, Camy, Camz, lensx, lensy, lensz, 0.0f, 1.0f, 0.0f);
	
	for(int x=0; x< 100; x++){
		if (x>0){
		Camx += 0.001;
		Camz += 0.023;
		lensx += 0.00025;
		lensz += 0.0016;
		glutPostRedisplay();
		}
		if (x>5){
		Camx += 0.0001;
		Camz += 0.0023;
		lensx += 0.0025;
		lensz += 0.0016;
		glutPostRedisplay();
		}
		if (x>15){
		Camx -= 0.001;
		Camz -= 0.00023;
		lensx -= 0.0025;
		lensz -= 0.00016;
		glutPostRedisplay();
		}
		if (x>31){
		Camx -= 0.0003;
		lensx += .000009;
		lensy -= 0.000003;
		glutPostRedisplay();
		}
		if (x>72){
		Camx += .00009;
		lensx = 0.000003;
		Camz += .00009;
		lensz +=0.000003;
		glutPostRedisplay();
		}

		Camx= Camx;
		Camy= Camy;
		Camz= Camz;
		lensx= lensx;
		lensy= lensy;
		lensz= lensz;
		glutPostRedisplay();
	}
	

	if (baseObjects.size() > 0) {
		for (current = baseObjects.begin(); 
			 current != baseObjects.end(); 
			 current++) {
				(*current)->draw();
		}
	}

	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();

	restorePerspectiveProjection();

	glutSwapBuffers();
	return;
}

void reshape(int width, int height){
    double aspectRatio;
    const double windowSize = 25.6;
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
			-1000000.0, 10000.0);
    } else {
		glOrtho(-windowSize*aspectRatio, windowSize*aspectRatio,
			-0.5*windowSize, 1.5*windowSize,
			-1000000.0, 10000.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

/*
 * The only one currently recognized is 'Q' or 'q' for quit.
 * Will be used in project 3 for moving and rotating view.
 */

void keypress(unsigned char key, int x, int y) {

	if (key == 'q' || key == 'Q') {
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
