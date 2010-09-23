#include "SDL/SDL_opengl.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math3d.h"

// arithmetic operations
INLINE vec3f_t* math3d_add_vec3f(vec3f_t *dest, const vec3f_t *v1, const vec3f_t *v2){
	dest->x = v1->x + v2->x;
	dest->y = v1->y + v2->y;
	dest->z = v1->z + v2->z;
	return dest;
}

INLINE vec3f_t* math3d_subtract_vec3f(vec3f_t *dest, const vec3f_t *minuend, const vec3f_t *subtrahend){
	dest->x = minuend->x - subtrahend->x;
	dest->y = minuend->y - subtrahend->y;
	dest->z = minuend->z - subtrahend->z;
	return dest;
}

INLINE vec3f_t* math3d_multiply_vec3f(vec3f_t *dest, const vec3f_t *v, const GLfloat n){
	dest->x = v->x * n;
	dest->y = v->y * n;
	dest->z = v->z * n;
	return dest;
}

INLINE vec3f_t* math3d_divide_vec3f(vec3f_t *dest, const vec3f_t *v,const  GLfloat n){
	dest->x = v->x / n;
	dest->y = v->y / n;
	dest->z = v->z / n;
	return dest;
}

INLINE vec3f_t *math3d_scalar_add_vec3f(vec3f_t *dest, const vec3f_t *v, const GLfloat s){
	dest->x = v->x + s;
	dest->y = v->y + s;
	dest->z = v->z + s;
	return dest;
}

INLINE vec3f_t *math3d_scalar_sub_vec3f(vec3f_t *dest, const vec3f_t *v, const GLfloat s){
	dest->x = v->x - s;
	dest->y = v->y - s;
	dest->z = v->z - s;
	return dest;
}

INLINE GLfloat math3d_dot_vec3f(const vec3f_t *a, const vec3f_t *b){
	return a->x*b->x + a->y*b->y + a->z*b->z;
}

INLINE vec3f_t* math3d_cross_vec3f(vec3f_t *dest, const vec3f_t *a, const vec3f_t *b){
	dest->x = a->y*b->z - a->z*b->y;
	dest->y = a->z*b->x - a->x*b->z;
	dest->z = a->x*b->y - a->y*b->x;
	
	return dest;
}

// miscellaneous arithmetic functions
INLINE GLfloat math3d_max_2f(GLfloat a, GLfloat b){
  if (b > a)
    return b;
  return a;
}

INLINE GLfloat math3d_min_2f(GLfloat a, GLfloat b){
  if (b < a)
    return b;
  return a;
}

INLINE GLfloat math3d_abs_f(GLfloat f){
  if (f < 0)
    return -f;
  return f;
}

INLINE GLboolean math3d_equal_2vec3f(const vec3f_t *v1, const vec3f_t *v2){
    if (math3d_abs_f(v1->x - v2->x) < EPSILON &&
        math3d_abs_f(v1->y - v2->y) < EPSILON &&
        math3d_abs_f(v1->z - v2->z) < EPSILON) {
        return GL_TRUE;
    }
    return GL_FALSE;
}

// vec3f_t unit operations
INLINE GLfloat math3d_length_vec3f(const vec3f_t *a){
	return sqrt(a->x*a->x + a->y*a->y + a->z*a->z);
}

INLINE vec3f_t* math3d_normalize_vec3f(vec3f_t *a){
	GLfloat normalizeLength;
	normalizeLength = math3d_length_vec3f(a);
	
	if(normalizeLength <= EPSILON)
	{
		printf("cannot normalize degenerate vec3f_t\n");
		return a;
	}
	
	math3d_divide_vec3f(a, a, normalizeLength);
	return a;
}

INLINE vec3f_t* math3d_invert_vec3f(vec3f_t *dest, const vec3f_t *v){
	dest->x = -v->x;
	dest->y = -v->y;
	dest->z = -v->z;
	return dest;
}

INLINE void math3d_print_vec3f(const vec3f_t *v){
	printf("%.2f %.2f %.2f\n", v->x, v->y, v->z);
}

// vec3f_t creation
INLINE vec3f_t* math3d_copy_vec3f(vec3f_t *dest, const vec3f_t *source){
	dest->x = source->x;
	dest->y = source->y;
	dest->z = source->z;
	return dest;
}

INLINE vec3f_t* math3d_random_vec3f(vec3f_t *v){
	do {
		v->x = (double)rand()/RAND_MAX*2-1;
		v->y = (double)rand()/RAND_MAX*2-1;
		v->z = (double)rand()/RAND_MAX*2-1;
	} while (v->x*v->x + v->y*v->y + v->z*v->z > 1.0);
	return v;
}

INLINE vec3f_t* math3d_make3f_vec3f(vec3f_t *v, const GLfloat x, const GLfloat y, const GLfloat z){
	v->x = x;
	v->y = y;
	v->z = z;
	return v;
}

INLINE vec3f_t* math3d_make2v_vec3f(vec3f_t *v, const vec3f_t *to, const vec3f_t *from){
	v->x = to->x - from->x;
	v->y = to->y - from->y;
	v->z = to->z - from->z;
	return v;
}

// vec3f_t combination operations
INLINE GLfloat math3d_distance_vec3f(const vec3f_t *a, const vec3f_t *b){
	return sqrt( pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + 
				pow(a->z - b->z, 2));
}

INLINE double math3d_distancesq_vec3f(vec3f_t *a, vec3f_t *b){
	return pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + 
				pow(a->z - b->z, 2);
}

INLINE GLfloat math3d_angle_vec3f(const vec3f_t *a, const vec3f_t *b) {
	return acos(math3d_dot_vec3f(a,b) / math3d_length_vec3f(a) / math3d_length_vec3f(b));
}

INLINE vec3f_t* math3d_reflect_vec3f(vec3f_t *dest, const vec3f_t *incoming, const vec3f_t *normal){
	GLfloat dp;
	dp = 2*math3d_dot_vec3f(normal, incoming);

	dest->x = incoming->x - dp*normal->x;
	dest->y = incoming->y - dp*normal->y;
	dest->z = incoming->z - dp*normal->z;
	
	return dest;
}
