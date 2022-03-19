#pragma once

#include "DungeonAutoGeneration.h"
#include "DungeonRoom.h"
class DungeonRect;
class DungeonRoom;

/// <summary>
/// �_���W�������̃^�C�������֐�
/// �}�b�v�̓^�C������ׂč��
/// �^�C���̒��ɂ͋��A����������
/// </summary>
class DungeonTile
{
public:
	DungeonTile();
	void Generate();
	void MapWriting(int mapData[][MAP_WIDTH_MAX],int xPos,int yPos);

private:
	void CreateRoad();
	void CreateRoadWorking(DungeonRoom* room1, DungeonRoom* room2, bool isHorizontal);
	bool IsHorizontal(DungeonRect* rect1, DungeonRect* rect2);

	int m_tileData[TILE_HEIGHT_MAX][TILE_WIDTH_MAX];

	std::vector<DungeonRect*> m_childList;		//���������q���X�g
	std::vector<DungeonRoom> m_roomList;		//�������X�g
};