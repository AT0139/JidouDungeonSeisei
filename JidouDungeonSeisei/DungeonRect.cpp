#include "DungeonRect.h"
#include "DungeonRoom.h"

/// <summary>
/// X方向に分割する関数
/// </summary>
/// <param name="splitX">分割するX座標</param>
/// <returns>分割出来たらtrue</returns>
bool DungeonRect::SplitRectX(int splitX)
{
	if (splitX < MIN_RECT || m_w - splitX < MIN_RECT)
		return false;	//最小サイズができるのを防ぐ

	m_child[0] = new DungeonRect(this, nullptr, nullptr, m_x, m_y, splitX, m_h);
	m_child[1] = new DungeonRect(this, nullptr, nullptr, m_x + splitX, m_y, m_w - splitX, m_h);

	return true;
}

/// <summary>
/// Y方向に分割する関数
/// </summary>
/// <param name="splitY">分割するY座標</param>
/// <returns>分割出来たらtrue</returns>
bool DungeonRect::SplitRectY(int splitY)
{
	if (splitY < MIN_RECT || m_h - splitY < MIN_RECT)
		return false;	//最小サイズができるのを防ぐ

	m_child[0] = new DungeonRect(this, nullptr, nullptr, m_x, m_y, m_w, splitY);
	m_child[1] = new DungeonRect(this, nullptr, nullptr, m_x, m_y + splitY, m_w, m_h - splitY);
	return true;
}

DungeonRect::~DungeonRect()
{
	delete m_child[0];
	delete m_child[1];
}

/// <summary>
/// このエリアをランダムXY方向に分割する関数
/// </summary>
void DungeonRect::RandomSplitting()
{
	bool isSplit = false;	//分割出来たか

	//乱数が0だったらX方向に分割
	if (rand() % 2 <= 0)
	{
		int div = m_w - MIN_RECT * 2;
		if (div <= 0)
			return;

		int x = rand() % div + MIN_RECT;

		isSplit = SplitRectX(x);
	}
	else
	{
		int div = m_h - MIN_RECT * 2;
		if (div <= 0)
			return;

		int y = rand() % div + MIN_RECT;

		isSplit = SplitRectY(y);
	}

	if (isSplit)
	{
		auto child = m_child[0];
		child->RandomSplitting();
	}
}

/// <summary>
/// 一番下の子を探す関数
/// </summary>
/// <param name="mostChildList">一番下の子を格納するリストポインタ</param>
void DungeonRect::SortMostChild(std::vector<DungeonRect*>* mostChildList)
{
	//子がnullならこれが一番下なので、追加
	if (m_child[0] == nullptr)
	{
		mostChildList->push_back(this);
		return;
	}
	//一番下じゃなかった場合
	else
	{
		m_child[0]->SortMostChild(mostChildList);
		m_child[1]->SortMostChild(mostChildList);
	}
}

/// <summary>
/// 部屋を作る関数
/// 区画の範囲内でランダム生成
/// </summary>
/// <returns>作成された部屋クラス</returns>
DungeonRoom DungeonRect::CreateRoom()
{
	int temp = m_w;
	int tempy = m_y;

	int w = rand() % (m_w - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;
	int h = rand() % (m_h - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;
	int x = m_x + rand() % (m_w - w);
	int y = m_y + rand() % (m_h - h);

	return DungeonRoom(this,x, y, w, h);
}

void DungeonRect::Draw(int mapData[][MAP_WIDTH_MAX])
{
	mapData[m_y][m_x] = TILE_DEBUG;
}
