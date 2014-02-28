#ifndef DRAWING_H
#define DRAWING_H

#include <SDL.h>

#undef main // prohibiting the additional behaviors in the header files

class World;
class Drawing {
public:
	//Constructor
	Drawing();

	//Destructor
	~Drawing();

	void setHeight(const int &);

	void setWidth(const int &);

	//Starts up SDL and creates window
	bool init();

	//Thread function of Ray Tracing
	static int rayTracingThread(void * data);

	//Thread function of "REAL" Ray Tracing
	static int realRayTracingThread(void * data);

	//Function of Maintaing the Ray Tracing Thread
	void nonBlockingRayTracing();

	//Function of Maintaing the "REAL" Ray Tracing Thread 
	void nonBlockRayTracingWorld(World *);

	//Thread function to Show Window 
	static int showWindowThread(void * data);

	//Function used to run another thread which is used to show window
	void nonBlockingShowWindow();

	//Function to handle events, including mouse and keyboard
	//Should be blocking
	void eventHandler();

	//Loads media
	//bool loadMedia();

	// set (x, y) to color(ARGB)
	void setPixel(const int &, const int &, const Uint32 &);
	Uint32 getPixel(const int &, const int &);

	// set refresh 
	void setRefresh(const bool &);

	//Frees media and shuts down SDL
	void close();

	// Getting the window pointer
	SDL_Window * getWindowPointer();

protected:
	//The Window Size
	int ScreenWidth, ScreenHeight;

	//The window we'll be rendering to
	SDL_Window* Window;

	//The surface contained by the window
	SDL_Surface* ScreenSurface;

	//The image we will load and show on the screen
	//SDL_Surface* gHelloWorld = NULL;

	//Global Quit Symbol
	bool Quit;

	//update screen or not
	bool refresh;
	bool restart;
};

#endif
