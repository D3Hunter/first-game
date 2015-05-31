#include "player.h"
#include "game.h"

#define VEL_MOVING 3
#define VEL_JUMP 12
#define GRAVITATION 1
#define PLAYER_SPRITE_WIDTH 160
#define PLAYER_SPRITE_HEIGHT 64
#define PLAYER_Y_OFFSET 2

//////////////////////////////////////////////////
// Player sprite image should be 128x64
// 128x(1-32) facing right
// 128x(33-64) facing left
// each side with 4 images
//////////////////////////////////////////////////
Player::Player(const TileMap *m, char *fileName, Uint8 r, Uint8 g, Uint8 b)
	:sprite()
{
	screenX = screenY = 3 * TILE_SIZE;		// init position
	spriteX = spriteY = 0;					// 
	w = TILE_SIZE;
	h = TILE_SIZE;
	velx = vely = 0;
	faceRight = true;
	lockJump = false;
	map = m;

	sprite.init(fileName, false, r, g, b);
}
void Player::think()
{
	static int animFrame = 0, step = TILE_SIZE;
	// stay still
	velx = 0;

	// Handle keys: a, d, space...
	if(keyStates[SDLK_a])
	{
		velx = -VEL_MOVING;
		faceRight = false;
		spriteY = TILE_SIZE;
	}
	if(keyStates[SDLK_d])
	{
		velx = VEL_MOVING;
		faceRight = true;
		spriteY = 0;
	}
	if(keyStates[SDLK_SPACE] && !lockJump)
	{
		vely = -VEL_JUMP;
		lockJump = true;
	}

	// update player anim para (ground only)
	if(0 != velx && !lockJump)
	{
#define ANIM_INTERVAL 5
		if(animFrame == ANIM_INTERVAL)// change every other frame
		{
			spriteX += step; // to next anim frame
			if(spriteX == PLAYER_SPRITE_WIDTH)
			{
				spriteX -= 2 * TILE_SIZE;
				step = -TILE_SIZE;
			}else if(0 == spriteX)
			{
				spriteX = TILE_SIZE;
				step = TILE_SIZE;
			}
			animFrame = 0;
		}
		animFrame++;
	}else
	{
		spriteX = 0;			// to init state
		animFrame = 0;
		step = TILE_SIZE;
	}

	int coord;
	// handle y axis
	if(vely < 0)				// up
	{
		if(collisionHor(screenX, screenY + vely, coord))
		{
			screenY = (coord+1) * TILE_SIZE;
			vely = 0;
		}
		else
		{
			screenY += vely;
			vely += GRAVITATION;
		}
	}else						// down/on ground
	{
		if(collisionHor(screenX, screenY + vely + h, coord))
		{
			screenY = coord * TILE_SIZE - h;
			vely = GRAVITATION;			// we are on the ground

			lockJump = false;
		}else							// in the air
		{
			screenY += vely;
			vely += GRAVITATION;

			// vely cannot be greater than TILE_SIZE
			if(vely > TILE_SIZE)
				vely = TILE_SIZE;
			lockJump = true;// cannot jump in the air
		}
	}

	// handle x axis
	if(velx > 0)				// moving right
	{
		// Detecting collision
		if(collisionVer(screenX + velx + w, screenY, coord)) // right side of the player
		{
			screenX = coord * TILE_SIZE - w;
		}
		else
			screenX += velx;
	}else if(velx < 0)			// moving left
	{
		if(collisionVer(screenX + velx, screenY, coord)) // left side of the player
		{
			screenX = (coord + 1) * TILE_SIZE;
		}else
			screenX += velx;
	}
}
void Player::draw()
{
	sprite.draw(screenX, screenY + PLAYER_Y_OFFSET, spriteX, spriteY);
}

// checking collision between line (screenX, y...y+h) and tiles
bool Player::collisionVer(int x, int y, int &coordX)
{
	int cx = coordX = x / TILE_SIZE;
	int startYPixel = y - y % TILE_SIZE;
	int cy = startYPixel / TILE_SIZE;
	int endYPixel = y + h;

	while(startYPixel < endYPixel)
	{
		if((*map)[cy][cx].solid == 1)
			return true;
		cy++;
		startYPixel += TILE_SIZE;
	}
	return false;
}
bool Player::collisionHor(int x, int y, int &coordY)
{
	int cy = coordY = y / TILE_SIZE;
	int startXPixel = x - x % TILE_SIZE;
	int cx = startXPixel / TILE_SIZE;
	int endXPixel = x + w;

	while(startXPixel < endXPixel)
	{
		if((*map)[cy][cx].solid == 1)
			return true;
		cx++;
		startXPixel += TILE_SIZE;
	}
	return false;
}
