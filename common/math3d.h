#include "opengl_structs.h"

#ifndef __MATH3D__
#define __MATH3D__

/*
// Based on Vector3 from http://kixor.net/  (a big thank you!)
*/

// define a version of PI
#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

// set an epsilon if not set
#ifndef EPSILON
#define EPSILON 0.00001f
#endif

// arithmetic operations
GLvoid math3d_add(GLfloat *dest, const GLfloat *v1, const GLfloat *v2);
GLvoid math3d_subtract(GLfloat *dest, const GLfloat *v1, const GLfloat *v2);
GLvoid math3d_multiply(GLfloat *dest, const GLfloat *v, const GLfloat n);
GLvoid math3d_divide(GLfloat *dest, const GLfloat *v, const GLfloat n);
GLvoid math3d_scalar_add(GLfloat *dest, const GLfloat *v, const GLfloat s);
GLvoid math3d_scalar_sub(GLfloat *dest, const GLfloat *v, const GLfloat s);
GLfloat math3d_dot(const GLfloat *a, const GLfloat *b);
GLvoid math3d_cross(GLfloat *dest, const GLfloat *a, const GLfloat *b);

// miscellaneous arithmetic functions
GLfloat math3d_max_2f(GLfloat a, GLfloat b);
GLfloat math3d_min_2f(GLfloat a, GLfloat b);
GLfloat math3d_abs_f(GLfloat f);
GLboolean math3d_equal(const GLfloat *v1, const GLfloat *v2);

// unit operations
GLfloat math3d_length(const GLfloat *a);
GLvoid math3d_normalize(GLfloat *a);
GLvoid math3d_invert(GLfloat *dest, const GLfloat *v);
GLvoid math3d_print(const GLfloat *v);

// creation
GLvoid math3d_copy(GLfloat *dest, const GLfloat *source);
GLvoid math3d_random(GLfloat *v);
GLvoid math3d_make3f(GLfloat *v, const GLfloat x, const GLfloat y, const GLfloat z);

// combination operations
GLfloat math3d_distance(const GLfloat *a, const GLfloat *b);
double math3d_distancesq(const GLfloat *a, const GLfloat *b);
GLfloat math3d_angle(const GLfloat *a, const GLfloat *b);
GLvoid math3d_reflect(GLfloat *dest, const GLfloat *incoming, const GLfloat *normal);



#endif
