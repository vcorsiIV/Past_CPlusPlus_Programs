#include "Cube.h"

float rotcube;

Cube::Cube(float edgeLength) {

	//Top of cube
	points[0] = 0.35 * edgeLength; points[1] = 0.35 * edgeLength; points[2] = -0.35 * edgeLength;
	points[3] = -0.35 * edgeLength; points[4] = 0.35 * edgeLength; points[5] = -0.35 * edgeLength;
	points[6] = -0.35 * edgeLength; points[7] = 0.35 * edgeLength; points[8] = 0.35 * edgeLength;
	points[9] = 0.35 * edgeLength; points[10] = 0.35 * edgeLength; points[11] = 0.35 * edgeLength;
	//Bottom of cube
	points[12] = 0.35 * edgeLength; points[13] = -0.35 * edgeLength; points[14] = 0.35 * edgeLength;
	points[15] = -0.35 * edgeLength; points[16] = -0.35 * edgeLength; points[17] = 0.35 * edgeLength;
	points[18] = -0.35 * edgeLength; points[19] = -0.35 * edgeLength; points[20] = -0.35 * edgeLength;
	points[21] = 0.35 * edgeLength; points[22] = -0.35 * edgeLength; points[23] = -0.35 * edgeLength;
	//Front
	points[24] = 0.35 * edgeLength; points[25] = 0.35 * edgeLength; points[26] = 0.35 * edgeLength;
	points[27] = -0.35 * edgeLength; points[28] = 0.35 * edgeLength; points[29] = 0.35 * edgeLength;
	points[30] = -0.35 * edgeLength; points[31] = -0.35 * edgeLength; points[32] = 0.35 * edgeLength;
	points[33] = 0.35 * edgeLength; points[34] = -0.35 * edgeLength; points[35] = 0.35 * edgeLength;
	//Back
	points[36] = 0.35 * edgeLength; points[37] = -0.35 * edgeLength; points[38] = -0.35 * edgeLength;
	points[39] = -0.35 * edgeLength; points[40] = -0.35 * edgeLength; points[41] = -0.35 * edgeLength;
	points[42] = -0.35 * edgeLength; points[43] = 0.35 * edgeLength; points[44] = -0.35 * edgeLength;
	points[45] = 0.35 * edgeLength; points[46] = 0.35 * edgeLength; points[47] = -0.35 * edgeLength;
	//Left side
	points[48] = -0.35 * edgeLength; points[49] = 0.35 * edgeLength; points[50] = 0.35 * edgeLength;
	points[51] = -0.35 * edgeLength; points[52] = 0.35 * edgeLength; points[53] = -0.35 * edgeLength;
	points[54] = -0.35 * edgeLength; points[55] = -0.35 * edgeLength; points[56] = -0.35 * edgeLength;
	points[57] = -0.35 * edgeLength; points[58] = -0.35 * edgeLength; points[59] = 0.35 * edgeLength;
	//Right side
	points[60] = 0.35 * edgeLength; points[61] = 0.35 * edgeLength; points[62] = -0.35 * edgeLength;
	points[63] = 0.35 * edgeLength; points[64] = 0.35 * edgeLength; points[65] = 0.35 * edgeLength;
	points[66] = 0.35 * edgeLength; points[67] = -0.35 * edgeLength; points[68] = 0.35 * edgeLength;
	points[69] = 0.35 * edgeLength; points[70] = -0.35 * edgeLength; points[71] = -0.35 * edgeLength;

}

void Cube::draw() {
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
	rotate(rotcube, 0.0f, 1.0f, 0.0f);
	rotate(rotcube, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	for (int i = 0; i < 108; i += 12) {
		glNormal3f(points[(i+2)],points[(i+1)],points[(i)]);
		glVertex3f(points[i], points[i+1], points[i+2]);
		glNormal3f(points[(i+5)],points[(i+4)],points[(i+3)]);
		glVertex3f(points[i+3], points[i+4], points[i+5]);
		glNormal3f(points[(i+8)],points[(i+7)],points[(i+6)]);
		glVertex3f(points[i+6], points[i+7], points[i+8]);
		glNormal3f(points[(i+11)],points[(i+10)],points[(i+9)]);
		glVertex3f(points[i+9], points[i+10], points[i+11]);
	}
    glEnd();
		rotcube +=0.00005f;
		if(rotcube > 360)
			rotcube -= 360;
    
	glPopAttrib();
	drawSubObjects();
    glPopMatrix();
	glutPostRedisplay();
}

