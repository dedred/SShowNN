#include "SDL.h"
#include "Log.h"
#include "nnet.h"
#include "render.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


/* Declare window and renderer */
SDL_Window * window;
SDL_Renderer * renderer;
SDL_bool isPaused = SDL_TRUE;
SDL_bool isQuit = SDL_FALSE;



void Init() {
	LogInit();
	LogSetLevel(LOG_DEBUG);
	SDL_Init(SDL_INIT_EVERYTHING);	/* Initialize SDL */
	window = SDL_CreateWindow("SDL_Shownn", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	NetInit(WINDOW_WIDTH, WINDOW_HEIGHT);
	NetComputeInit();
	RenderInit(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
	LogDebug("Init complete");
}


/* Deinitialize everything */
void Done() {
	RenderDone();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	LogDebug("App done");
	LogEnd();
}



int main(int argc, char ** argv) {
	SDL_Event event;
	int x, y;
	Init();

	/* Main game loop */
	while (!isQuit && !SDL_QuitRequested()) {
		if (!isPaused)
			RenderPrep(OutputLayer[RenderDataIdx]);
		SDL_RenderClear(renderer);
		/* Place your simulation code and rendering code here */
		RenderDraw(renderer);
		SDL_RenderPresent(renderer);
		
		while(SDL_PollEvent(&event)){
			switch(event.type) {
				case SDL_QUIT:
					isQuit = 1;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (NetDataCount < MAX_DATA_IN) {
						SDL_GetMouseState(&x, &y);
						NetInput[NetDataCount][0] = (float)x / (float)WINDOW_WIDTH;
						NetInput[NetDataCount][1] = (float)y / (float)WINDOW_HEIGHT;
						LogDebug("SDL_MOUSEBUTTONDOWN (%d, %d)", x, y);
						if (event.button.button == SDL_BUTTON_LEFT) {
							NetOutput[NetDataCount++][0] = 1;
							LogDebug("Left click at %f,%f", NetInput[NetDataCount][0], NetInput[NetDataCount][1]);
						} else if (event.button.button == SDL_BUTTON_RIGHT) {
							NetOutput[NetDataCount++][0] = 0;
							LogDebug("Right click at %f,%f", NetInput[NetDataCount][0], NetInput[NetDataCount][1]);
						}
					}
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							LogDebug("Escape pressed");
							isQuit = 1;
							break;
						case SDLK_SPACE:
							if (isPaused) {
								isPaused = SDL_FALSE;
								LogDebug("Unpaused pressed");
							} else {
								isPaused = SDL_TRUE;
								LogDebug("Paused pressed");
							}
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
			SDL_Delay(1);
		}
	}

	/* Deinitialize everything */
	Done();
	return 0;
}
