#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include <stdio.h>
#include <math.h>
#include "g_game.h"
#include "s_camera.h"
#include "sora.h"



#define TICK_TIME 33
//#define TICK_TIME 1000/15

//global game resources
extern g_resources_t g_resources;

static void init_gl_state(void){
  //SETUP START
  GLfloat fAspect;
  
  // Prevent a divide by zero
  int w = 800;
  int h = 600;
  
  // Set Viewport to window dimensions
  glViewport(0, 0, w, h);

  // Reset coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Establish clipping volume (left, right, bottom, top, near, far)
  h = (h < 1) ? 1 : h;
  fAspect = (GLfloat)w/(GLfloat)h;
  s_CameraPerspective (g_resources.fovy, fAspect, 0.1f, 400.0f);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //SETUP END
  
    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat	 lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
	
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

static void cleanup_gl_sdl(void){
  // Now we can delete the OpenGL texture and close down SDL
  //glDeleteTextures( 1, &texture );
  printf("Goodbye...\n");
  SDL_Quit();
}

static void render(float percentWithinTick){  
  float fZ,bZ;

  // Clear the window with current clearing color
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  fZ = 100.0f;
  bZ = -100.0f;
  
  // Save the matrix state and do the rotations
  glPushMatrix();
  s_CameraSet(&g_resources.camera);
  //glTranslatef(g_resources.xMove, g_resources.yMove, g_resources.zMove);
  //glRotatef(g_resources.xRot, 1.0f, 0.0f, 0.0f);
  //glRotatef(g_resources.yRot, 0.0f, 1.0f, 0.0f);

  // Set material color, Red
  glColor3f(1.0f, 0.0f, 0.0f);
  
  //set shading
  glShadeModel(GL_SMOOTH);
  
  // Front Face ///////////////////////////////////
  glBegin(GL_QUADS);
       // Pointing straight out Z
       glNormal3f(0.0f, 0.0f, 1.0f);	

       // Left Panel
       glVertex3f(-50.0f, 50.0f, fZ);
       glVertex3f(-50.0f, -50.0f, fZ);
       glVertex3f(-35.0f, -50.0f, fZ);
       glVertex3f(-35.0f,50.0f,fZ);

       // Right Panel
       glVertex3f(50.0f, 50.0f, fZ);
       glVertex3f(35.0f, 50.0f, fZ);
       glVertex3f(35.0f, -50.0f, fZ);
       glVertex3f(50.0f,-50.0f,fZ);

       // Top Panel
       glVertex3f(-35.0f, 50.0f, fZ);
       glVertex3f(-35.0f, 35.0f, fZ);
       glVertex3f(35.0f, 35.0f, fZ);
       glVertex3f(35.0f, 50.0f,fZ);

       // Bottom Panel
       glVertex3f(-35.0f, -35.0f, fZ);
       glVertex3f(-35.0f, -50.0f, fZ);
       glVertex3f(35.0f, -50.0f, fZ);
       glVertex3f(35.0f, -35.0f,fZ);

       // Top length section ////////////////////////////
       // Normal points up Y axis
       glNormal3f(0.0f, 1.0f, 0.0f);
       glVertex3f(-50.0f, 50.0f, fZ);
       glVertex3f(50.0f, 50.0f, fZ);
       glVertex3f(50.0f, 50.0f, bZ);
       glVertex3f(-50.0f,50.0f,bZ);

       // Bottom section
       glNormal3f(0.0f, -1.0f, 0.0f);
       glVertex3f(-50.0f, -50.0f, fZ);
       glVertex3f(-50.0f, -50.0f, bZ);
       glVertex3f(50.0f, -50.0f, bZ);
       glVertex3f(50.0f, -50.0f, fZ);

       // Left section
       glNormal3f(1.0f, 0.0f, 0.0f);
       glVertex3f(50.0f, 50.0f, fZ);
       glVertex3f(50.0f, -50.0f, fZ);
       glVertex3f(50.0f, -50.0f, bZ);
       glVertex3f(50.0f, 50.0f, bZ);

       // Right Section
       glNormal3f(-1.0f, 0.0f, 0.0f);
       glVertex3f(-50.0f, 50.0f, fZ);
       glVertex3f(-50.0f, 50.0f, bZ);
       glVertex3f(-50.0f, -50.0f, bZ);
       glVertex3f(-50.0f, -50.0f, fZ);
   glEnd();

   glFrontFace(GL_CW);		// clock-wise polygons face out

   glBegin(GL_QUADS);
       // Back section
       // Pointing straight out Z
       glNormal3f(0.0f, 0.0f, -1.0f);	

       // Left Panel
       glVertex3f(-50.0f, 50.0f, bZ);
       glVertex3f(-50.0f, -50.0f, bZ);
       glVertex3f(-35.0f, -50.0f, bZ);
       glVertex3f(-35.0f,50.0f,bZ);

       // Right Panel
       glVertex3f(50.0f, 50.0f, bZ);
       glVertex3f(35.0f, 50.0f, bZ);
       glVertex3f(35.0f, -50.0f, bZ);
       glVertex3f(50.0f,-50.0f,bZ);

       // Top Panel
       glVertex3f(-35.0f, 50.0f, bZ);
       glVertex3f(-35.0f, 35.0f, bZ);
       glVertex3f(35.0f, 35.0f, bZ);
       glVertex3f(35.0f, 50.0f,bZ);

       // Bottom Panel
       glVertex3f(-35.0f, -35.0f, bZ);
       glVertex3f(-35.0f, -50.0f, bZ);
       glVertex3f(35.0f, -50.0f, bZ);
       glVertex3f(35.0f, -35.0f,bZ);

       // Insides /////////////////////////////
   	glColor3f(0.75f, 0.75f, 0.75f);

       // Normal points up Y axis
       glNormal3f(0.0f, 1.0f, 0.0f);
       glVertex3f(-35.0f, 35.0f, fZ);
       glVertex3f(35.0f, 35.0f, fZ);
       glVertex3f(35.0f, 35.0f, bZ);
       glVertex3f(-35.0f,35.0f,bZ);

       // Bottom section
       glNormal3f(0.0f, 1.0f, 0.0f);
       glVertex3f(-35.0f, -35.0f, fZ);
       glVertex3f(-35.0f, -35.0f, bZ);
       glVertex3f(35.0f, -35.0f, bZ);
       glVertex3f(35.0f, -35.0f, fZ);

       // Left section
       glNormal3f(1.0f, 0.0f, 0.0f);
       glVertex3f(-35.0f, 35.0f, fZ);
       glVertex3f(-35.0f, 35.0f, bZ);
       glVertex3f(-35.0f, -35.0f, bZ);
       glVertex3f(-35.0f, -35.0f, fZ);

       // Right Section
       glNormal3f(-1.0f, 0.0f, 0.0f);
       glVertex3f(35.0f, 35.0f, fZ);
       glVertex3f(35.0f, -35.0f, fZ);
       glVertex3f(35.0f, -35.0f, bZ);
       glVertex3f(35.0f, 35.0f, bZ);
   glEnd();

  glFrontFace(GL_CCW);		// Counter clock-wise polygons face out

  // Restore the matrix state
  glPopMatrix();

  SDL_GL_SwapBuffers();
}


int main(int argc, char* argv[]){
  SDL_Surface *screen;

  // Slightly different SDL initialization
  if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }
  
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
  
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);  
  
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  //limit framerate
  SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
  
  screen = SDL_SetVideoMode( 800, 600, 16, SDL_OPENGL );
  if ( !screen ) {
	  printf("Unable to set video mode: %s\n", SDL_GetError());
		return 1;
	}
  
  //init
  //init game resources
  g_InitResources();
  
  SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
  SDL_WarpMouse(400, 300);
  SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
  
  //init OpenGL
  init_gl_state();

  //game loop
  Uint32 time0, time1, time2, frameTime;
  
  time0 = SDL_GetTicks();
  while (!g_resources.gameDone){
    time1 = SDL_GetTicks();
    frameTime = 0;
    while ((time1 - time0) > TICK_TIME){
      //update game logic
      g_Ticker();
      time0 += TICK_TIME;
      frameTime += TICK_TIME;
    }
    //gather player input & general housekeeping
    //g_IndependentTickRun(frameTime); //why frameTime?
    g_IndependentTickRun();
    
    // Account for numLoops overflow causing percent > 1.
    float percentWithinTick = fminf(1.f, (float)(time1 - time0)/TICK_TIME);
    //printf("percentWithinTick: %f\n", percentWithinTick);
    //GameDrawWithInterpolation(percentWithinTick);
    s_CameraCompute(&g_resources.camera, percentWithinTick);
    render(percentWithinTick);

    //for testing fps
    time2 = SDL_GetTicks();
    //printf("Speed %.3f frames/sec (%d ms)\n", 1000.0/(time2-time1), time2-time1);
  }
  
  cleanup_gl_sdl();
  return 0;
  
}