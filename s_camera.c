#include <math.h>
#include "SDL/SDL_opengl.h"

#include "s_camera.h"
#include "common/s_shared.h"


void s_CameraCompute(s_camera_t *camera, float deltaTime){
	GLfloat x, y, z;
	
	x = 0;
	y = 0;
	/*
	if(w || input->mouse_button[1])
		camera->speed++;
	if(s)
		camera->speed--;
	if(a)
		camera->side_speed++;
	if(d)
		camera->side_speed--;
  */
  
	camera->speed *= 0.9;
	camera->side_speed *= 0.9;

	camera->pos[0] -= camera->matrix[8] * deltaTime * camera->speed;
	camera->pos[1] -= camera->matrix[9] * deltaTime * camera->speed;
	camera->pos[2] -= camera->matrix[10] * deltaTime * camera->speed;
	camera->pos[0] -= camera->matrix[0] * deltaTime * camera->side_speed;
	camera->pos[1] -= camera->matrix[1] * deltaTime * camera->side_speed;
	camera->pos[2] -= camera->matrix[2] * deltaTime * camera->side_speed;

}


void s_CameraInit(s_camera_t *camera){
	int i;
	for(i = 0; i < 16; i++){
		if(i % 5 == 0)
			camera->matrix[i] = 1;
		else
			camera->matrix[i] = 0;
	}
	camera->pos[0] = 0;
	camera->pos[1] = 0;
	camera->pos[2] = 0;
	camera->pitch = 0;
	camera->jaw = 0;
	camera->pitch_goal = 0;
	camera->jaw_goal = 0;
	camera->pitch_goal = 0;
	camera->jaw_goal = 0;
	
  return;
}

void s_CameraPerspective( GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar ){
  GLdouble xmin, xmax, ymin, ymax;

  ymax = zNear * tanf( fovy * M_PI / 360.0 );
  ymin = -ymax;

  xmin = ymin * aspect;
  xmax = ymax * aspect;

  glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}

void s_CameraSet(s_camera_t *camera){
	double matrix[16];
	matrix[0] = camera->matrix[0];
	matrix[1] = camera->matrix[4];
	matrix[2] = camera->matrix[8];
	matrix[3] = camera->matrix[12];
	matrix[4] = camera->matrix[1];
	matrix[5] = camera->matrix[5];
	matrix[6] = camera->matrix[9];
	matrix[7] = camera->matrix[13];
	matrix[8] = camera->matrix[2];
	matrix[9] = camera->matrix[6];
	matrix[10] = camera->matrix[10];
	matrix[11] = camera->matrix[14];
	matrix[12] = camera->matrix[3];
	matrix[13] = camera->matrix[7];
	matrix[14] = camera->matrix[11];
	matrix[15] = camera->matrix[15];

	glMultMatrixd(matrix);
	glTranslatef(camera->pos[0], camera->pos[1], camera->pos[2]);
	
  return;
}

void s_ComputeMatrix(GLfloat *matrix){
	GLfloat r;
	r = sqrt(matrix[8] * matrix[8] + matrix[9] * matrix[9] + matrix[10] * matrix[10]);
	matrix[8] = matrix[8] / r;
	matrix[9] = matrix[9] / r;
	matrix[10] = matrix[10] / r;
	matrix[0] = matrix[5] * matrix[10] - matrix[6] * matrix[9];
	matrix[1] = matrix[6] * matrix[8] - matrix[4] * matrix[10];
	matrix[2] = matrix[4] * matrix[9] - matrix[5] * matrix[8];
	r = sqrt(matrix[0] * matrix[0] + matrix[1] * matrix[1] + matrix[2] * matrix[2]);
	matrix[0] = matrix[0] / r;
	matrix[1] = matrix[1] / r;
	matrix[2] = matrix[2] / r;
	matrix[4] = matrix[9] * matrix[2] - matrix[10] * matrix[1];
	matrix[5] = matrix[10] * matrix[0] - matrix[8] * matrix[2];
	matrix[6] = matrix[8] * matrix[1] - matrix[9] * matrix[0];
}
