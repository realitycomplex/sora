#ifndef __MATH3D__
#define __MATH3D__

/*
// Based on Vector3 from http://kixor.net/  (a big thank you!)
*/

// define a version of PI
#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif


// inlining definition
#ifndef INLINE
//#define INLINE
# if __GNUC__ && !__GNUC_STDC_INLINE__
#  define INLINE extern inline
# else
#  define INLINE inline
# endif
#endif


// set an epsilon if not set
#ifndef EPSILON
#define EPSILON 0.001f
#endif

// define vector structures for float
typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} vec3f;

// arithmetic operations
INLINE vec3f* math3d_vec3f_add(vec3f *dest, const vec3f *v1, const vec3f *v2);
INLINE vec3f* math3d_vec3f_subtract(vec3f *dest, const vec3f *minuend, const vec3f *subtrahend);
INLINE vec3f* math3d_vec3f_multiply(vec3f *dest, const vec3f *v, const GLfloat n);
INLINE vec3f* math3d_vec3f_divide(vec3f *dest, const vec3f *v, const GLfloat n);
INLINE vec3f* math3d_vec3f_scalar_add(vec3f *dest, const vec3f *v, const GLfloat s);
INLINE vec3f* math3d_vec3f_scalar_sub(vec3f *dest, const vec3f *v, const GLfloat s);
INLINE GLfloat math3d_vec3f_dot(const vec3f *a, const vec3f *b);
INLINE vec3f* math3d_vec3f_cross(vec3f *dest, const vec3f *a, const vec3f *b);

// unit operations
INLINE GLfloat math3d_vec3f_length(const vec3f *a);
INLINE vec3f* math3d_vec3f_normalize(vec3f *a);
INLINE vec3f* math3d_vec3f_invert(vec3f *dest, const vec3f *v);
INLINE void math3d_vec3f_print(const vec3f *v);

// creation
INLINE vec3f* math3d_vec3f_copy(vec3f *dest, const vec3f *source);
INLINE vec3f* math3d_vec3f_random(vec3f *v);
INLINE vec3f* math3d_vec3f_make3f(vec3f *v, const GLfloat x, const GLfloat y, const GLfloat z);
INLINE vec3f* math3d_vec3f_make2v(vec3f *v, const vec3f *to, const vec3f *from);

// combination operations
INLINE GLfloat math3d_vec3f_distance(const vec3f *a, const vec3f *b);
INLINE double math3d_vec3f_distancesq(vec3f *a, vec3f *b);
INLINE GLfloat math3d_vec3f_angle(const vec3f *a, const vec3f *b);
INLINE vec3f* math3d_vec3f_reflect(vec3f *dest, const vec3f *incoming, const vec3f *normal);



#endif
