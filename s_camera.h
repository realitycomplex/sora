#ifndef __S_CAMERA__
#define __S_CAMERA__


typedef struct {
	GLfloat	matrix[16];
	GLfloat	pos[3];
	GLfloat	pitch;
	GLfloat	jaw;
	GLfloat	pitch_goal;
	GLfloat	jaw_goal;
	GLfloat	speed;
	GLfloat	side_speed;
} s_camera_t;

void s_CameraCompute(s_camera_t *camera, float deltaTime);
void s_CameraInit(s_camera_t *camera);
void s_CameraPerspective( GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar );
void s_CameraSet(s_camera_t *camera);
void s_ComputeMatrix(GLfloat *matrix);

#endif