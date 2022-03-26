#pragma once
#include"DungeonAutoGeneration.h"

class DungeonRect;

/// <summary>
/// ダンジョン内の部屋を管理するクラス
/// 区画の中に部屋がある
/// </summary>
class DungeonRoom
{
public:
	DungeonRoom(DungeonRect* parent, int x, int y, int w, int h) :m_parentRect(parent), m_x(x), m_y(y), m_w(w), m_h(h) {}
	DungeonRoom() = delete;

	void Generate(int mapData[][TILE_WIDTH_MAX]);

	DungeonRect* GetParentRect() { return m_parentRect; }
	int GetX() { return m_x; }
	int GetY() { return m_y; }
	int GetW() { return m_w; }
	int GetH() { return m_h; }

private:
	DungeonRect* m_parentRect;	//この部屋はどの区画の中にあるか

	int m_x;	//左上のx座標
	int m_y;	//左上のy座標
	int m_w;	//部屋の幅
	int m_h;	//部屋の高さ
};