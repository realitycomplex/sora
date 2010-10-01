#include "file_utils.h"
#include "file_obj_loader.h"


// Shortcut to access a triangle
#define T(x) (model->triangles[(x)])

// Find a group in the model
tri_group_t* objLoader_find_group(model_t* model, char* name) {
  tri_group_t* group;
  
  group = model->groups;
  while(group) {
    if (!strcmp(name, group->name)) break;
    group = group->next;
  }
  
  return group;
}

// Add a group to the model
tri_group_t* objLoader_add_group(model_t* model, char* name) {
  tri_group_t* group;
  
  group = objLoader_find_group(model, name);
  if (!group) {
    group = (tri_group_t*)malloc(sizeof(tri_group_t));
    group->name = strdup(name);
    group->material = 0;
    group->numtriangles = 0;
    group->triangles = NULL;
    group->next = model->groups;
    model->groups = group;
    model->numgroups++;
  }
  
  return group;
}

// Read a wavefront material library file
static GLvoid objLoader_read_mtl_file(model_t* model, char* name) {
  FILE* file;
  char* dir;
  char* filename;
  char buf[128];
  GLuint nummaterials;
  int i;
    
  dir = fileUtils_dir_name(model->pathname);
  filename = (char*)malloc(sizeof(char) * (strlen(dir) + strlen(name) + 1));
  strcpy(filename, dir);
  strcat(filename, name);
  free(dir);
    
  file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "objLoader_read_mtl_file() failed: can't open material file \"%s\".\n", filename);
    exit(1);
  }
  free(filename);
    
  // count the number of materials in the file 
  nummaterials = 1;
  while(fscanf(file, "%s", buf) != EOF) {
    switch(buf[0]) {
      case '#':               /* comment */
        /* eat up rest of line */
        fgets(buf, sizeof(buf), file);
        break;
      case 'n':               /* newmtl */
        fgets(buf, sizeof(buf), file);
        nummaterials++;
        sscanf(buf, "%s %s", buf, buf);
        break;
      default:
        /* eat up rest of line */
        fgets(buf, sizeof(buf), file);
        break;
    }
  }
    
  rewind(file);
    
  model->materials = (material_t*)malloc(sizeof(material_t) * nummaterials);
  model->nummaterials = nummaterials;
    
  // set the default material
  for (i = 0; i < nummaterials; i++) {
    model->materials[i].name = NULL;
    model->materials[i].shininess = 65.0;
    model->materials[i].diffuse[0] = 0.8;
    model->materials[i].diffuse[1] = 0.8;
    model->materials[i].diffuse[2] = 0.8;
    model->materials[i].diffuse[3] = 1.0;
    model->materials[i].ambient[0] = 0.2;
    model->materials[i].ambient[1] = 0.2;
    model->materials[i].ambient[2] = 0.2;
    model->materials[i].ambient[3] = 1.0;
    model->materials[i].specular[0] = 0.0;
    model->materials[i].specular[1] = 0.0;
    model->materials[i].specular[2] = 0.0;
    model->materials[i].specular[3] = 1.0;
  }
  model->materials[0].name = strdup("default");
    
  // read in the data
  nummaterials = 0;
  while(fscanf(file, "%s", buf) != EOF) {
    switch(buf[0]) {
      case '#':               /* comment */
        /* eat up rest of line */
        fgets(buf, sizeof(buf), file);
        break;
      case 'n':               /* newmtl */
        fgets(buf, sizeof(buf), file);
        sscanf(buf, "%s %s", buf, buf);
        nummaterials++;
        model->materials[nummaterials].name = strdup(buf);
        break;
      case 'N':
        fscanf(file, "%f", &model->materials[nummaterials].shininess);
        /* wavefront shininess is from [0, 1000], so scale for OpenGL */
        model->materials[nummaterials].shininess /= 1000.0;
        model->materials[nummaterials].shininess *= 128.0;
        break;
      case 'K':
        switch(buf[1]) {
          case 'd':
            fscanf(file, "%f %f %f",
              &model->materials[nummaterials].diffuse[0],
              &model->materials[nummaterials].diffuse[1],
              &model->materials[nummaterials].diffuse[2]);
            break;
          case 's':
            fscanf(file, "%f %f %f",
              &model->materials[nummaterials].specular[0],
              &model->materials[nummaterials].specular[1],
              &model->materials[nummaterials].specular[2]);
            break;
          case 'a':
            fscanf(file, "%f %f %f",
              &model->materials[nummaterials].ambient[0],
              &model->materials[nummaterials].ambient[1],
              &model->materials[nummaterials].ambient[2]);
            break;
          default:
            /* eat up rest of line */
            fgets(buf, sizeof(buf), file);
            break;
        }
        break;
      default:
        /* eat up rest of line */
        fgets(buf, sizeof(buf), file);
        break;
    }
  }

  //close mtl file
  fclose(file);
}

