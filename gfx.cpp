////////////////////////////////////////////////////////////////////////////////
//               Copyright(c) 2013
// Filename        :    gfx.cpp
// Projectname     :    small game
// Author          :    Jujj
// Email           :    
// Date            :    周日 十二月  8 16:12:03 2013 (+0800)
// Version         :    v 1.0
// Description     :    
////////////////////////////////////////////////////////////////////////////////
#include "common.h"
#include "gfx.h"
#include "game.h"
#include <stdarg.h>

#define GFX_BPP 0
#define GFX_FLAGS SDL_SWSURFACE

bool gfx_init(int w, int h, bool fullScreen)
{
	DEBUG_PRINT("GFX init...\n");
	TEST_EQZ(SDL_Init(SDL_INIT_VIDEO));
	atexit(SDL_Quit);
	
	Uint32 flags = GFX_FLAGS;
	if(fullScreen) flags |= SDL_FULLSCREEN;
	TEST_NEZ(screen = SDL_SetVideoMode(w, h, GFX_BPP, flags));

	return true;
}
void gfx_setResolution(int w, int h, bool fullScreen)
{
	Uint32 flags = GFX_FLAGS;
	if(fullScreen) flags |= SDL_FULLSCREEN;
	TEST_NEZ(screen = SDL_SetVideoMode(w, h, GFX_BPP, flags));
}

// Sprite
Sprite::Sprite()
{
	picture = NULL;
}
Sprite::~Sprite()
{
	if(picture)
	{
		SDL_FreeSurface(picture);
		picture = NULL;
	}
}
bool Sprite::init(const char *fileName, bool full, Uint8 r, Uint8 g, Uint8 b)
{
	// previous inited, free first
	if(picture)
	{
		SDL_FreeSurface(picture);
		picture = NULL;
	}

	// load bmp & set color key
	TEST_NEZ(picture = SDL_LoadBMP(fileName));
	TEST_EQZ(SDL_SetColorKey(picture, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(picture->format, r, g, b)));

	// convert to display format
	SDL_Surface *temp = NULL;
	TEST_NEZ(temp = SDL_DisplayFormat(picture));
	SDL_FreeSurface(picture);
	picture = temp;

	if(full)// draw full image
	{
		screenRect.w = spriteRect.w = picture->w;
		screenRect.h = spriteRect.h = picture->h;
	}else// draw as tile size
	{
		screenRect.w = spriteRect.w = TILE_SIZE;
		screenRect.h = spriteRect.h = TILE_SIZE;
	}

	return true;
}

bool Sprite::init(const char *fileName, bool full)
{
	// previous inited, free first
	if(picture)
	{
		SDL_FreeSurface(picture);
		picture = NULL;
	}

	// load bmp
	TEST_NEZ(picture = SDL_LoadBMP(fileName));

	// convert to display format
	SDL_Surface *temp = NULL;
	TEST_NEZ(temp = SDL_DisplayFormat(picture));
	SDL_FreeSurface(picture);
	picture = temp;

	if(full)// draw full image
	{
		screenRect.w = spriteRect.w = picture->w;
		screenRect.h = spriteRect.h = picture->h;
	}else// draw as tile size
	{
		screenRect.w = spriteRect.w = TILE_SIZE;
		screenRect.h = spriteRect.h = TILE_SIZE;
	}
	return true;
}

bool Sprite::draw(int screenX, int screenY, int spriteX, int spriteY) const
{
	screenRect.x = screenX;
	screenRect.y = screenY;
	spriteRect.x = spriteX;
	spriteRect.y = spriteY;

	// blit onto the screen
	TEST_EQZ(SDL_BlitSurface(picture, &spriteRect, screen, &screenRect));

	return true;
}
