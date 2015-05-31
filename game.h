#ifndef __GAME_H__
#define __GAME_H__

#define TILE_SIZE 32
#define TILE_X 20
#define TILE_Y 15
#define WINDOW_X (TILE_X * TILE_SIZE)
#define WINDOW_Y (TILE_Y * TILE_SIZE)

#define FRAME_DURATION 15

extern SDL_Surface *screen;
extern Uint8 *keyStates;

#endif
