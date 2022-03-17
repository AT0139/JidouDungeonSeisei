#pragma once

#include <vector>

#define MAP_WIDTH_MAX  50		//�}�b�v���ő�l
#define MAP_HEIGHT_MAX  50		//�}�b�v�c�ő�l

class DungeonRect;
class DungeonRoom;

enum DUNGEON_TILE
{
	TILE_NONE,
	TILE_WALL,
	TILE_DEBUG,
	TILE_DEBUG_ROAD,


	TILE_MAX,
};

class DungeonAutoGeneration
{
public:
	DungeonAutoGeneration();

	void Init();
	void Generate();
	void Draw();

private:
	void CreateRoad();
	void CreateRoadWorking(DungeonRoom* room1, DungeonRoom* room2);
	void FillAllWall();

	int m_mapData[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];	//2�����z��}�b�v�f�[�^

	std::vector<DungeonRect*> m_childList;		//���������q���X�g
	std::vector<DungeonRoom> m_roomList;		//�������X�g
};