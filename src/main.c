#define RGFW_IMPLEMENTATION
#define RGFW_OPENGL
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 

#include "RGFW.h"
#include <glad/glad.h>
#include <stdio.h>
uint CompileShader(const char *FilePath, GLenum ShaderType) ;
float vertices[] = {
    0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f,
};

float texCoords [] ={ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

uint indices[] = {0, 1, 3, 1, 2, 3};

struct {
  unsigned int shaderProgram;
  unsigned int VAO;
  unsigned int EBO;
  unsigned int VBO;
} RenderVariables;

typedef struct Sprite{
  uint ImageID;
  char* Name;
};


void prepRender(){
  // Load Vertex Shader
  uint vert_shader = CompileShader("vertex.glsl", GL_VERTEX_SHADER);
  // Load Fragment Shader
  uint frag_shader = CompileShader("fragment.glsl", GL_FRAGMENT_SHADER);

  RenderVariables.shaderProgram = glCreateProgram();
  glAttachShader(RenderVariables.shaderProgram, vert_shader);
  glAttachShader(RenderVariables.shaderProgram, frag_shader);

  glLinkProgram(RenderVariables.shaderProgram);
  int success;
  glGetProgramiv(RenderVariables.shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    char log[512];
    glGetProgramInfoLog(RenderVariables.shaderProgram, 512, NULL, log);
    printf("LINK ERROR SHADERPROGRAM", log);
  }
  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  glGenVertexArrays(1, &RenderVariables.VAO);
  glGenBuffers(1, &RenderVariables.VBO);
  glGenBuffers(1, &RenderVariables.EBO);

  glBindVertexArray(RenderVariables.VAO);

  glBindBuffer(GL_ARRAY_BUFFER, RenderVariables.VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RenderVariables.EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

}


void keyfunc(RGFW_window *win, RGFW_key key, u8 keychar, RGFW_keymod keymod,
             RGFW_bool repeat, RGFW_bool pressed) {
  RGFW_UNUSED(repeat);
  if (key == RGFW_escape && pressed) {
    RGFW_window_setShouldClose(win, 1);
  }
}

RGFW_window *SetupWindow() {
  RGFW_glHints *hints = RGFW_getGlobalHints_OpenGL();
  hints->major = 4;
  hints->minor = 6;
  RGFW_setGlobalHints_OpenGL(hints);
  RGFW_window *win = RGFW_createWindow("PACMAN CLONE", 0, 0, 800, 600,
                                       RGFW_windowCenter | RGFW_windowNoResize |
                                           RGFW_windowOpenGL | RGFW_windowHide);
  RGFW_window_createContext_OpenGL(win, hints);
  RGFW_window_show(win);

  RGFW_setKeyCallback(keyfunc);
  RGFW_window_makeCurrentContext_OpenGL(win);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)RGFW_getProcAddress_OpenGL)) {
    printf("Failed to load GLAD!");
    return NULL;
  }
  return win;
}

long stat_GetSize(FILE *file) {
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET); // Reset to the beginning
  return size;
}
char *LoadFile(const char *Path) {
  FILE *fptr;
  fptr = fopen(Path, "r");
  if (!fptr) {
    printf("Failed to open file");
    return NULL;
  }
  long size = stat_GetSize(fptr);
  char *text = malloc(sizeof(char) * (size + 1));
  memset(text, 0x00, sizeof(char)*(size + 1));
  fread(text, size + 1, 1, fptr);
  fclose(fptr);
  return text;
}

uint CompileShader(const char *FilePath, GLenum ShaderType) {
  char *shdr_text = LoadFile(FilePath);
  printf("%s\n" , shdr_text);
  uint shader = glCreateShader(ShaderType);
  glShaderSource(shader, 1, (const char **)&shdr_text, NULL);
  glCompileShader(shader);
  int status;
  char info[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (!status) {
    glGetShaderInfoLog(shader, 512, NULL, info);
    const char *typename =
        ShaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
    printf("ERROR::SHADER::%s::COMPILATION %s\n", typename, info);
  }
  free(shdr_text);
  return shader;
}

void Setup() {
  prepRender();


  // Load images
  uint width, height;
  uint channels =4;
  unsigned char * data  = stbi_load("../sprites/mineger.png" ,&width, &height, &channels, 4);
  printf("Loaded PNG penger is %u * %u and has %u channels",  width, height , channels);

  free(data);
  // Setup world etc....
}

void clearScreen(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Render(RGFW_window * win){
    glUseProgram(RenderVariables.shaderProgram);
    glBindVertexArray(RenderVariables.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    RGFW_window_swapBuffers_OpenGL(win);
}



void Update(){
  // DO SOMETHING
}

int main(int argc, char **argv) {
  RGFW_window *win = SetupWindow();
  Setup();
  while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
    RGFW_event event;
    RGFW_pollEvents();
    Update();
    Render(win);

  }
  RGFW_window_close(win);

  return 0;
}
