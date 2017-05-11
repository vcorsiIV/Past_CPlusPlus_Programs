#include "Material.h"
#include "glut.h"
/*
 * A rather simplistic class for a material that is being
 * used to handle the materials in this case -- not complete
 * by any means.
 */

	Material::Material() {
		ambient[0]  = 0.2; ambient[1]  = 0.2; ambient[2]  = 0.2; ambient[3]  = 1.0;
		diffuse[0]  = 0.8; diffuse[1]  = 0.8; diffuse[2]  = 0.8; ambient[3]  = 1.0;
		specular[0] = 0.0; specular[1] = 0.0; specular[2] = 0.0; specular[3] = 1.0;
		shininess   = 0.0;
		emission[0] = 0.0; emission[1] = 0.0; emission[2] = 0.0; emission[3] = 1.0;
	}

	Material::Material (float ar, float ag, float ab,
		      float dr, float dg, float db,
			  float sr, float sg, float sb,
			  float shininess) {
		ambient[0]  = ar; ambient[1]  = ag; ambient[2]  = ab; ambient[3]  = 1.0;
		diffuse[0]  = dr; diffuse[1]  = dg; diffuse[2]  = db; diffuse[3]  = 1.0;
		specular[0] = sr; specular[1] = sg; specular[2] = sb; specular[3] = 1.0;
		this->shininess = shininess;
	}

	void Material::setAmbient( float a[]) {
		ambient[0] = a[0];
		ambient[1] = a[1];
		ambient[2] = a[2];
		ambient[3] = a[3];
	}

	void Material::setDiffuse(float d[]) {
		diffuse[0] = d[0];
		diffuse[1] = d[1];
		diffuse[2] = d[2];
		diffuse[3] = d[3];
	}

	void Material::setSpecular(float s[]) {
		specular[0] = s[0];
		specular[1] = s[1];
		specular[2] = s[2];
		specular[3] = s[3];
	}

	void Material::setEmission( float e[]) {
		emission[0] = e[0];
		emission[1] = e[1];
		emission[2] = e[2];
		emission[3] = e[3];
	}

	void Material::setShininess(float shine) {
		shininess = shine;
	}

	void Material::useMaterial()
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  specular);
		glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}
