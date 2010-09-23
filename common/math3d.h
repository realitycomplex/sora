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
#define EPSILON 0.00001f
#endif

// arithmetic operations
INLINE vec3f_t* math3d_add_vec3f(vec3f_t *dest, const vec3f_t *v1, const vec3f_t *v2);
INLINE vec3f_t* math3d_subtract_vec3f(vec3f_t *dest, const vec3f_t *minuend, const vec3f_t *subtrahend);
INLINE vec3f_t* math3d_multiply_vec3f(vec3f_t *dest, const vec3f_t *v, const GLfloat n);
INLINE vec3f_t* math3d_divide_vec3f(vec3f_t *dest, const vec3f_t *v, const GLfloat n);
INLINE vec3f_t* math3d_scalar_add_vec3f(vec3f_t *dest, const vec3f_t *v, const GLfloat s);
INLINE vec3f_t* math3d_scalar_sub_vec3f(vec3f_t *dest, const vec3f_t *v, const GLfloat s);
INLINE GLfloat math3d_dot_vec3f(const vec3f_t *a, const vec3f_t *b);
INLINE vec3f_t* math3d_cross_vec3f(vec3f_t *dest, const vec3f_t *a, const vec3f_t *b);

// miscellaneous arithmetic functions
INLINE GLfloat math3d_max_2f(GLfloat a, GLfloat b);
INLINE GLfloat math3d_min_2f(GLfloat a, GLfloat b);
INLINE GLfloat math3d_abs_f(GLfloat f);
INLINE GLboolean math3d_equal_2vec3f(const vec3f_t *v1, const vec3f_t *v2);

// unit operations
INLINE GLfloat math3d_length_vec3f(const vec3f_t *a);
INLINE vec3f_t* math3d_normalize_vec3f(vec3f_t *a);
INLINE vec3f_t* math3d_invert_vec3f(vec3f_t *dest, const vec3f_t *v);
INLINE void math3d_print_vec3f(const vec3f_t *v);

// creation
INLINE vec3f_t* math3d_copy_vec3f(vec3f_t *dest, const vec3f_t *source);
INLINE vec3f_t* math3d_random_vec3f(vec3f_t *v);
INLINE vec3f_t* math3d_make3f_vec3f(vec3f_t *v, const GLfloat x, const GLfloat y, const GLfloat z);
INLINE vec3f_t* math3d_make2v_vec3f(vec3f_t *v, const vec3f_t *to, const vec3f_t *from);

// combination operations
INLINE GLfloat math3d_distance_vec3f(const vec3f_t *a, const vec3f_t *b);
INLINE double math3d_distancesq_vec3f(vec3f_t *a, vec3f_t *b);
INLINE GLfloat math3d_angle_vec3f(const vec3f_t *a, const vec3f_t *b);
INLINE vec3f_t* math3d_reflect_vec3f(vec3f_t *dest, const vec3f_t *incoming, const vec3f_t *normal);



#endif
