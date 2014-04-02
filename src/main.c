#include "microapi.h"

#define FALSE 0
#define TRUE 1

void handleKeys( unsigned char key, int x, int y ) {
	//Toggle quad
	if( key == 'q' ) {
		m_quitMainLoop();
	}
}

static double x_mouse=100;
static double y_mouse=100;

void keystate_function(const Uint8* keystate,int x, int y){
	x_mouse=x;
	y_mouse=y;

	// if(keystate[SDL_SCANCODE_A]){
	//	printf("caca\n");
	// }
}

static m_window* gWindow;


static SDL_Rect rects[200];
static double rects_x[200];
static double rects_y[200];

static int win_x;
static int win_y;
static double win_dx;
static double win_dy;

// static float t =0;
void render() {
	// t+=0.1;
	// m_setPosition(gWindow,100+100*cos(t), 100+100*sin(t));
	SDL_GetWindowPosition(gWindow->sdl_window, &win_x, &win_y);
	double ddx=.02*(x_mouse-150);
	double ddy=.02*(y_mouse-150);
	// if(fabs(ddx)<.1)ddx=0;
	// if(fabs(ddy)<.1)ddy=0;
	win_dx*=.95;
	win_dy*=.95;
	win_dx+=5*ddx+.25;
	win_dy+=5*ddy+.25;


	x_mouse-=.8*(win_dx-1);
	y_mouse-=.8*(win_dy-1);
	// if(win_dx> 20)win_dx= 20;
	// if(win_dy> 20)win_dy= 20;
	// if(win_dx<-20)win_dx=-20;
	// if(win_dy<-20)win_dy=-20;
	m_setPosition(gWindow,win_x+win_dx,win_y+win_dy);
	SDL_WarpMouseInWindow(gWindow->sdl_window, x_mouse, y_mouse);

	SDL_SetRenderDrawColor(gWindow->sdl_renderer, 180, 180, 180, 255);
	SDL_RenderClear(gWindow->sdl_renderer);

	SDL_Surface* surface;
	for(int i=0;i<100;i++){
		double a1=i;
		double a2=.05*(100-i);
		if(i%2)
			a2*=10;
		double b=a1+a2;
		rects_x[i] = (a1*rects[i].x + a2*(x_mouse-(i/2.)*8.))/b ;
		rects_y[i] = (a1*rects[i].y + a2*(y_mouse-(i/2.)*8.))/b ;
		rects[i].x = rects_x[i];
		rects[i].y = rects_y[i];
		SDL_SetRenderDrawColor(gWindow->sdl_renderer, 140, 140, 140, 128);
		SDL_RenderDrawRect(gWindow->sdl_renderer,&rects[i]);
		SDL_RenderPresent(gWindow->sdl_renderer);
	}
	SDL_Delay(10);
}

int main(int argc,char* args[]) {

	for(int i=0;i<200;i++){
		rects[i].x = 150-(i/2.)*4;
		rects[i].y = 150-(i/2.)*4;
		rects_x[i] = rects[i].x;
		rects_y[i] = rects[i].y;
		rects[i].w = i*8;
		rects[i].h = i*8;
	}

	// if(!m_init(3,1)) {return 1;}
	if(!m_init()) {return 1;}

	gWindow = m_newWindow(300,300,"Would you like to quit ?",FALSE);
	SDL_Delay(10);
	SDL_WarpMouseInWindow(gWindow->sdl_window, x_mouse, y_mouse);
	

	m_setTypingFunction(handleKeys);
	m_setKeyStateFunction(keystate_function);
	m_setMainLoopFunction(render);

	m_MainLoop();

	m_close();

	return 0;
}
