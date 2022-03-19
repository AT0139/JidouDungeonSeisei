#pragma once

#include <vector>

#define TILE_WIDTH_MAX 30
#define TILE_HEIGHT_MAX 30
#define MAP_WIDTH_MAX  80		//�}�b�v���ő�l
#define MAP_HEIGHT_MAX  80		//�}�b�v�c�ő�l

class DungeonTile;

enum DUNGEON_MAPCHIP
{
	MAPCHIP_NONE,
	MAPCHIP_WALL,
	MAPCHIP_DEBUG,
	MAPCHIP_DEBUG_ROAD,

	MAPCHIP_MAX,
};

class DungeonAutoGeneration
{
public:
	DungeonAutoGeneration();

	void Init();
	void Generate();
	void Draw();

private:
	void FillAllWall();

	int m_mapData[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];	//2�����z��}�b�v�f�[�^
};