#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math3d.h"


#ifndef __FILE_OBJ_LOADER__
#define __FILE_OBJ_LOADER__

/*
// Based on GLM by Nate Robins 1997, 2000 http://www.pobox.com/~nate  (a big thank you!)
*/

// Reads a model description from a Wavefront .OBJ file. Returns a pointer to the created object which should be free'd with objloader_delete_obj_file()
model_t* objloader_read_obj_file(char* filename);

// Deletes a model_t structure
GLvoid objloader_delete_obj_file(model_t* model);

// "Unitize" a model by scaling it to fit in a unit cube around the origin.  Returns the scalefactor used
GLfloat objloader_unitize_obj(model_t* model);

// Generates facet normals for a model. Assumes a counter-clockwise winding
GLvoid objloader_facet_normals(model_t* model);

// Generates smooth vertex normals for a model. The angle to use depends on the model, but 90 degrees is usually a good start
GLvoid objloader_vertex_normals(model_t* model, GLfloat angle);

// Renders the model to the current OpenGL context
GLvoid objloader_draw_obj(model_t* model);


#endif