// objLoader_first_pass: first pass at a Wavefront OBJ file that gets the object counts in the model
static GLvoid objLoader_first_pass(model_t* model, FILE* file) {
  GLuint numvertices;
  GLuint numnormals;
  GLuint numtexcoords;
  GLuint numtriangles;
  tri_group_t* group;
  int v, n, t;
  char buf[128];
    
  // make a default group
  group = objLoader_add_group(model, "default");
    
  numvertices = numnormals = numtexcoords = numtriangles = 0;
  while(fscanf(file, "%s", buf) != EOF) {
    switch(buf[0]) {
      case '#':               /* comment */
        /* eat up rest of line */
        fgets(buf, sizeof(buf), file);
        break;
      
      case 'v':               /* v, vn, vt */
        switch(buf[1]) {
          case '\0':          /* vertex */
            /* eat up rest of line */
            fgets(buf, sizeof(buf), file);
            numvertices++;
            break;
          
          case 'n':           /* normal */
            /* eat up rest of line */
            fgets(buf, sizeof(buf), file);
            numnormals++;
            break;
          
          case 't':           /* texcoord */
            /* eat up rest of line */
            fgets(buf, sizeof(buf), file);
            numtexcoords++;
            break;
          
          default:
            printf("objLoader_first_pass(): Unknown token \"%s\".\n", buf);
            exit(1);
            break;
        }
        break;
        
      case 'm':
        fgets(buf, sizeof(buf), file);
        sscanf(buf, "%s %s", buf, buf);
        model->mtllibname = strdup(buf);
        objLoader_read_mtl_file(model, buf);
        break;

      case 'u':
        /* eat up rest of line */
        fgets(buf, sizeof(buf), file);
        break;
      
      case 'g':               /* group */
        /* eat up rest of line */
        fgets(buf, sizeof(buf), file);
        buf[strlen(buf)-1] = '\0';  /* nuke '\n' */
        group = objLoader_add_group(model, buf);
        break;
      
      case 'f':               /* face */
        v = n = t = 0;
        fscanf(file, "%s", buf);
        /* can be one of %d, %d//%d, %d/%d, %d/%d/%d %d//%d */
        if (strstr(buf, "//")) {
          /* v//n */
          sscanf(buf, "%d//%d", &v, &n);
          fscanf(file, "%d//%d", &v, &n);
          fscanf(file, "%d//%d", &v, &n);
          numtriangles++;
          group->numtriangles++;
          while(fscanf(file, "%d//%d", &v, &n) > 0) {
            numtriangles++;
            group->numtriangles++;
          }
        } 
        else if (sscanf(buf, "%d/%d/%d", &v, &t, &n) == 3) {
          /* v/t/n */
          fscanf(file, "%d/%d/%d", &v, &t, &n);
          fscanf(file, "%d/%d/%d", &v, &t, &n);
          numtriangles++;
          group->numtriangles++;
          while(fscanf(file, "%d/%d/%d", &v, &t, &n) > 0) {
            numtriangles++;
            group->numtriangles++;
          }
        } 
        else if (sscanf(buf, "%d/%d", &v, &t) == 2) {
          /* v/t */
          fscanf(file, "%d/%d", &v, &t);
          fscanf(file, "%d/%d", &v, &t);
          numtriangles++;
          group->numtriangles++;
          while(fscanf(file, "%d/%d", &v, &t) > 0) {
            numtriangles++;
            group->numtriangles++;
          }
        } 
        else {
          /* v */
          fscanf(file, "%d", &v);
          fscanf(file, "%d", &v);
          numtriangles++;
          group->numtriangles++;
          while(fscanf(file, "%d", &v) > 0) {
            numtriangles++;
            group->numtriangles++;
          }
        }
        break;
      
      default:
        /* eat up rest of line */
        fgets(buf, sizeof(buf), file);
        break;
    }
  }
  
  // set the stats in the model structure
  model->numvertices = numvertices;
  model->numnormals = numnormals;
  model->numtexcoords = numtexcoords;
  model->numtriangles = numtriangles;
  
  // allocate memory for the triangles in each group
  group = model->groups;
  while(group) {
    group->triangles = (GLuint*)malloc(sizeof(GLuint) * group->numtriangles);
    group->numtriangles = 0;
    group = group->next;
  }
}

