#ifndef __GFX_H__
#define __GFX_H__

#include "SDL.h"

bool gfx_init(int w, int h, bool fullScreen);
void gfx_setResolution(int w, int h, bool fullScreen);

class Sprite
{
public:
	Sprite();
	~Sprite();

	bool init(const char *fileName, bool full, Uint8 r, Uint8 g, Uint8 b); // color keyed
	bool init(const char *fileName, bool full);							// non-color keyed
	bool draw(int screenX, int screenY, int spriteX = 0, int spriteY = 0) const;
	int getWidth(){return picture->w;};
	int getHeight(){return picture->h;};
	SDL_Surface *getSurface(){return picture;};

	SDL_Surface *picture;
	mutable SDL_Rect screenRect, spriteRect;
};

#endif
