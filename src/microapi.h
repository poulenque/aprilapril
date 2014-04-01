#ifndef MICROAPI__H
#define MICROAPI__H

#include <SDL2/SDL.h>
// #include <GLES3/gl3.h>
// #include <GL/glew.h>
// #include <GL/gl.h>
// #include <GL/glu.h>
// #include <SDL2/SDL_opengl.h>

typedef int bool;

typedef struct m_window m_window;
struct m_window{
	SDL_Window* sdl_window;
	SDL_Renderer* sdl_renderer;
};

typedef double m_vec1[1];
typedef double m_vec2[2];
typedef double m_vec3[3];
typedef double m_vec4[4];
typedef double m_mat1[1];
typedef double m_mat2[4];
typedef double m_mat3[9];
typedef double m_mat4[16];

//m_init(3,2) will create a 3.2 opengl context
bool m_init();
void m_close();

m_window* m_newWindow(int width,int height,const char* title,bool resizable);
void m_setWindowTitle(m_window* window,const char* title);

// ========
// ==TODO==
// ========
void m_setPosition(m_window* window,int x, int y);
void m_setSize(m_window* window,int w, int h);
// ========
// ========

void m_setTypingFunction(void(*f)(unsigned char key, int x, int y));
void m_setKeyStateFunction(void(*f)(const Uint8* keystate,int x, int y));
void m_setMainLoopFunction(void(*f)(void));
void m_MainLoop();

void m_quitMainLoop();


#endif