// second pass at a Wavefront OBJ file that reads the data into the model structure
static GLvoid objLoader_second_pass(GLMmodel* model, FILE* file) 
{
  GLuint numvertices;       
  GLuint numnormals;         
  GLuint numtexcoords;     
  GLuint numtriangles; 
  GLfloat* vertices; 
  GLfloat* normals; 
  GLfloat* texcoords; 
  tri_group_t* group;
  GLuint material;
  int v, n, t;
  char buf[128];
    
  // set the pointer shortcuts
  vertices = model->vertices;
  normals = model->normals;
  texcoords = model->texcoords;
  group = model->groups;
    
  // read all the data into the allocated arrays
  numvertices = numnormals = numtexcoords = 1;
  numtriangles = 0;
  material = 0;
  while(fscanf(file, "%s", buf) != EOF) {
    switch(buf[0]) {
      case '#':               /* comment */
        /* eat up rest of line */
        fgets(buf, sizeof(buf), file);
        break;
      
      case 'v':               /* v, vn, vt */
        switch(buf[1]) {
          case '\0':          /* vertex */
            fscanf(file, "%f %f %f", 
              &vertices[3 * numvertices + 0], 
              &vertices[3 * numvertices + 1], 
              &vertices[3 * numvertices + 2]);
            numvertices++;
            break;
          case 'n':           /* normal */
            fscanf(file, "%f %f %f", 
              &normals[3 * numnormals + 0],
              &normals[3 * numnormals + 1], 
              &normals[3 * numnormals + 2]);
            numnormals++;
            break;
          case 't':           /* texcoord */
            fscanf(file, "%f %f", 
              &texcoords[2 * numtexcoords + 0],
              &texcoords[2 * numtexcoords + 1]);
            numtexcoords++;
            break;
        }
        break;
      
      case 'u':
        fgets(buf, sizeof(buf), file);
        sscanf(buf, "%s %s", buf, buf);
        group->material = material = glmFindMaterial(model, buf);
        break;
      case 'g':               /* group */
        /* eat up rest of line */
        fgets(buf, sizeof(buf), file);
        buf[strlen(buf)-1] = '\0';  /* nuke '\n' */
        group = glmFindGroup(model, buf);
        group->material = material;
        break;
      case 'f':               /* face */
        v = n = t = 0;
        fscanf(file, "%s", buf);
        /* can be one of %d, %d//%d, %d/%d, %d/%d/%d %d//%d */
        if (strstr(buf, "//")) {
          /* v//n */
          sscanf(buf, "%d//%d", &v, &n);
          T(numtriangles).vect[0] = v < 0 ? v + numvertices : v;
          T(numtriangles).norm[0] = n < 0 ? n + numnormals : n;
          fscanf(file, "%d//%d", &v, &n);
          T(numtriangles).vect[1] = v < 0 ? v + numvertices : v;
          T(numtriangles).norm[1] = n < 0 ? n + numnormals : n;
          fscanf(file, "%d//%d", &v, &n);
          T(numtriangles).vect[2] = v < 0 ? v + numvertices : v;
          T(numtriangles).norm[2] = n < 0 ? n + numnormals : n;
          group->triangles[group->numtriangles++] = numtriangles;
          numtriangles++;
          while(fscanf(file, "%d//%d", &v, &n) > 0) {
            T(numtriangles).vect[0] = T(numtriangles-1).vect[0];
            T(numtriangles).norm[0] = T(numtriangles-1).norm[0];
            T(numtriangles).vect[1] = T(numtriangles-1).vect[2];
            T(numtriangles).norm[1] = T(numtriangles-1).norm[2];
            T(numtriangles).vect[2] = v < 0 ? v + numvertices : v;
            T(numtriangles).norm[2] = n < 0 ? n + numnormals : n;
            group->triangles[group->numtriangles++] = numtriangles;
            numtriangles++;
          }
        } 
        else if (sscanf(buf, "%d/%d/%d", &v, &t, &n) == 3) {
          /* v/t/n */
          T(numtriangles).vect[0] = v < 0 ? v + numvertices : v;
          T(numtriangles).texc[0] = t < 0 ? t + numtexcoords : t;
          T(numtriangles).norm[0] = n < 0 ? n + numnormals : n;
          fscanf(file, "%d/%d/%d", &v, &t, &n);
          T(numtriangles).vect[1] = v < 0 ? v + numvertices : v;
          T(numtriangles).texc[1] = t < 0 ? t + numtexcoords : t;
          T(numtriangles).norm[1] = n < 0 ? n + numnormals : n;
          fscanf(file, "%d/%d/%d", &v, &t, &n);
          T(numtriangles).vect[2] = v < 0 ? v + numvertices : v;
          T(numtriangles).texc[2] = t < 0 ? t + numtexcoords : t;
          T(numtriangles).norm[2] = n < 0 ? n + numnormals : n;
          group->triangles[group->numtriangles++] = numtriangles;
          //HERE - NOTE: still need to work on logic in creating triangles. this is just organizing the code.
                    numtriangles++;
                    while(fscanf(file, "%d/%d/%d", &v, &t, &n) > 0) {
                        T(numtriangles).vect[0] = T(numtriangles-1).vect[0];
                        T(numtriangles).texc[0] = T(numtriangles-1).texc[0];
                        T(numtriangles).norm[0] = T(numtriangles-1).norm[0];
                        T(numtriangles).vect[1] = T(numtriangles-1).vect[2];
                        T(numtriangles).texc[1] = T(numtriangles-1).texc[2];
                        T(numtriangles).norm[1] = T(numtriangles-1).norm[2];
                        T(numtriangles).vect[2] = v < 0 ? v + numvertices : v;
                        T(numtriangles).texc[2] = t < 0 ? t + numtexcoords : t;
                        T(numtriangles).norm[2] = n < 0 ? n + numnormals : n;
                        group->triangles[group->numtriangles++] = numtriangles;
                        numtriangles++;
                    }
                } else if (sscanf(buf, "%d/%d", &v, &t) == 2) {
                    /* v/t */
                    T(numtriangles).vect[0] = v < 0 ? v + numvertices : v;
                    T(numtriangles).texc[0] = t < 0 ? t + numtexcoords : t;
                    fscanf(file, "%d/%d", &v, &t);
                    T(numtriangles).vect[1] = v < 0 ? v + numvertices : v;
                    T(numtriangles).texc[1] = t < 0 ? t + numtexcoords : t;
                    fscanf(file, "%d/%d", &v, &t);
                    T(numtriangles).vect[2] = v < 0 ? v + numvertices : v;
                    T(numtriangles).texc[2] = t < 0 ? t + numtexcoords : t;
                    group->triangles[group->numtriangles++] = numtriangles;
                    numtriangles++;
                    while(fscanf(file, "%d/%d", &v, &t) > 0) {
                        T(numtriangles).vect[0] = T(numtriangles-1).vect[0];
                        T(numtriangles).texc[0] = T(numtriangles-1).texc[0];
                        T(numtriangles).vect[1] = T(numtriangles-1).vect[2];
                        T(numtriangles).texc[1] = T(numtriangles-1).texc[2];
                        T(numtriangles).vect[2] = v < 0 ? v + numvertices : v;
                        T(numtriangles).texc[2] = t < 0 ? t + numtexcoords : t;
                        group->triangles[group->numtriangles++] = numtriangles;
                        numtriangles++;
                    }
                } else {
                    /* v */
                    sscanf(buf, "%d", &v);
                    T(numtriangles).vect[0] = v < 0 ? v + numvertices : v;
                    fscanf(file, "%d", &v);
                    T(numtriangles).vect[1] = v < 0 ? v + numvertices : v;
                    fscanf(file, "%d", &v);
                    T(numtriangles).vect[2] = v < 0 ? v + numvertices : v;
                    group->triangles[group->numtriangles++] = numtriangles;
                    numtriangles++;
                    while(fscanf(file, "%d", &v) > 0) {
                        T(numtriangles).vect[0] = T(numtriangles-1).vect[0];
                        T(numtriangles).vect[1] = T(numtriangles-1).vect[2];
                        T(numtriangles).vect[2] = v < 0 ? v + numvertices : v;
                        group->triangles[group->numtriangles++] = numtriangles;
                        numtriangles++;
                    }
                }
                break;
                
            default:
                /* eat up rest of line */
                fgets(buf, sizeof(buf), file);
                break;
    }
  }
}

