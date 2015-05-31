#include "common.h"
#include "gfx.h"
#include "game.h"
#include "map.h"
#include "player.h"

SDL_Surface *screen = NULL;
Uint8 *keyStates = NULL;

int main(int argc, char **argv)
{
	bool done = false;
	SDL_Event event;

	// init graphics
	gfx_init(WINDOW_X, WINDOW_Y, false);
	// get key state array
	keyStates = SDL_GetKeyState(NULL);

#define SPRITE_CNT 1
	Sprite *sprites[SPRITE_CNT+1];
	sprites[0] = NULL;
	sprites[1] = new Sprite();
	sprites[1]->init("1.bmp", false, 255, 255, 255);

	Sprite backGround;
	backGround.init("background.bmp", true);

	// load from file
	TileMap map;
	map.loadMap(MAPFILE_NAME);

	Player player(&map, "player.bmp", 0, 0, 0);

	Uint32 frameStart;
	while(!done)
	{
		frameStart = SDL_GetTicks();
		// event processing
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				done = true;
			default:
				break;
			}
		}
		// player think
		player.think();

		// draw
		backGround.draw(0, 0);
		map.draw((const Sprite **)sprites, NULL);
		player.draw();

		// flip buffer
		SDL_Flip(screen);

		// Key to have smooth moving and jump animation
		while(SDL_GetTicks() - frameStart < FRAME_DURATION);
	}

	return 0;
}
