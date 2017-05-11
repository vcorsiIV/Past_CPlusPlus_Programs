#include "MultiObj.h"

MultiObj::MultiObj(float edgeLength) {
	// Cylinder
	int x = 0;
	for(int i=0;i<=180;i+=3){
		pointsCy[i]=(cos(-x)); pointsCy[i+2]=(sin(-x));
		x++;
	}
	int y = 0;
	for(int i=181;i<=361;i+=3){
		pointsCy[i]=(cos(y)); pointsCy[i+2]=(sin(y));
		y++;
	}

	int a = 0;
	pointsCo[0]=0;pointsCo[1]=8; pointsCo[2]=0;
	for(int i=3;i<=183;i+=3){
		pointsCo[i]=(2*cos(-a));pointsCo[i+1]=1; pointsCo[i+2]=(2*sin(-a));
		a++;
	}

	
}

void MultiObj::draw(){
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
	material.useMaterial();
	glColor3fv(color);
    glMultMatrixd(currentTransform);  // Apply current object's transformation

	//Top end of the cylinder
	glBegin( GL_TRIANGLE_FAN ); 
	glColor3f(0.0,0.25,0.01);
	glNormal3f(0.0f,1.0f,0.0f);    
	//change y value here and in the vertex below to move the end up or    
	//down to seal the top end of the cylinder    
	glVertex3f(0.0f,1.0f,0.0f);    
	for(int i=0;i<=90;i+=3){ 
		glColor3f(0.0,0.25,0.01);
		glVertex3f(pointsCy[i],pointsCy[i+1]=1.0,pointsCy[i+2]);    
	}     
	glEnd();
	glColor3f(0.0,0.25,0.01);
	// bottom end of cylinder    
	glBegin( GL_TRIANGLE_FAN );    
	glNormal3f(0.0f,-1.0f,0.0f);    
	//changeing the y value moves the end up or down to
	//seal the bottom end of the cylinder.   
	//glVertex3f(0.0f,-0.0f,0.0f);    
	for(int i=0;i<=180;i+=3){ 
		glColor3f(0.0,0.25,0.01);
		glVertex3f(pointsCy[i],0,pointsCy[i+2]);    
	}
	glEnd();
	//side of cylinder, y-values are used for the length of the cylinder
	//x and z values are used for the radius.
		for(int j=0;j<=6;j++){
		glBegin(GL_QUAD_STRIP);
		for(int i=0;i<360;i+=3){
			glNormal3f(pointsCy[i], pointsCy[i+1]=(0.0f), pointsCy[i+2]);                     
			glVertex3f(pointsCy[i], pointsCy[i+1]=((j)/6), pointsCy[i+2]);
			glVertex3f(pointsCy[i], pointsCy[i+1]=((j+1)/6), pointsCy[i+2]);
		}
	}
	
	glEnd();

	// bottom end of Cone1    
	glBegin( GL_TRIANGLE_FAN );    
	glNormal3f(0.0f,0.0f,0.0f);    
	//changeing the y value moves the end up or down to
	//seal the bottom end of the Cone1.
	glColor3f(0.01,0.3,0.3);
	glVertex3f(0.0f,1.0f,0.0f);    
	for(int i=3;i<=93;i+=3){
		glColor3f(0.01,0.3,0.3);
		glVertex3f(pointsCo[i],pointsCo[i+1],pointsCo[i+2]);
	}
	glEnd();
	//side of Cone1, y-values are used for the length of the Cone
	//x and z values are used for the radius.    
	glBegin(GL_QUADS);
	for(int i=3;i<93;i+=3){
		glNormal3f(pointsCo[0], pointsCo[1], pointsCo[2]);
		glColor3f(0.01,0.3,0.3);
		glVertex3f(pointsCo[0],pointsCo[1],pointsCo[2]);
		glNormal3f(pointsCo[i], pointsCo[i+1], pointsCo[i+2]);
		glColor3f(0.01,0.3,0.3);
		glVertex3f(pointsCo[i],pointsCo[i+1],pointsCo[i+2]);
		glNormal3f(pointsCo[i+3], pointsCo[i+4], pointsCo[i+5]);
		glColor3f(0.01,0.3,0.3);
		glVertex3f(pointsCo[i+3],pointsCo[i+4],pointsCo[i+5]);
	}
	glEnd();
	

	glPopAttrib();
	drawSubObjects();
    glPopMatrix();
}