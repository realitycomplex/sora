#ifndef __OPENGL_STRUCTS__
#define __OPENGL_STRUCTS__

/*
// Based on GLM by Nate Robins 1997, 2000 http://www.pobox.com/~nate  (a big thank you!)
*/

// define vector structures for float
typedef struct vec3f_s{
	GLfloat x;                  // x component
	GLfloat y;                  // y component
	GLfloat z;                  // z component
} vec3f_t;

// define triangle structure
typedef struct triangle_s{
  GLfloat x, y, z;            // vertex component
  GLfloat nx, ny, nz;         // normal component
  GLfloat s0, t0;             // texcoord0 component
  GLfloat s1, t1;             // texcoord1 component
  GLfloat s2, t2;             // texcoord2 component
  GLfloat padding[4];
} triangle_t;

// define material structure
typedef struct material_s{
  char* name;                 // name of material
  GLfloat diffuse[4];         // diffuse component 
  GLfloat ambient[4];         // ambient component 
  GLfloat specular[4];        // specular component
  GLfloat emmissive[4];       // emmissive component
  GLfloat shininess;          // specular exponent 
} material_t;

// structure that defines a group in a model
typedef struct tri_group_s{
  char* name;                 // name of this group
  GLuint numtriangles;        // number of triangles in this group
  GLuint* triangles;          // array of triangle indices
  GLuint material;            // index to material for group 
} tri_group_t;

// define model structure
typedef struct model_s{
  char* pathname;             // path to this model
  char* mtllibname;           // name of the material library

  GLuint numvertices;         // number of vertices in model
  GLfloat* vertices;          // array of vertices

  GLuint numnormals;          // number of normals in model
  GLfloat* normals;           // array of normals

  GLuint numtexcoords;        // number of texcoords in model
  GLfloat* texcoords;         // array of texture coordinates

  GLuint numfacetnorms;       // number of facetnorms in model
  GLfloat* facetnorms;        // array of facetnorms

  GLuint numtriangles;        // number of triangles in model
  triangle_t* triangles;     // array of triangles

  GLuint nummaterials;        // number of materials in model
  material_t* materials;     // array of materials

  GLuint numgroups;           // number of groups in model
  tri_group_t* groups;           // linked list of groups

  GLfloat position[3];        // position of the model

} model_t;

#endif

