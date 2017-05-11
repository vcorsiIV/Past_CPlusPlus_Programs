#ifndef __MATERIAL_H__
#define __MATERIAL_H__
/*
 * A rather simplistic class for a material that is being
 * used to handle the materials in this case -- not complete
 * by any means.
 */
class Material {
protected:
	float ambient[4];
	float diffuse[4]; 
	float specular[4];
	float shininess;
	float emission[4];
public:
	Material();
	Material (float ar, float ag, float ab,
		      float dr, float dg, float db,
			  float sr, float sg, float sb,
			  float shininess);
	void setAmbient( float a[]);
	void setDiffuse(float d[]);
	void setSpecular(float s[]);
	void setEmission( float e[]);
	void setShininess(float shine);
	void useMaterial();
};
#endif
