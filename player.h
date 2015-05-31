#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "gfx.h"
#include "map.h"

class Player
{
public:
	Player(const TileMap *m, char *fileName, Uint8 r, Uint8 g, Uint8 b);
	void think();				// handle input, collision detection..
	void draw();
private:
	bool collisionVer(int x, int y, int &coordX);
	bool collisionHor(int x, int y, int &coordY);
private:
	int screenX, screenY;					// left-top coord on the screen
	int spriteX, spriteY;					// for player animation
	int h, w;
	int velx, vely;
	bool faceRight;
	bool lockJump;

	const TileMap *map;
	Sprite sprite;
};

#endif
