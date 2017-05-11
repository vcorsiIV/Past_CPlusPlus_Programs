#ifndef __TEXTURE_OBJ_H__
#define __TEXTURE_OBJ_H__
#include "HierarchicalObject.h"
#include "imageloader.h"

class Texture_Obj : public HierarchicalObject {
protected:
	float  points[900];
public:
	
	Texture_Obj (float edgeLength = 1.0 );
	void draw();
	void Rendering();
	void readtexture();
};

#endif
