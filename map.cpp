#include "common.h"
#include "map.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>

TileMap::TileMap()
{
	tileWidth = tileHeight = TILE_SIZE;
	mapWidth = WINDOW_X;
	mapHeight = WINDOW_Y;
	tilesW = mapWidth / tileWidth;
	tilesH = mapHeight / tileHeight;

	int len = tilesW * tilesH * sizeof(Tile);
	tiles = (Tile *)malloc(len);
	memset(tiles, 0, len);
}
TileMap::~TileMap()
{
	destroy();
}
void TileMap::loadMap(const char *fileName)
{
	// free first on load-ahead scenario
	destroy();

	// open file in rb mode
	FILE *fin = fopen(fileName, "rb");
	TEST_NEZ(fin);

	// read w/h info
	TEST_EQ_NUM(fread(&tileWidth, sizeof(int), 1, fin), 1);
	TEST_EQ_NUM(fread(&tileHeight, sizeof(int), 1, fin), 1);
	TEST_EQ_NUM(fread(&mapWidth, sizeof(int), 1, fin), 1);
	TEST_EQ_NUM(fread(&mapHeight, sizeof(int), 1, fin), 1);
	tilesW = mapWidth / tileWidth;
	tilesH = mapHeight / tileHeight;

	// alloc && read
	int len = tilesW * tilesH * sizeof(Tile);
	tiles = (Tile *)malloc(len);
	memset(tiles, 0, len);
	TEST_EQ_NUM(fread(tiles, len , 1, fin), 1);

	// close file 
	fclose(fin);
}
void TileMap::saveMap(const char *fileName)
{
	FILE *fout = fopen(fileName, "wb");
	TEST_NEZ(fout);

	// write w/h info
	TEST_EQ_NUM(fwrite(&tileWidth, sizeof(int), 1, fout), 1);
	TEST_EQ_NUM(fwrite(&tileHeight, sizeof(int), 1, fout), 1);
	TEST_EQ_NUM(fwrite(&mapWidth, sizeof(int), 1, fout), 1);
	TEST_EQ_NUM(fwrite(&mapHeight, sizeof(int), 1, fout), 1);

	// write data
	int len = tilesW * tilesH * sizeof(Tile);
	TEST_EQ_NUM(fwrite(tiles, len , 1, fout), 1);

	// close file 
	fclose(fout);
}
void TileMap::draw(const Sprite **sprites, const Sprite *solid)
{
	int idx;
	for(int i = 0; i < tilesH; i++)
	{
		for(int j = 0; j < tilesW; j++)
		{
			idx = i * tilesW + j;
			if(EMPTY_TILE_GID != tiles[idx].gid) // skip empty tile
			{
				sprites[tiles[idx].gid]->draw(j * tileWidth, i * tileHeight);
			}
			if(NULL != solid && tiles[idx].solid)
				solid->draw(j * tileWidth, i * tileHeight);
		}
	}
}
