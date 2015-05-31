#ifndef __MAP_H__
#define __MAP_H__
#include "gfx.h"

#define EMPTY_TILE_GID 0
#define MAPFILE_NAME "level-1.map"

class Tile
{
public:
	int gid;					// 0 none, otherwise sprite id
	int solid;					// 1 solid, 0 not
};

class TileMap
{
public:
	TileMap();
	~TileMap();
	void loadMap(const char *fileName);
	void saveMap(const char *fileName);
	void draw(const Sprite **sprites, const Sprite *solid);
	inline Tile * operator[](int y) const
	{
		return tiles + y * tilesW;
	}

	int tileWidth, tileHeight;
	int mapWidth, mapHeight;
	int tilesW, tilesH;
	Tile *tiles;				// y(height) major array

private:
	void destroy()
	{
		if(NULL != tiles) free(tiles);
	}
};

#endif
