#include "Pyramid.h"

Pyramid::Pyramid(float edgeLength) {
	points[0] = 0.0; points[1] = 0.0; points[2] = 0.433*edgeLength;
	points[3] = -0.5 * edgeLength; points[4] = 0.0; points[5] = -0.433 * edgeLength;
	points[6] = 0.5 * edgeLength; points[7] = 0.0; points[8] = -0.433 * edgeLength;

	points[9] = 0.0; points[10] = 0.0; points[11] = 0.433 * edgeLength;
	points[12] = -0.5 *edgeLength; points[13] = 0.0; points[14] = -0.433 * edgeLength;
	points[15] = 0.0; points[16] = 0.866*edgeLength; points[17] = -0.143 * edgeLength;

	points[18] = 0.0; points[19] = 0.0; points[20] = 0.433 * edgeLength;
	points[21] = 0.5 * edgeLength; points[22] = 0.0; points[23] = -0.433 * edgeLength;
	points[24] = 0.0; points[25] = 0.866*edgeLength; points[26] = -0.143 * edgeLength;

	points[27] = -0.5 * edgeLength; points[28] = 0.0; points[29] = -0.433 * edgeLength;
	points[30] = 0.5 * edgeLength; points[31] = 0.0; points[32] = -0.433 * edgeLength;
	points[33] = 0.0; points[34] = 0.866 * edgeLength;  points[35] = -0.143*edgeLength;
}

void Pyramid::draw() {
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
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i += 3) {
		glNormal3f(points[i], points[i], points[i+1]);
		glVertex3f(points[i], points[i+1], points[i+2]);
	}
    glEnd();

    glPopAttrib();
	drawSubObjects();

    glPopMatrix();
}


