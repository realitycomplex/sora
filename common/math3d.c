#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math3d.h"

// arithmetic operations
GLvoid math3d_add(GLfloat *dest, const GLfloat *v1, const GLfloat *v2){
	dest[0] = v1[0] + v2[0];
	dest[1] = v1[1] + v2[1];
	dest[2] = v1[2] + v2[2];
}

GLvoid math3d_subtract(GLfloat *dest, const GLfloat *v1, const GLfloat *v2){
	dest[0] = v1[0] - v2[0];
	dest[1] = v1[1] - v2[1];
	dest[2] = v1[2] - v2[2];
}

GLvoid math3d_multiply(GLfloat *dest, const GLfloat *v, const GLfloat n){
	dest[0] = v[0] * n;
	dest[1] = v[1] * n;
	dest[2] = v[2] * n;
}

GLvoid math3d_divide(GLfloat *dest, const GLfloat *v,const  GLfloat n){
	dest[0] = v[0] / n;
	dest[1] = v[1] / n;
	dest[2] = v[2] / n;
}

GLvoid math3d_scalar_add(GLfloat *dest, const GLfloat *v, const GLfloat s){
	dest[0] = v[0] + s;
	dest[1] = v[1] + s;
	dest[2] = v[2] + s;
}

GLvoid math3d_scalar_sub(GLfloat *dest, const GLfloat *v, const GLfloat s){
	dest[0] = v[0] - s;
	dest[1] = v[1] - s;
	dest[2] = v[2] - s;
}

GLfloat math3d_dot(const GLfloat *v1, const GLfloat *v2){
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

GLvoid math3d_cross(GLfloat *dest, const GLfloat *v1, const GLfloat *v2){
	dest[0] = v1[1]*v2[2] - v1[2]*v2[1];
	dest[1] = v1[2]*v2[0] - v1[0]*v2[2];
	dest[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

// miscellaneous arithmetic functions
GLfloat math3d_max_2f(GLfloat a, GLfloat b){
  if (b > a)
    return b;
  return a;
}

GLfloat math3d_min_2f(GLfloat a, GLfloat b){
  if (b < a)
    return b;
  return a;
}

GLfloat math3d_abs_f(GLfloat f){
  if (f < 0)
    return -f;
  return f;
}

GLboolean math3d_equal(const GLfloat *v1, const GLfloat *v2){
    if (math3d_abs_f(v1[0] - v2[0]) < EPSILON &&
        math3d_abs_f(v1[1] - v2[1]) < EPSILON &&
        math3d_abs_f(v1[2] - v2[2]) < EPSILON) {
        return GL_TRUE;
    }
    return GL_FALSE;
}

// unit operations
GLfloat math3d_length(const GLfloat *v){
	return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

GLvoid math3d_normalize(GLfloat *v){
	GLfloat normalizeLength;
	normalizeLength = math3d_length(v);
	
	if(normalizeLength >= EPSILON){
		math3d_divide(v, v, normalizeLength);
	}
}

GLvoid math3d_invert(GLfloat *dest, const GLfloat *v1){
	dest[0] = -v1[0];
	dest[1] = -v1[1];
	dest[2] = -v1[2];
}

GLvoid math3d_print(const GLfloat *v){
	printf("%.2f %.2f %.2f\n", v[0], v[1], v[2]);
}

// creation
GLvoid math3d_copy(GLfloat *dest, const GLfloat *source){
	dest[0] = source[0];
	dest[1] = source[1];
	dest[2] = source[2];
}

GLvoid math3d_random(GLfloat *v){
	do {
		v[0] = (double)rand()/RAND_MAX*2-1;
		v[1] = (double)rand()/RAND_MAX*2-1;
		v[2] = (double)rand()/RAND_MAX*2-1;
	} while (v[0]*v[0] + v[1]*v[1] + v[2]*v[2] > 1.0);
}

GLvoid math3d_make3f(GLfloat *v, const GLfloat x, const GLfloat y, const GLfloat z){
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

// combination operations
GLfloat math3d_distance(const GLfloat *v1, const GLfloat *v2){
	return sqrt( math3d_distancesq(v1, v2) );
				
}

double math3d_distancesq(const GLfloat *v1, const GLfloat *v2){
	return pow(v1[0] - v2[0], 2) + pow(v1[1] - v2[1], 2) + 
				pow(v1[2] - v2[2], 2);
}

GLfloat math3d_angle(const GLfloat *v1, const GLfloat *v2) {
	return acos(math3d_dot(v1,v2) / math3d_length(v1) / math3d_length(v2));
}

GLvoid math3d_reflect(GLfloat *dest, const GLfloat *incoming, const GLfloat *normal){
	GLfloat dp;
	dp = 2*math3d_dot(normal, incoming);

	dest[0] = incoming[0] - dp*normal[0];
	dest[1] = incoming[1] - dp*normal[1];
	dest[2] = incoming[2] - dp*normal[2];
}
