#ifndef __CONE_H__
#define __CONE_H__
#include "HierarchicalObject.h"

class Cone : public HierarchicalObject {
protected:
	float  points[900];
public:
	Cone (float edgeLength = 1.0f );
	const int QVector3D ();
	void draw();
};

#endif
