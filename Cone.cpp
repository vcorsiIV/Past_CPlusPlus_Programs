#include "Cone.h"
float rotcone;
float rotcone2;

Cone::Cone(float edgeLength) {
	int x = 0;
	
	points[0]=0;points[1]=10; points[2]=0;
	
	for(int i=3;i<=363;i+=3){
		points[i]=(2*cos(-x));points[i+1]=0; points[i+2]=(2*sin(-x));
		x++;
	}
}

void Cone::draw(){
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
	rotate(rotcone, 0.0f, 1.0f, 0.0f);
	rotate(rotcone2, 1.0f, 0.0f, 0.0f);
	// bottom end of Cone    
	glBegin( GL_TRIANGLE_FAN );    
	glNormal3f(0.0f,0.0f,0.0f);    
	//changeing the y value moves the end up or down to
	//seal the bottom end of the Cone.   
	glVertex3f(0.0f,-0,0.0f);    
	for(int i=3;i<=363;i+=3){        
		glVertex3f(points[i],points[i+1],points[i+2]);
	}
	glEnd();
	//side of Cone, y-values are used for the length of the Cone
	//x and z values are used for the radius.    
	glBegin(GL_QUADS);
	for(int i=3;i<363;i+=3){
		glNormal3f(points[0], points[1], points[2]);
		glVertex3f(points[0],points[1],points[2]);
		glNormal3f(points[i], points[i+1], points[i+2]);
		glVertex3f(points[i],points[i+1],points[i+2]);
		glNormal3f(points[i+3], points[i+4], points[i+5]);
		glVertex3f(points[i+3],points[i+4],points[i+5]);
	}
	glEnd();
	rotcone +=3.0f;
	if(rotcone > 360)
		rotcone -= 360;
	rotcone2 +=0.1f;
	if(rotcone2 > 360)
		rotcone2 -= 360;
	glPopAttrib();
	drawSubObjects();
    glPopMatrix();
	glutPostRedisplay();
}