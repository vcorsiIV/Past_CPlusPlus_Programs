#ifndef __TEXT_OBJ_H__
#define __TEXT_OBJ_H__
#include "HierarchicalObject.h"

class Text_Obj : public HierarchicalObject {
protected:
	float  points[900];
public:
	Text_Obj (float edgeLength = 1.0f );
	const int QVector3D ();
	void draw();
};

#endif

