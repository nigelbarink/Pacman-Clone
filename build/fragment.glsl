#version 460 core
uniform sampler2D image;
in vec2 texCoord;
out vec4 fragcolor;

void main(){

  fragcolor = texture( image , texCoord) * vec4(1.0, 0.5, 0.2, 1.0);

}
