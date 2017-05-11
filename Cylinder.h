#ifndef __CYLINDER_H__
#define __CYLINDER_H__
#include "HierarchicalObject.h"

class Cylinder : public HierarchicalObject {
protected:
	float  points[1500];
public:
	Cylinder (float edgeLength = 1.0f );
	void draw();
	void CreateCone();
};

#endif