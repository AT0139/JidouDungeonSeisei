#pragma once

#include<vector>
#include "DungeonAutoGeneration.h"

class DungeonRoom;

/// <summary>
///	区画を管理するクラス  
/// 区画を分割していってダンジョンを作る  
/// 二分木で分割していくので親と最大2つの子を持っている  
/// 区画の中に部屋を作るイメージ
/// </summary>
class DungeonRect
{
public:
	DungeonRect() = delete;

	DungeonRect(DungeonRect* parent, DungeonRect* child1, DungeonRect* child2, int x, int y, int w, int h)
		:m_parent(parent), m_x(x), m_y(y), m_w(w), m_h(h) {
		m_child[0] = child1;
		m_child[1] = child2;
	}

	~DungeonRect();

	void RandomSplitting();

	void SortMostChild(std::vector<DungeonRect*>* mostChildList);

	DungeonRoom CreateRoom();
	
	void Draw(int mapData[][MAP_WIDTH_MAX]);

private:
	const int MIN_RECT = 5;	//最小区画サイズ
	const int MIN_ROOM_SIZE = 2;	//最小部屋サイズ

	bool SplitRectX(int splitX);
	bool SplitRectY(int splitY);


	int m_x, m_y;//区画左上座標
	int m_w, m_h;//区画の高さ、幅

	DungeonRect* m_parent;		//親区画
	DungeonRect* m_child[2];
};