#include "s_camera.h"

#ifndef __G_GAME__
#define __G_GAME__

//
// GAME
//

//global variables
typedef struct {
  //window size
  const SDL_VideoInfo *videoInfo;
  
  //keyboard state
  Uint8 *keystate;
  
  //mouse movement state
  int mousestate[4];
  
  //main camera
  s_camera_t camera;
  
  //perspective variables
  GLfloat fovy;
  
  //translation variables
  GLfloat xMove;
  GLfloat yMove;
  GLfloat zMove;

  // Rotation amounts
  GLfloat xRot;
  GLfloat yRot;

  //are we done playing?
  int gameDone;
  
} g_resources_t;

extern g_resources_t g_resources;


//function prototypes
void game_init_resources(void);

void game_ticker(void);

//void game_independent_ticker(Uint32);
void game_independent_ticker(void);

void game_handle_keyboard(Uint8 *keystate);

void game_handle_mouse(int *mousestate);

#endif