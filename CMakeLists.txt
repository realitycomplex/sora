cmake_minimum_required (VERSION 2.6)
project (sora)

set (
   SOURCES
   s_main.c
   s_debug.c
   s_camera.c
   g_game.c
   common/math3d.c
)

Find_Package ( SDL REQUIRED )
Find_Package ( OpenGL REQUIRED )

# Workaround for the non-working REQUIRED flag
if ( NOT SDL_FOUND )
   message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

link_libraries (
   ${SDL_LIBRARY}
   ${OPENGL_LIBRARY}
   SDLmain
)

add_executable (
   sora
   ${SOURCES}
)
