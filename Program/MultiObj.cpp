#include "MultiObj.h"

MultiObj::MultiObj(float edgeLength) {
	// Cylinder
	int x = 0;
	for(int i=0;i<=360;i+=3){
		pointsCy[i]=(0.75*cos(-x)); pointsCy[i+2]=(0.75*sin(-x));
		x++;
	}
	int y = 0;
	for(int i=91;i<=721;i+=3){
		pointsCy[i]=(0.75*cos(y)); pointsCy[i+2]=(0.75*sin(y));
		y++;
	}

	int a = 0;
	pointsCo[0]=0;pointsCo[1]=10; pointsCo[2]=0;
	for(int i=3;i<=363;i+=3){
		pointsCo[i]=(1.75*cos(-a));pointsCo[i+1]=1.75; pointsCo[i+2]=(1.75*sin(-a));
		a++;
	}

	int b = 0;
	pointsCo2[0]=0;pointsCo2[1]=10; pointsCo2[2]=0;
	for(int i=3;i<=363;i+=3){
		pointsCo2[i]=(1.65*cos(-b));pointsCo2[i+1]=3.8; pointsCo2[i+2]=(1.65*sin(-b));
		b++;
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
	glVertex3f(0.0f,7.0f,0.0f);    
	for(int i=0;i<=360;i+=3){ 
		glColor3f(0.0,0.25,0.01);
		glVertex3f(pointsCy[i],pointsCy[i+1]=7.0,pointsCy[i+2]);    
	}     
	glEnd();
	glColor3f(0.0,0.25,0.01);
	// bottom end of cylinder    
	glBegin( GL_TRIANGLE_FAN );    
	glNormal3f(0.0f,-1.0f,0.0f);    
	//changeing the y value moves the end up or down to
	//seal the bottom end of the cylinder.   
	//glVertex3f(0.0f,-0.0f,0.0f);    
	for(int i=0;i<=360;i+=3){ 
		glColor3f(0.0,0.25,0.01);
		glVertex3f(pointsCy[i],0,pointsCy[i+2]);    
	}
	glEnd();
	//side of cylinder, y-values are used for the length of the cylinder
	//x and z values are used for the radius.    
	for(int j=0;j<=30;j++){
		glBegin(GL_QUAD_STRIP);
		for(int i=0;i<360;i+=3){
			glNormal3f(pointsCy[i], pointsCy[i+1]=(0.0f), pointsCy[i+2]);
			glColor3f(0.0,0.25,0.01);
			glVertex3f(pointsCy[i], pointsCy[i+1]=((j)/6), pointsCy[i+2]);
			glColor3f(0.0,0.25,0.01);
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
	glVertex3f(0.0f,1.8f,0.0f);    
	for(int i=3;i<=363;i+=3){
		glColor3f(0.01,0.3,0.3);
		glVertex3f(pointsCo[i],pointsCo[i+1],pointsCo[i+2]);
	}
	glEnd();
	//side of Cone1, y-values are used for the length of the Cone
	//x and z values are used for the radius.    
	glBegin(GL_QUADS);
	for(int i=3;i<363;i+=3){
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
	
	// bottom end of Cone2    
	glBegin( GL_TRIANGLE_FAN );    
	glNormal3f(0.0f,0.0f,0.0f);    
	//changeing the y value moves the end up or down to
	//seal the bottom end of the Cone2.   
	glColor3f(0.01,0.4,0.4);
	glVertex3f(0.0f,4,0.0f);    
	for(int i=3;i<=363;i+=3){  
		glColor3f(0.01,0.4,0.4);
		glVertex3f(pointsCo2[i],pointsCo2[i+1],pointsCo2[i+2]);
	}
	glEnd();
	//side of Cone2, y-values are used for the length of the Cone
	//x and z values are used for the radius.    
	glBegin(GL_QUADS);
	for(int i=3;i<363;i+=3){
		glColor3f(0.01,0.4,0.4);
		glNormal3f(pointsCo2[0], pointsCo2[1], pointsCo2[2]);
		glVertex3f(pointsCo2[0],pointsCo2[1],pointsCo2[2]);
		glNormal3f(pointsCo2[i], pointsCo2[i+1], pointsCo2[i+2]);
		glColor3f(0.01,0.4,0.4);
		glVertex3f(pointsCo2[i],pointsCo2[i+1],pointsCo2[i+2]);
		glNormal3f(pointsCo2[i+3], pointsCo2[i+4], pointsCo2[i+5]);
		glColor3f(0.01,0.4,0.4);
		glVertex3f(pointsCo2[i+3],pointsCo2[i+4],pointsCo2[i+5]);
	}
	glEnd();

	glPopAttrib();
	drawSubObjects();
    glPopMatrix();
}