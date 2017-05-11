#include "Plane.h"

Plane::Plane(float edgeLength) {

	//Plane
	for(int i= 0; i<120; i+=12){
	points[i] = 0.5 * edgeLength; points[i+1] = 0.5 * edgeLength; points[i+2] = -0.5 * edgeLength;
	points[i+3] = -0.5 * edgeLength; points[i+4] = 0.5 * edgeLength; points[i+5] = -0.5 * edgeLength;
	points[i+6] = -0.5 * edgeLength; points[i+7] = 0.5 * edgeLength; points[i+8] = 0.5 * edgeLength;
	points[i+9] = 0.5 * edgeLength; points[i+10] = 0.5 * edgeLength; points[i+11] = 0.5 * edgeLength;
	}
}

void Plane::draw() {
	list<HierarchicalObject *>::iterator current;

    glPushMatrix();  // saves the current transformation
    glPushAttrib(GL_ALL_ATTRIB_BITS); // Saves attribute information (in case I change it...)
    if (stippledLine) {
		glLineStipple(1, linePattern);
		glEnable(GL_LINE_STIPPLE);
    }
    if (stippledPolygon) {
		glPolygonStipple(&polygonPattern[0]);
		glEnable(GL_POLYGON_STIPPLE);
    }
    glPolygonMode(GL_FRONT_AND_BACK, polygonStyle);
	glColor3fv(color);
	material.useMaterial();
    glMultMatrixd(currentTransform);  // Apply current object's transformation
	glBegin(GL_QUADS);
	for (int i = 0; i < 1200; i += 12) {
		glNormal3f(0,0,1);
		glVertex3f(points[i], points[i+1], points[i+2]);
		glNormal3f(0,1,0);
		glVertex3f(points[i+3], points[i+4], points[i+5]);
		glNormal3f(0,1,1);
		glVertex3f(points[i+6], points[i+7], points[i+8]);
		glNormal3f(1,0,0);
		glVertex3f(points[i+9], points[i+10], points[i+11]);
	}
    glEnd();

	glPopAttrib();
	drawSubObjects();
    glPopMatrix();
	glutPostRedisplay();
}


