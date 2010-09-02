#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include <stdio.h>

void DisplayState(SDL_KeyboardEvent *key)
{
	//What type of keypress was this?
	if (key->type == SDL_KEYUP)
		printf("RELEASED: ");
	else
		printf("PRESSED: ");
	
}

void DisplayModifiers(SDL_KeyboardEvent *key)
{
	//What modifiers were held down when the keyboard event took place?
	SDLMod modifier = key->keysym.mod;
	if( modifier & KMOD_NUM ) printf( "NUMLOCK " );		//Numlock modifier
	if( modifier & KMOD_CAPS ) printf( "CAPSLOCK " );	//Capslock modifier
	if( modifier & KMOD_MODE ) printf( "MODE " );		//Special "Mode" modifier
	if( modifier & KMOD_LCTRL ) printf( "LCTRL " );		//Left control key modifier
	if( modifier & KMOD_RCTRL ) printf( "RCTRL " );		//Right control key modifier
	if( modifier & KMOD_LSHIFT ) printf( "LSHIFT " );	//Left shift key modifier
	if( modifier & KMOD_RSHIFT ) printf( "RSHIFT " );	//Right shift key modifier
	if( modifier & KMOD_LALT ) printf( "LALT " );		//Left alt key modifier
	if( modifier & KMOD_RALT ) printf( "RALT " );		//Right alt key modifier
	if( modifier & KMOD_LMETA ) printf( "LMETA " );		//Left meta (Apple 'Command') key modifier
	if( modifier & KMOD_RMETA ) printf( "RMETA " );		//Right meta (Apple 'Command') key modifier
	
	//The following are included for completeness, but would give duplicate output if used with the code above
	//if( modifier & KMOD_CTRL ) printf( "CTRL " );		//Left or right control key modifier
	//if( modifier & KMOD_SHIFT ) printf( "SHIFT " );	//Left or right shift key modifier
	//if( modifier & KMOD_ALT ) printf( "ALT " );		//Left or right alt key modifier
	//if( modifier & KMOD_META ) printf( "META " );		//Left or right meta (Apple 'Command') key modifier
}

void DisplayKey(SDL_KeyboardEvent *key)
{
	//Print out text corresponding to the key in question
	//printf( "%s\n", SDL_GetKeyName(key->keysym.sym));
	printf( "%s\n", SDL_GetKeyName(key->keysym.sym));
}

void DisplayMatrixes(){
  static GLdouble modelmatrix[16];
	static GLdouble projmatrix[16];
	static GLint viewport[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, modelmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
	glGetIntegerv(GL_VIEWPORT, viewport);
	
  int i;
  printf("modelmatrix");
  for(i=0; i<16; i++) printf(":%d", modelmatrix[i]);
  printf("\nprojmatrix");
  for(i=0; i<16; i++) printf(":%d", projmatrix[i]);
  printf("\nviewport");
  for(i=0; i<4; i++) printf(":%i", viewport[i]);
  printf("\n");
}