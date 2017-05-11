#ifndef __PLANE_H__
#define __PLANE_H__
#include "HierarchicalObject.h"

class Plane : public HierarchicalObject {
protected:
	float  points[1500];
public:
	Plane (float edgeLength = 1.0 );
	void draw();
};

#endif