// Deletes a model_t structure
GLvoid objLoader_delete_obj_file(model_t* model){
  tri_group_t* group;
  int i;
    
  if (model->pathname) free(model->pathname);
  if (model->mtllibname) free(model->mtllibname);
  if (model->vertices) free(model->vertices);
  if (model->normals) free(model->normals);
  if (model->texcoords) free(model->texcoords);
  if (model->facetnorms) free(model->facetnorms);
  if (model->triangles) free(model->triangles);
  if (model->materials) {
    for (i = 0; i < model->nummaterials; i++)
      free(model->materials[i].name);
  }
  free(model->materials);
  while(model->groups) {
    group = model->groups;
    model->groups = model->groups->next;
    free(group->name);
    free(group->triangles);
    free(group);
  }
  
  free(model);
}

// Reads a model description from a Wavefront .OBJ file. Returns a pointer to the created object which should be free'd with objLoader_delete_obj_file().
model_t* objLoader_read_obj_file(char* filename){
  model_t* model;
  FILE* file;
  
  // open the file
  file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "objLoader_read_obj_file() failed: can't open data file \"%s\".\n", filename);
    exit(1);
  }
  
  // allocate a new model
  model = (model_t*)malloc(sizeof(model_t));
  model->pathname = strdup(filename);
  model->mtllibname = NULL;
  model->numvertices = 0;
  model->vertices = NULL;
  model->numnormals = 0;
  model->normals = NULL;
  model->numtexcoords = 0;
  model->texcoords = NULL;
  model->numfacetnorms = 0;
  model->facetnorms = NULL;
  model->numtriangles = 0;
  model->triangles = NULL;
  model->nummaterials = 0;
  model->materials = NULL;
  model->numgroups = 0;
  model->groups = NULL;
  model->position[0] = 0.0;
  model->position[1] = 0.0;
  model->position[2] = 0.0;
  
  // make a first pass through the file to get a count of the number of vertices, normals, texcoords & triangles
  objLoader_first_pass(model, file);

  // allocate memory
  model->vertices = (GLfloat*)malloc(sizeof(GLfloat) * 3 * (model->numvertices + 1));
  model->triangles = (tri_group_t*)malloc(sizeof(tri_group_t) * model->numtriangles);
  if (model->numnormals) {
    model->normals = (GLfloat*)malloc(sizeof(GLfloat) * 3 * (model->numnormals + 1));
  }
  if (model->numtexcoords) {
    model->texcoords = (GLfloat*)malloc(sizeof(GLfloat) * 2 * (model->numtexcoords + 1));
  }
  
  // rewind to beginning of file
  rewind(file);
  
  // read in the data with the 2nd pass
  //HERE
  glmSecondPass(model, file);
  
  // close the file
  fclose(file);
  
  return model;
}
