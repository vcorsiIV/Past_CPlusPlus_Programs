#include "Texture_Obj.h"
#include "imageloader.h"
#include <iostream>
#include <stdlib.h>
#include "glut.h"
float rotobj;

using namespace std;

Texture_Obj::Texture_Obj(float edgeLength) {

	//Top of cube
	points[0] = 2.50 * edgeLength; points[1] = 2.50 * edgeLength; points[2] = -2.50 * edgeLength;
	points[3] = -2.50 * edgeLength; points[4] = 2.50 * edgeLength; points[5] = -2.50 * edgeLength;
	points[6] = -2.50 * edgeLength; points[7] = 2.50 * edgeLength; points[8] = 2.50 * edgeLength;
	points[9] = 2.50 * edgeLength; points[10] = 2.50 * edgeLength; points[11] = 2.50 * edgeLength;
	//Bottom of cube -2.5
	points[12] = 2.50 * edgeLength; points[13] = -2.50 * edgeLength; points[14] = 2.50 * edgeLength;
	points[15] = -2.50 * edgeLength; points[16] = -2.50 * edgeLength; points[17] = 2.50 * edgeLength;
	points[18] = -2.50 * edgeLength; points[19] = -2.50 * edgeLength; points[20] = -2.50 * edgeLength;
	points[21] = 2.50 * edgeLength; points[22] = -2.50 * edgeLength; points[23] = -2.50 * edgeLength;
	//Front
	points[24] = 2.50 * edgeLength; points[25] = 2.50 * edgeLength; points[26] = 2.50 * edgeLength;
	points[27] = -2.50 * edgeLength; points[28] = 2.50 * edgeLength; points[29] = 2.50 * edgeLength;
	points[30] = -2.50 * edgeLength; points[31] = -2.50 * edgeLength; points[32] = 2.50 * edgeLength;
	points[33] = 2.50 * edgeLength; points[34] = -2.50 * edgeLength; points[35] = 2.50 * edgeLength;
	//Back
	points[36] = 2.50 * edgeLength; points[37] = -2.50 * edgeLength; points[38] = -2.50 * edgeLength;
	points[39] = -2.50 * edgeLength; points[40] = -2.50 * edgeLength; points[41] = -2.50 * edgeLength;
	points[42] = -2.50 * edgeLength; points[43] = 2.50 * edgeLength; points[44] = -2.50 * edgeLength;
	points[45] = 2.50 * edgeLength; points[46] = 2.50 * edgeLength; points[47] = -2.50 * edgeLength;
	//Left side
	points[48] = -2.50 * edgeLength; points[49] = 2.50 * edgeLength; points[50] = 2.50 * edgeLength;
	points[51] = -2.50 * edgeLength; points[52] = 2.50 * edgeLength; points[53] = -2.50 * edgeLength;
	points[54] = -2.50 * edgeLength; points[55] = -2.50 * edgeLength; points[56] = -2.50 * edgeLength;
	points[57] = -2.50 * edgeLength; points[58] = -2.50 * edgeLength; points[59] = 2.50 * edgeLength;
	//Right side
	points[60] = 2.50 * edgeLength; points[61] = 2.50 * edgeLength; points[62] = -2.50 * edgeLength;
	points[63] = 2.50 * edgeLength; points[64] = 2.50 * edgeLength; points[65] = 2.50 * edgeLength;
	points[66] = 2.50 * edgeLength; points[67] = -2.50 * edgeLength; points[68] = 2.50 * edgeLength;
	points[69] = 2.50 * edgeLength; points[70] = -2.50 * edgeLength; points[71] = -2.50 * edgeLength;

}

GLuint loadTexture(Image* image){
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId);
	//Map the image to the texture:
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,		//Always in 2d format, start at 0, and RGB format
				 image->width, image->height,	//Width and height
				 0, GL_RGB, GL_UNSIGNED_BYTE,	//Boader of image,because pixels are stored in RGB format as unsigned #s
				 image->pixels);				//actual pixel data
	return textureId;							//returns id of the texture
}

GLuint _textureId; //The id of the texture

void Texture_Obj::draw() {
	Image* image = loadBMP("salt_on_spoon.bmp");
	_textureId = loadTexture(image);
	delete image;

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
	rotate(rotobj, 0.0f, 1.0f, 0.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //Blocky image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Blurry image
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	
	for (int i = 0; i < 108; i += 12) {
		glNormal3f(0,1,0);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(points[i], points[i+1], points[i+2]);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(points[i+3], points[i+4], points[i+5]);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(points[i+6], points[i+7], points[i+8]);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(points[i+9], points[i+10], points[i+11]);
	}
	
	glEnd();
	rotobj +=0.0011f;
	if(rotobj > 360)
		rotobj -= 360;
    
	glPopAttrib();
	drawSubObjects();
    glPopMatrix();
	glutPostRedisplay();
}

