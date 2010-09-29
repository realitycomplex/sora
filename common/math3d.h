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
GLvoid math3d_add(Glfloat *dest, const Glfloat *v1, const Glfloat *v2);
GLvoid math3d_subtract(Glfloat *dest, const Glfloat *v1, const Glfloat *v2);
GLvoid math3d_multiply(Glfloat *dest, const Glfloat *v, const GLfloat n);
GLvoid math3d_divide(Glfloat *dest, const Glfloat *v, const GLfloat n);
GLvoid math3d_scalar_add(Glfloat *dest, const Glfloat *v, const GLfloat s);
GLvoid math3d_scalar_sub(Glfloat *dest, const Glfloat *v, const GLfloat s);
GLfloat math3d_dot(const Glfloat *a, const Glfloat *b);
GLvoid math3d_cross(Glfloat *dest, const Glfloat *a, const Glfloat *b);

// miscellaneous arithmetic functions
GLfloat math3d_max_2f(GLfloat a, GLfloat b);
GLfloat math3d_min_2f(GLfloat a, GLfloat b);
GLfloat math3d_abs_f(GLfloat f);
GLboolean math3d_equal(const Glfloat *v1, const Glfloat *v2);

// unit operations
GLfloat math3d_length(const Glfloat *a);
GLvoid math3d_normalize(Glfloat *a);
GLvoid math3d_invert(Glfloat *dest, const Glfloat *v);
GLvoid math3d_print(const Glfloat *v);

// creation
GLvoid math3d_copy(Glfloat *dest, const Glfloat *source);
GLvoid math3d_random(Glfloat *v);
GLvoid math3d_make3f(Glfloat *v, const GLfloat x, const GLfloat y, const GLfloat z);

// combination operations
GLfloat math3d_distance(const Glfloat *a, const Glfloat *b);
double math3d_distancesq(Glfloat *a, Glfloat *b);
GLfloat math3d_angle(const Glfloat *a, const Glfloat *b);
GLvoid math3d_reflect(Glfloat *dest, const Glfloat *incoming, const Glfloat *normal);



#endif
