#ifndef __MULTIOBJ_H__
#define __MULTIOBJ_H__
#include "HierarchicalObject.h"

class MultiObj : public HierarchicalObject {
protected:
	float pointsCy[1500];
	float pointsCo[900];
	float pointsCo2[900];
public:
	MultiObj (float edgeLength = 1.0f );
	const int QVector3D ();
	void draw();
};

#endif

