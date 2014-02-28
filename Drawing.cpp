#include "common.h"
#include "Constants.h"

#include "Ray.h"
#include "World.h"

#include "Drawing.h"

Drawing::Drawing() {
	Window = NULL;
	ScreenSurface = NULL;
	Quit = false;
	restart = false;
	ScreenWidth = 1280;
	ScreenHeight = 800;
}

Drawing::~Drawing() {
	close();
}

void Drawing::setHeight(const int &h) {
	ScreenHeight = h;
}

void Drawing::setWidth(const int &w) {
	ScreenWidth = w;
}

SDL_Window * Drawing::getWindowPointer() {
	return Window;
}

bool Drawing::init() {

	//Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        //printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		infoPrint("SDL could not initialize! SDL_Error:"+string(SDL_GetError())+"!");
        success = false;
    }
    else
    {
        //Create window
		//cout << "Window Created" << endl;
		infoPrint("Window Created!");
		Window = SDL_CreateWindow( "RayTracing System", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN );
        if( Window == NULL )
        {
            //printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			infoPrint("Window could not be created! SDL_Error:"+string(SDL_GetError())+"!");
            success = false;
        }
        else
        {
            //Get window surface
            ScreenSurface = SDL_GetWindowSurface( Window );
        }
    }

    return success;

}

int Drawing::rayTracingThread(void * data) {
	//While the program is not over
	Drawing * Draw= (Drawing *) data;
	for( int i = 0; i < Draw->ScreenHeight; i++) {
		for( int j = 0; j < Draw->ScreenWidth; j++) {
					int x = 400, y = 300, r = 50;
					Uint8 * pixel = (Uint8*)Draw->ScreenSurface->pixels;
					pixel += (i * Draw->ScreenSurface->pitch) + (j * sizeof(Uint32));
					if( (x-j)*(x-j) + (y-i)*(y-i) < r * r) {
						*((Uint32*)pixel) = (0xFF << 24) | (0x00 << 16) | (0xFF << 8) | (0x00); // ARGB
					}
					else {
						*((Uint32*)pixel) = (0xFF << 24) | (0xFF << 16) | (0x00 << 8) | (0x00); // ARGB
					}

					SDL_Delay( 1 );
					//Every time the pixels updated, Update the surface
					//SDL_UpdateWindowSurface( gWindow );
				}
			}
	return 0;
}

// for world ray tracing thread
int Drawing::realRayTracingThread(void * data) {

	World * ptr = (World *)data;
	//ptr->simpleRenderScene();
	ptr->camera_ptr->renderScene(*ptr);
	return 0;
}

void Drawing::nonBlockingRayTracing() {
	SDL_Thread * thread = SDL_CreateThread( Drawing::rayTracingThread, "ray tracing", this);
}

void Drawing::nonBlockRayTracingWorld(World * world_ptr) {
	SDL_Thread * thread = SDL_CreateThread( Drawing::realRayTracingThread, "ray tracing", world_ptr);
}

int Drawing::showWindowThread(void * data) {
	//The Thread for update surface of the window
	//SDL_Thread* thread = SDL_CreateThread( drawingThread, "Show Window", (void *)Window);//(void *) data);
	Drawing * Draw= (Drawing *) data;
	while(Draw->Quit == false) {
		SDL_UpdateWindowSurface( Draw->getWindowPointer());//Window );
		//SDL_Delay(1000);
	}
	return 0;
}

void Drawing::nonBlockingShowWindow() {
	SDL_Thread * thread = SDL_CreateThread( Drawing::showWindowThread, "show window", this);
}

void Drawing::eventHandler() {
	//Event handler
	SDL_Event e;

	//While application is running
	while( Quit == false)
	{
		//Handle events on queue

		//update surface
		if(refresh) {
			SDL_UpdateWindowSurface( getWindowPointer());//Window );

			// similarly event driven
			refresh = false;
		}
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				Quit = true;
				//break;
			}
			else if( e.type == SDL_KEYDOWN) {
				// for test
				if(e.key.keysym.sym == SDLK_a) {
					cout << "A" << endl;
					for(int i = 0; i < ScreenHeight/10; i++) {
						for(int j = 0; j < ScreenWidth/10; j++) {
							//cout << getPixel(i*10, j*10) << ' ';
							setPixel(i*10, j*10, (0xff << 16));
						}
					}
					setRefresh(true);
					restart = true;
				}
			}
		}
	}
}

// as left down corner should be the smallest coordinates
// so the coors should be converted
void Drawing::setPixel(const int &t_y, const int &t_x, const Uint32 &color) {
	int x, y;
	x = t_x + 1;//ScreenWidth - t_x - 1;
	y = ScreenHeight - t_y - 1;

	Uint8 * pixel = (Uint8*)ScreenSurface->pixels;
	pixel += (y * ScreenSurface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;

	//require window update
	// too frequently
	//refresh = true;
}

Uint32 Drawing::getPixel(const int &t_y, const int &t_x) {
	int x, y;
	x = t_x + 1;//ScreenWidth - t_x - 1;
	y = ScreenHeight - t_y - 1;

	Uint8 * pixel = (Uint8*)ScreenSurface->pixels;
	pixel += (y * ScreenSurface->pitch) + (x * sizeof(Uint32));
	//cout << *((Uint32*)pixel) << endl;
	return *((Uint32*)pixel);
}

void Drawing::setRefresh(const bool &ref_) {
	refresh = ref_;
}

void Drawing::close() {

	//Deallocate surface
    //SDL_FreeSurface( gHelloWorld );
    //gHelloWorld = NULL;

    //Destroy window
    SDL_DestroyWindow( Window );
    Window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
