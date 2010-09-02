#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "g_game.h"
#include "s_camera.h"
#include "s_shared.h"
#include "sora.h"

//game resources
g_resources_t g_resources;

void g_InitResources(){
  g_resources.videoInfo = SDL_GetVideoInfo();
  g_resources.keystate = SDL_GetKeyState(NULL);
  g_resources.fovy = 60.0f;
  g_resources.xMove = 0.0f;
  g_resources.yMove = 0.0f;
  g_resources.zMove = -300.0f;
  g_resources.xRot = 0.0f;
  g_resources.yRot = 0.0f;
  g_resources.gameDone = 0;
  
  s_CameraInit(&g_resources.camera);
  
  return;
}

void g_Ticker(){
  //update game logic here
  //
  //handle keyboard input (updated in g_IndependentTickRun)
  g_HandleKeyboard(g_resources.keystate);
  g_HandleMouse(g_resources.mousestate);
  
  return;
}

void g_IndependentTickRun(){
  //gather user input and do housekeeping
  SDL_Event event;
  
  while ( SDL_PollEvent(&event) ) {
	  switch(event.type){
	    case SDL_KEYDOWN:
  		case SDL_KEYUP:
  		  //update Keyboard state
  		  g_resources.keystate = SDL_GetKeyState(NULL);
  			break;
  		case SDL_MOUSEMOTION:
  		  g_resources.mousestate[2] = event.motion.x - g_resources.mousestate[0];
        g_resources.mousestate[3] = event.motion.y - g_resources.mousestate[1];
        g_resources.mousestate[0] = event.motion.x;
        g_resources.mousestate[1] = event.motion.y;
        break;
  		case SDL_QUIT:
        g_resources.gameDone = 1;
        break;
      default:
        printf("Unhandled Event!\n");
        break;
  	}
  }
  
  return;
}

// Respond to keyboard input
void g_HandleKeyboard(Uint8 *keystate){
    
  if(keystate[SDLK_q])
    g_resources.gameDone = 1;
  
  if(keystate[SDLK_w]){
    g_resources.zMove += 5.0f;
    g_resources.camera.pos[2] += 5.0f;
  }
  
  if(keystate[SDLK_s]){
    g_resources.zMove -= 5.0f;
    g_resources.camera.pos[2] -= 5.0f;
  }
  
  if(keystate[SDLK_a]){
    g_resources.xMove += 5.0f;
    g_resources.camera.pos[0] += 5.0f;
  }
  
  if(keystate[SDLK_d]){
    g_resources.xMove -= 5.0f;
    g_resources.camera.pos[0] -= 5.0f;
  }
    
  return;
}

//Respond to mouse input
void g_HandleMouse(int *mousestate){
  /*
  GLfloat w = (GLfloat)g_resources.videoInfo->current_w;
  GLfloat h = (GLfloat)g_resources.videoInfo->current_h;
  g_resources.xRot = -(GLfloat)mousestate[1];
  g_resources.yRot = (GLfloat)mousestate[0];
  
  g_resources.xRot = (GLfloat)((int)g_resources.xRot % 360);
  g_resources.yRot = (GLfloat)((int)g_resources.yRot % 360);

  printf("w: %f; h: %f; mx: %i; my: %i; xRot: %f; yRot: %f\n", w, h, mousestate[0], mousestate[1], g_resources.xRot, g_resources.yRot);
  */
  float x, y, z;
	
  printf("x: %i; y: %i; xRel: %i; yRel: %i\n", mousestate[0], mousestate[1], mousestate[2], mousestate[3]);
	
  g_resources.camera.matrix[4] = 0;
  g_resources.camera.matrix[5] = 1;
  g_resources.camera.matrix[6] = 0;
  g_resources.camera.pitch += mousestate[3];
  g_resources.camera.jaw += -mousestate[2];
  g_resources.camera.jaw = (float)((int)g_resources.camera.jaw % 360);
  g_resources.camera.pitch = (float)((int)g_resources.camera.pitch % 360);
  /*
  if(g_resources.camera.pitch > M_PI * 0.499)
    g_resources.camera.pitch = M_PI * 0.499;
  if(g_resources.camera.pitch < -M_PI * 0.499)
    g_resources.camera.pitch = -M_PI * 0.499;
  */
  y = cos(g_resources.camera.pitch * M_PI / 180);
  g_resources.camera.matrix[8] = sin(g_resources.camera.jaw * M_PI / 180) * y;
  g_resources.camera.matrix[9] = sin(g_resources.camera.pitch) ;
  g_resources.camera.matrix[10] = cos(g_resources.camera.jaw * M_PI / 180) * y;
  
  s_ComputeMatrix(g_resources.camera.matrix);
  
  printf("jaw: %f; pitch: %f\n", g_resources.camera.jaw, g_resources.camera.pitch);
  
  return;
}
