CMAKE_MINIMUM_REQUIRED(VERSION 3.20)
set( CMAKE_EXPORT_COMPILE_COMMANDS on)
project(Pacman)

add_executable(Pacman src/main.c)
target_link_libraries( Pacman
		       X11
		       GL
		       Xrandr
		       
)
target_include_directories(Pacman
	PRIVATE "libs/rgfw/" 

)

