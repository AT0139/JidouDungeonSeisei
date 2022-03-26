#pragma once

#include <vector>

#define TILE_WIDTH_MAX 30		//�^�C������
#define TILE_HEIGHT_MAX 30		//�^�C���c��
#define TILE_HORIZONTAL_NUM 2	//�^�C������
#define TILE_VERTICAL_NUM 2		//�^�C���c��

#define MAP_WIDTH_MAX  (TILE_WIDTH_MAX * TILE_HORIZONTAL_NUM)	//�}�b�v���ő�l
#define MAP_HEIGHT_MAX  (TILE_HEIGHT_MAX * TILE_VERTICAL_NUM)	//�}�b�v�c�ő�l

class DungeonTile;


enum ROAD_DIRECTION
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	DIR_MAX
};

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
	void ConnectTiles();
	void CreateRoadTileHorizontal(int x1, int y1, int x2, int y2);
	void CreateRoadTileVertical(int x1, int y1, int x2, int y2);

	int m_mapData[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];	//2�����z��}�b�v�f�[�^

	std::vector<DungeonTile*> m_tileList;			//�^�C���f�[�^�z��
};