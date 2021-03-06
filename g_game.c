#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "g_game.h"
#include "s_camera.h"
#include "common/math3d.h"
#include "sora.h"

//game resources
g_resources_t g_resources;

void game_init_resources(){
  //get video info
  g_resources.videoInfo = SDL_GetVideoInfo();
  
  //setup mouse and keyboard states
  SDL_PumpEvents();
  g_resources.keystate = SDL_GetKeyState(NULL);
  SDL_GetMouseState(&g_resources.mousestate[0], &g_resources.mousestate[1]);
  g_resources.mousestate[2] = 0;
  g_resources.mousestate[3] = 0;
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

void game_ticker(){
  //update game logic here
  //
  //handle keyboard input (updated in game_independent_ticker)
  game_handle_keyboard(g_resources.keystate);
  game_handle_mouse(g_resources.mousestate);
  
  return;
}

void game_independent_ticker(){
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
void game_handle_keyboard(Uint8 *keystate){
  //quit game
  if(keystate[SDLK_q])
    g_resources.gameDone = 1;
  
  //move forward
  if(keystate[SDLK_w]){
    g_resources.zMove += 5.0f;
    g_resources.camera.pos[2] += 5.0f;
  }
  
  //move backward
  if(keystate[SDLK_s]){
    g_resources.zMove -= 5.0f;
    g_resources.camera.pos[2] -= 5.0f;
  }
  
  //strafe left
  if(keystate[SDLK_a]){
    g_resources.xMove += 5.0f;
    g_resources.camera.pos[0] += 5.0f;
  }
  
  //strafe right
  if(keystate[SDLK_d]){
    g_resources.xMove -= 5.0f;
    g_resources.camera.pos[0] -= 5.0f;
  }
    
  return;
}

//Respond to mouse input
void game_handle_mouse(int *mousestate){
  /*
  //This does not work well and is buggy.
  //The whole "camera" system needs to be re-worked
  */
  float y;
	
	//DEBUG START
  printf("x: %i; y: %i; xRel: %i; yRel: %i\n", mousestate[0], mousestate[1], mousestate[2], mousestate[3]);
	//DEBUG END
	
  g_resources.camera.matrix[4] = 0;
  g_resources.camera.matrix[5] = 1;
  g_resources.camera.matrix[6] = 0;
  g_resources.camera.pitch += mousestate[3] * 0.5f;
  g_resources.camera.jaw += -mousestate[2] * 0.5f;

  //reset mouse relative position
  mousestate[2] = mousestate[3] = 0;
  
  //"convert" to degrees
  g_resources.camera.jaw = (float)((int)g_resources.camera.jaw % 360);
  g_resources.camera.pitch = (float)((int)g_resources.camera.pitch % 360);

  y = cos(g_resources.camera.pitch * M_PI / 180);
  g_resources.camera.matrix[8] = sin(g_resources.camera.jaw * M_PI / 180) * y;
  //g_resources.camera.matrix[9] = sin(g_resources.camera.pitch);
  g_resources.camera.matrix[10] = cos(g_resources.camera.jaw * M_PI / 180) * y;
  
  s_ComputeMatrix(g_resources.camera.matrix);
  
  //DEBUG START
  printf("jaw: %f; pitch: %f\n", g_resources.camera.jaw, g_resources.camera.pitch);
  //DEBUG END
  
  return;
}
