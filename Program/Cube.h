#ifndef __CUBE_H__
#define __CUBE_H__
#include "HierarchicalObject.h"

class Cube : public HierarchicalObject {
protected:
	float  points[900];
public:
	Cube (float edgeLength = 1.0 );
	void draw();
};

#endif
