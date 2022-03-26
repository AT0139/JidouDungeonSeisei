#pragma once

#include "DungeonAutoGeneration.h"
#include "DungeonRoom.h"
class DungeonRect;
class DungeonRoom;

/// <summary>
/// ダンジョン内のタイルを作る関数
/// マップはタイルを並べて作る
/// タイルの中には区画、部屋がある
/// </summary>
class DungeonTile
{
public:
	DungeonTile();
	void Generate();
	void MapWriting(int mapData[][MAP_WIDTH_MAX],int xPos,int yPos);

	DungeonRoom* SeekNearestRoom(int x,int y, ROAD_DIRECTION dir);

	bool isUpRoad;
	bool isDownRoad;
	bool isLeftRoad;
	bool isRightRoad;

	void CreateRoadWorking(DungeonRoom* room1, DungeonRoom* room2, bool isHorizontal);

private:
	void CreateRoad();
	bool IsHorizontal(DungeonRect* rect1, DungeonRect* rect2);

	int m_tileData[TILE_HEIGHT_MAX][TILE_WIDTH_MAX];

	std::vector<DungeonRect*> m_childList;		//部屋を作る子リスト
	std::vector<DungeonRoom> m_roomList;		//部屋リスト
};