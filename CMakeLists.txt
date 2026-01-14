CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
set( CMAKE_EXPORT_COMPILE_COMMANDS on)
project(Pacman)

add_executable(Pacman src/main.c libs/glad/src/glad.c)
target_link_libraries( Pacman
  m
  X11
  GL
  Xrandr)
target_include_directories(Pacman
	PRIVATE "libs/rgfw/" 
	PRIVATE "libs/glad/include"
      )


