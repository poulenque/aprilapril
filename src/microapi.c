#include "microapi.h"

#include <stdio.h>

#define FALSE 0
#define TRUE 1

//TODO
//
// implement multiple window
// -> should glewInit be called once per new window ?
// event handling
// window resizing
// m_close should delete glPrograms


//list all windows
static m_window** windows;
static int window_count=0;
static int window_max=0;

static void(*main_loop_function)(void);
static void(*typing_function)(unsigned char key, int x, int y);
static void(*keystate_function)(const Uint8* keystate,int x,int y);

void m_setWindowTitle(m_window* window,const char* title){
	SDL_SetWindowTitle(window->sdl_window,title);
}
void m_setPosition(m_window* window,int x, int y){
	SDL_SetWindowPosition(window->sdl_window, x, y);
}
void m_setSize(m_window* window,int w, int h){

}

void m_setMainLoopFunction(void(*f)(void)){
	main_loop_function=f;
}
void m_setTypingFunction(void(*f)(unsigned char key, int x, int y)){
	typing_function=f;
}
void m_setKeyStateFunction(void(*f)(const Uint8* keystate,int x,int y)){
	keystate_function = f;
}

static bool quit = FALSE;

void m_quitMainLoop(){
	quit=TRUE;
}

void m_MainLoop(){
	quit = FALSE;
	SDL_Event e;

	SDL_StartTextInput();
	while( !quit ) {
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				quit = TRUE;
			} else if( e.type == SDL_TEXTINPUT ) {
				// if a function had been choosen
				if(typing_function){
					int x = 0, y = 0;
					SDL_GetMouseState( &x, &y );
					typing_function(e.text.text[0], x, y);
				}
			}
		}
		if(keystate_function){
			int x = 0, y = 0;
			SDL_GetMouseState( &x, &y );
			keystate_function(SDL_GetKeyboardState(NULL),x,y);
		}
		main_loop_function();
		// ==========
		// == TODO == this part will change with multiple window
		// ==========
		// SDL_GL_SwapWindow( windows[window_count-1]->sdl_window );
		// ==========
		// ==========
	}
	SDL_StopTextInput();

}


bool m_init(){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return FALSE;
	}
	return TRUE;	
}

void m_close(){
	//delete all windows
	for(int i=0;i<window_count;i++){
		SDL_DestroyWindow( windows[i]->sdl_window );
		windows[i]->sdl_window = NULL;
	}
	SDL_Quit();
}


m_window* m_newWindow(int width,int height,const char* title,bool resizable){

	if(window_count){
		printf("=======================================================\n");
		printf("== ERROR : for now only one window can be created... ==\n");
		printf("==         this is in the TODO list :¬P              ==\n");
		printf("==         have to figurate how to open more than    ==\n");
		printf("==         one opengl context ._.                    ==\n");
		printf("=======================================================\n");
		return NULL;
	}

	m_window* window = malloc(sizeof(m_window));
	if(title==NULL){title="";}
	// Uint32 flags= SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS;
	Uint32 flags= SDL_WINDOW_SHOWN;
	if(resizable){
		flags|=SDL_WINDOW_RESIZABLE;
	}
	window->sdl_window = SDL_CreateWindow( title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height,
		flags);
	if( window->sdl_window == NULL ) {
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return FALSE;
	}
	window->sdl_renderer = SDL_CreateRenderer( window->sdl_window, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor(window->sdl_renderer, 180, 180, 180, 255);
	SDL_RenderClear(window->sdl_renderer);
	SDL_RenderPresent(window->sdl_renderer);

	//================================
	window_count++;
	if(window_count>window_max){
		window_max=2*(window_max+1);
		windows=realloc(windows,window_max*sizeof(m_window*));
	}
	windows[window_count-1]=window;
	//================================
	return window;
}

