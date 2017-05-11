#ifndef __HIERARCHICALOBJECT_H__
#define __HIERARCHICALOBJECT_H__
#include <list>
#include <glut.h>
#include "Material.h"

using namespace std;


class HierarchicalObject;
/*
 * This is a base class for a combined hierarchical object. 
 * It provides some useful methods and instance variables and
 * can be built on by a user.
 * 
 * This is the base class for the objects in Project 2.  It may 
 * see additional changes in order to handle the shaders but the
 * basic code that is here is correct.
 *
 * Author: Jerry Heuring
 *
 * Revisions:
 * October 22, 2013:  Added a field for materials with the intent of
 *                    supporting materials for this project and lab.

 */
class HierarchicalObject {
protected:
	double currentTransform[16];
	GLenum polygonStyle;
	bool   stippledLine;
	unsigned int linePattern;
	bool   stippledPolygon;
	unsigned char polygonPattern[128];
	list<HierarchicalObject *> subObjectList;
	float  color[3];
	void drawSubObjects();
	Material material;
public:
	HierarchicalObject();
	void translate (double dx, double dy, double dz);
	void scale ( double sx, double sy, double sz);
	void rotate ( double angle, double vx, double vy, double vz);
	virtual void draw() = 0;  // You need to implement this in your class....
	void setLineStipple(unsigned int pattern);
	unsigned int getLineStipple();
	void unsetLineStipple();
	void setPolygonStipple (unsigned char pattern[]);
	void unsetPolygonStipple();
	void getPolygonStipple (unsigned char pattern[]);
	void addSubObject(HierarchicalObject *obj);
	void setColor(float red, float green, float blue);
	void getColor(float& red, float& green, float& blue);
	void setPolygonMode(GLenum mode);
	GLenum getPolygonMode();
	Material getMaterial();
	void setMaterial(Material orig);
};
#endif
