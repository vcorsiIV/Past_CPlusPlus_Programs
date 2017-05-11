#include "Cylinder.h"

float rotCylinder;
float xaxis;
float yaxis;
int add;

Cylinder::Cylinder(float edgeLength) {
	int x = 0;
	for(int i=0;i<=360;i+=3){
		points[i]=(2*cos(-x)); points[i+2]=(2*sin(-x));
		x++;
	}
	int y = 0;
	for(int i=361;i<=721;i+=3){
		points[i]=(2*cos(y)); points[i+2]=(2*sin(y));
		y++;
	}
}

void Cylinder::draw(){
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

	add+=0.5;
	rotCylinder+=0.05;
	yaxis= 0.04*cos(rotCylinder)-add;
	yaxis= 0.04*sin(rotCylinder)+add;
	rotate(rotCylinder, 0.0f, 0.0f, 1.0f);
	translate(xaxis, yaxis, 0.0f);
	rotate(-rotCylinder, 0.0f, 0.0f, 1.0f);
	if(rotCylinder>45){
		for(rotCylinder=45; rotCylinder>=0; rotCylinder--){
			add-=-0.5;
			rotCylinder-=.05;
			if (add <-4)
				add+=0.55;
		}
	}

	//Top end of the cylinder
	glBegin( GL_TRIANGLE_FAN );    
	glNormal3f(0.0f,1.0f,0.0f);    
	//change y value here and in the vertex below to move the end up or    
	//down to seal the top end of the cylinder    
	glVertex3f(0.0f,7.0f,0.0f);    
	for(int i=0;i<=360;i+=3){ 
		glVertex3f(points[i],points[i+1]=7.0,points[i+2]);    
	}     
	glEnd();
	// bottom end of cylinder    
	glBegin( GL_TRIANGLE_FAN );    
	glNormal3f(0.0f,-1.0f,0.0f);    
	//changeing the y value moves the end up or down to
	//seal the bottom end of the cylinder.   
	//glVertex3f(0.0f,-0.0f,0.0f);    
	for(int i=0;i<=360;i+=3){        
		glVertex3f(points[i],0,points[i+2]);    
	}
	glEnd();
	//side of cylinder, y-values are used for the length of the cylinder
	//x and z values are used for the radius.    
	for(int j=0;j<=45;j++){
		glBegin(GL_QUAD_STRIP);
		for(int i=0;i<360;i+=3){
			glNormal3f(points[i], points[i+1]=(0.0f), points[i+2]);                     
			glVertex3f(points[i], points[i+1]=((j)/6), points[i+2]);
			glVertex3f(points[i], points[i+1]=((j+1)/6), points[i+2]);
		}
	}
	glEnd();

	glPopAttrib();
	drawSubObjects();

    glPopMatrix();
	glutPostRedisplay();
}
