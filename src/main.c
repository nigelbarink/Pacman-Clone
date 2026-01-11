#define RGFW_IMPLEMENTATION
#define RGFW_OPENGL
#include "RGFW.h"
#include <stdio.h>

void keyfunc (RGFW_window* win, RGFW_key key, u8 keychar, RGFW_keymod keymod, RGFW_bool repeat, RGFW_bool pressed){
  RGFW_UNUSED(repeat);
  if (key == RGFW_escape && pressed){
    RGFW_window_setShouldClose(win, 1);
  }
}

int main (int argc, char **argv){
	RGFW_window* win = RGFW_createWindow("PACMAN CLONE", 0,0, 800, 600, RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowOpenGL);
	RGFW_setKeyCallback(keyfunc);

	while ( RGFW_window_shouldClose(win) == RGFW_FALSE){
	  RGFW_event event;
	  RGFW_pollEvents();



	  


	  
	}

	

	RGFW_window_close(win);
	
	return 0;
}

