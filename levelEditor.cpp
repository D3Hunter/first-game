#include "common.h"
#include "gfx.h"
#include "game.h"
#include "map.h"

SDL_Surface *screen = NULL;

int main(int argc, char **argv)
{
	bool done = false;
	SDL_Event event;

	gfx_init(WINDOW_X, WINDOW_Y, false);

#define SPRITE_CNT 1
	Sprite *sprites[SPRITE_CNT+1];
	sprites[0] = NULL;
	sprites[1] = new Sprite();
	sprites[1]->init("1.bmp", false, 255, 255, 255);

	Sprite backGround, solid;
	backGround.init("background.bmp", true);
	solid.init("solid.bmp", false, 255, 255, 255);

	TileMap map;
	// load from file
	map.loadMap(MAPFILE_NAME);
	int x, y, currGid = 1, currSolid;
	while(!done)
	{
		// process event
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				map.saveMap(MAPFILE_NAME);
				done = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x / map.tileWidth;
				y = event.button.y / map.tileHeight;
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					map[y][x].gid = currGid;
				}else if(event.button.button == SDL_BUTTON_MIDDLE)
				{
					// to next sprite
					currGid = (currGid+1) % (SPRITE_CNT+1);

					// change current sprite
					map[y][x].gid = currGid;
				}else			// right button
				{
					currSolid = map[y][x].solid = 1 - map[y][x].solid;
				}
				break;
			case SDL_MOUSEMOTION:
				x = event.motion.x / map.tileWidth;
				y = event.motion.y / map.tileHeight;
				if(event.motion.state == SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					map[y][x].gid = currGid;
				}else if(event.motion.state == SDL_BUTTON(SDL_BUTTON_RIGHT))
				{
					map[y][x].solid = currSolid;
				}
				break;
			default:
				break;
			}
		}
		backGround.draw(0, 0);
		map.draw((const Sprite **)sprites, &solid);

		// flip buffer
		SDL_Flip(screen);
	}

	return 0;
}
