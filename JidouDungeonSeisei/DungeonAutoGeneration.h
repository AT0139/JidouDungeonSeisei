#pragma once

#include <vector>

#define MAP_WIDTH_MAX  50		//マップ横最大値
#define MAP_HEIGHT_MAX  50		//マップ縦最大値

class DungeonRect;
class DungeonRoom;

enum DUNGEON_TILE
{
	TILE_NONE,
	TILE_WALL,
	TILE_DEBUG,



	TILE_MAX,
};

class DungeonAutoGeneration
{
public:
	DungeonAutoGeneration();

	void Init();
	void Generate();
	void FillAllWall();

	void Draw();
private:

 
	static const int SPRIT_RECT_MAX = 5;	//部屋分割最大数

	static const int MIN_ROOM_SIZE = 3;
	static const int MAX_ROOM_SIZE = 5;

	int m_mapData[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];	//2次元配列マップデータ

	std::vector<DungeonRect*> m_childList;		//部屋を作る子リスト
	std::vector<DungeonRoom> m_roomList;		//部屋リスト
};