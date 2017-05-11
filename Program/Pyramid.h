#ifndef __PYRAMID_H__
#define __PYRAMID_H__
#include "HierarchicalObject.h"

class Pyramid : public HierarchicalObject {
protected:
	float  points[60];
public:
	Pyramid (float edgeLength = 1.0f );
	void draw();
};

#endif