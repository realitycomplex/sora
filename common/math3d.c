#include "SDL/SDL_opengl.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math3d.h"

// arithmetic operations
INLINE vec3f* math3d_vec3f_add(vec3f *dest, const vec3f *v1, const vec3f *v2)
{
	dest->x = v1->x + v2->x;
	dest->y = v1->y + v2->y;
	dest->z = v1->z + v2->z;
	return dest;
}

INLINE vec3f* math3d_vec3f_subtract(vec3f *dest, const vec3f *minuend, const vec3f *subtrahend)
{
	dest->x = minuend->x - subtrahend->x;
	dest->y = minuend->y - subtrahend->y;
	dest->z = minuend->z - subtrahend->z;
	return dest;
}

INLINE vec3f* math3d_vec3f_multiply(vec3f *dest, const vec3f *v, const GLfloat n)
{
	dest->x = v->x * n;
	dest->y = v->y * n;
	dest->z = v->z * n;
	return dest;
}

INLINE vec3f* math3d_vec3f_divide(vec3f *dest, const vec3f *v,const  GLfloat n)
{
	dest->x = v->x / n;
	dest->y = v->y / n;
	dest->z = v->z / n;
	return dest;
}

INLINE vec3f *math3d_vec3f_scalar_add(vec3f *dest, const vec3f *v, const GLfloat s)
{
	dest->x = v->x + s;
	dest->y = v->y + s;
	dest->z = v->z + s;
	return dest;
}

INLINE vec3f *math3d_vec3f_scalar_sub(vec3f *dest, const vec3f *v, const GLfloat s)
{
	dest->x = v->x - s;
	dest->y = v->y - s;
	dest->z = v->z - s;
	return dest;
}

INLINE GLfloat math3d_vec3f_dot(const vec3f *a, const vec3f *b)
{
	return a->x*b->x + a->y*b->y + a->z*b->z;
}

INLINE vec3f* math3d_vec3f_cross(vec3f *dest, const vec3f *a, const vec3f *b)
{
	dest->x = a->y*b->z - a->z*b->y;
	dest->y = a->z*b->x - a->x*b->z;
	dest->z = a->x*b->y - a->y*b->x;
	
	return dest;
}

// vec3f unit operations
INLINE GLfloat math3d_vec3f_length(const vec3f *a)
{
	return sqrt(a->x*a->x + a->y*a->y + a->z*a->z);
}

INLINE vec3f* math3d_vec3f_normalize(vec3f *a)
{
	GLfloat normalizeLength;
	normalizeLength = math3d_vec3f_length(a);
	
	if(normalizeLength <= EPSILON)
	{
		printf("cannot normalize degenerate vec3f\n");
		return a;
	}
	
	math3d_vec3f_divide(a, a, normalizeLength);
	return a;
}

INLINE vec3f* math3d_vec3f_invert(vec3f *dest, const vec3f *v)
{
	dest->x = -v->x;
	dest->y = -v->y;
	dest->z = -v->z;
	return dest;
}

INLINE void math3d_vec3f_print(const vec3f *v)
{
	printf("%.2f %.2f %.2f\n", v->x, v->y, v->z);
}

// vec3f creation
INLINE vec3f* math3d_vec3f_copy(vec3f *dest, const vec3f *source)
{
	dest->x = source->x;
	dest->y = source->y;
	dest->z = source->z;
	return dest;
}

INLINE vec3f* math3d_vec3f_random(vec3f *v)
{
	do {
		v->x = (double)rand()/RAND_MAX*2-1;
		v->y = (double)rand()/RAND_MAX*2-1;
		v->z = (double)rand()/RAND_MAX*2-1;
	} while (v->x*v->x + v->y*v->y + v->z*v->z > 1.0);
	return v;
}

INLINE vec3f* math3d_vec3f_make3f(vec3f *v, const GLfloat x, const GLfloat y, const GLfloat z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	return v;
}

INLINE vec3f* math3d_vec3f_make2v(vec3f *v, const vec3f *to, const vec3f *from)
{
	v->x = to->x - from->x;
	v->y = to->y - from->y;
	v->z = to->z - from->z;
	return v;
}

// vec3f combination operations
INLINE GLfloat math3d_vec3f_distance(const vec3f *a, const vec3f *b)
{
	return sqrt( pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + 
				pow(a->z - b->z, 2));
}

INLINE double math3d_vec3f_distancesq(vec3f *a, vec3f *b)
{
	return pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + 
				pow(a->z - b->z, 2);
}

INLINE GLfloat math3d_vec3f_angle(const vec3f *a, const vec3f *b) 
{
	return acos(math3d_vec3f_dot(a,b) / math3d_vec3f_length(a) / math3d_vec3f_length(b));
}

INLINE vec3f* math3d_vec3f_reflect(vec3f *dest, const vec3f *incoming, const vec3f *normal)
{
	GLfloat dp;
	dp = 2*math3d_vec3f_dot(normal, incoming);

	dest->x = incoming->x - dp*normal->x;
	dest->y = incoming->y - dp*normal->y;
	dest->z = incoming->z - dp*normal->z;
	
	return dest;
}
