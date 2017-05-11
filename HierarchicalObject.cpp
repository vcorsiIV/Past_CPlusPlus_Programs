
#include "HierarchicalObject.h"
/*
 * These are the routines for the base object of the hierarchical
 * object class.  Most of the routines (other than draw) are filled
 * in.  It may still be useful to add more as time goes on...
 *
 * Need to add color as an attribute.
 *
 * Author:  Jerry Heuring
 * Date:    September 25, 2002
 *
 * Revisions:
 *
 * Unknown Date       -- added color as an attribute
 *
 * September 29, 2003 -- revised the code to check on and keep track of current
 *                       matrix mode.  Patched a few other minor issues.
 * October 21, 2013 -- Added material get/set methods and initialization in 
 *                     constructors.
 */

HierarchicalObject::HierarchicalObject()
{
    /* 
     * the constructor originally sets the transformation 
     * and sets the flags to a "sane" version.
     */
    int i;

    for (i = 0; i < 16; i++) {
	currentTransform[i] = 0.0;
    }
    for (i = 0; i < 16; i += 5) {
	currentTransform[i] = 1.0;
    }
    stippledPolygon = false;
    stippledLine = false;
    polygonStyle = GL_LINE;
}

void HierarchicalObject::unsetPolygonStipple() {
    /*
     * turn off polygon stippling (default)
     */
    stippledPolygon = false;
}

void HierarchicalObject::unsetLineStipple() {
    /*
     * Turn off line stippling (default)
     */
    stippledLine = false;
}

void HierarchicalObject::setLineStipple(unsigned int stipple){
    /*
     * set the current line stipple pattern
     */
    linePattern = stipple;
}

unsigned int HierarchicalObject::getLineStipple() {
    /*
     * get the current line stipple pattern
     */
    return linePattern;
}

void HierarchicalObject::getPolygonStipple ( unsigned char pattern[]) {
    /*
     * get the current stipple pattern for the polygon.
     */
    int i;
    for (i = 0; i < 128; i++) {
	pattern[i] = polygonPattern[i];
    }
    return;
}

void HierarchicalObject::setPolygonStipple ( unsigned char pattern[]) {
    /*
     * Set the stipple pattern for polygons in this object 
     */
    int i;

    for (i = 0; i < 128; i++) {
	polygonPattern[i] = pattern[i];
    }
    return;
}

/*
 * Translate this object by the distances given as arguments.
 */
void HierarchicalObject::translate (double dx, double dy, double dz) {
    /*
     * Do a translation
     */
    GLint saveMode;

    glGetIntegerv(GL_MATRIX_MODE, &saveMode);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMultMatrixd(currentTransform);
    glTranslated(dx, dy, dz);
    glGetDoublev(GL_MODELVIEW_MATRIX, currentTransform);
    glPopMatrix();
    glMatrixMode(saveMode);
}

/*
 * Scale this object by a factor given as an argument.
 */
void HierarchicalObject::scale ( double sx, double sy, double sz) {
    /*
     * Do a scaling with respect to the origin.  
     */
    GLint saveMode;

    glGetIntegerv(GL_MATRIX_MODE, &saveMode);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMultMatrixd(currentTransform);
    glScaled(sx, sy, sz);
    glGetDoublev(GL_MODELVIEW_MATRIX, currentTransform);
    glPopMatrix();
    glMatrixMode(saveMode);
}

/*
 * rotate the current object by an angle around the specified vector.
 *
 * The angle is assumed to be in degrees.
 */
void HierarchicalObject::rotate ( double angle, double vx, double vy, double vz) {
    /*
     * Do a rotation around the specified axis.  
     */
    GLint saveMode;

    glGetIntegerv(GL_MATRIX_MODE, &saveMode);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMultMatrixd(currentTransform);
    glRotated(angle, vx, vy, vz);
    glGetDoublev(GL_MODELVIEW_MATRIX, currentTransform);
    glPopMatrix();
    glMatrixMode(saveMode);
}

void HierarchicalObject::addSubObject( HierarchicalObject *obj ) {
    /*
     * add an object to the list of subobjects.  No 
     * order is meant to be maintained but they do tend to 
     * be in the order that they were added to the list.
     */
    subObjectList.push_back(obj);
}

/*
 * Set the color to use with this object. 
 */
void HierarchicalObject::setColor(float red, float green, float blue){
    color[0] = red;
    color[1] = green;
    color[2] = blue;
    return;
}

/*
 * Get the red, green, blue components for the color of this object.
 *
 * Note:  This should probably converted to return a vector or structure
 *        rather than the three variables that are passed in.
 */
void HierarchicalObject::getColor(float& red, float& green, float& blue) {
    red  = color[0];
    green= color[1];
    blue = color[2];
}

/*
 * Set the polygon mode for this object.
 */
void HierarchicalObject::setPolygonMode(GLenum mode)
{
    polygonStyle = mode;
    return;
}

/*
 * returns the polygon mode (filled or not)
 */
GLenum HierarchicalObject::getPolygonMode() {
    return polygonStyle;
}

/*
 * Go through the list of subobjects and call each of their
 * draw routines in turn.
 */
void HierarchicalObject::drawSubObjects() {
    list<HierarchicalObject *>::iterator current;

    if (subObjectList.size() > 0 ) {
	for ( current = subObjectList.begin();
	      current != subObjectList.end();
	      current++){
	    (*current)->draw();
	}
    }
}

/*
 * get The material associated with this object.
 */
Material HierarchicalObject::getMaterial() {
	return material;
}

/*
 * set the material to be associated with this object
 */
void HierarchicalObject::setMaterial(Material orig) {
	material = orig;
}
