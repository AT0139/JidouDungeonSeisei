#include "DungeonTile.h"
#include "DungeonRect.h"
#include "DungeonRoom.h"
#include <vector>


DungeonTile::DungeonTile()
{
	isUpRoad = false;
	isDownRoad = false;
	isLeftRoad = false;
	isRightRoad = false;

	for (int y = 0; y < TILE_HEIGHT_MAX; y++)
	{
		for (int x = 0; x < TILE_WIDTH_MAX; x++)
		{
			m_tileData[y][x] = MAPCHIP_WALL;
		}
	}
}

/// <summary>
/// タイルを生成
/// </summary>
void DungeonTile::Generate()
{
	int cnt = 0;
	DungeonRect rect(nullptr, nullptr, nullptr, 0, 0, TILE_WIDTH_MAX, TILE_HEIGHT_MAX);	//最大サイズの区画

	rect.RandomSplitting();	//分割
	rect.SortMostChild(&m_childList);//部屋を作る区画を探す

	int c = 0;
	//部屋を作る
	for (auto it : m_childList)
	{
		c++;
		m_roomList.push_back(it->CreateRoom());

		m_roomList.at(cnt).Generate(m_tileData);
		it->Draw(m_tileData, c + MAPCHIP_MAX);
		cnt++;
	}

	CreateRoad();
}

/// <summary>
/// 引数に受け取ったマップデータにタイルデータを書き込む
/// </summary>
/// <param name="mapData">マップデータ</param>
/// <param name="xPos">タイル左上X座標</param>
/// <param name="yPos">タイル左上Y座標</param>
void DungeonTile::MapWriting(int mapData[][MAP_WIDTH_MAX], int xPos, int yPos)
{
	for (int y = 0; y < TILE_HEIGHT_MAX; y++)
	{
		for (int x = 0; x < TILE_WIDTH_MAX; x++)
		{
			mapData[y + yPos][x + xPos] = m_tileData[y][x];
		}
	}
}

/// <summary>
/// もらった座標に一番近い部屋を探す
/// </summary>
/// <param name="x">x座標</param>
/// <param name="y">y座標</param>
/// <param name="dir">方向</param>
/// <returns>一番近い部屋ポインタ</returns>
DungeonRoom* DungeonTile::SeekNearestRoom(int x,int y, ROAD_DIRECTION dir)
{
	int distance = 10000;
	int nearRoomNo = 0;
	//境界位置
	switch(dir)
	{
	case ROAD_DIRECTION::RIGHT:
		for (int i = 0; i < m_roomList.size(); ++i)
		{
			int roomdis = x - (m_roomList.at(i).GetX() + m_roomList.at(i).GetW());
			if (distance > roomdis)
			{
				nearRoomNo = i;
				distance = roomdis;
			}
		}
		return &m_roomList.at(nearRoomNo);
	case ROAD_DIRECTION::LEFT:
		for (int i = 0; i < m_roomList.size(); ++i)
		{
			int roomdis = m_roomList.at(i).GetX() - x;
			if (distance > roomdis)
			{
				nearRoomNo = i;
				distance = roomdis;
			}
		}
		return &m_roomList.at(nearRoomNo);
	case ROAD_DIRECTION::UP:
		//上側
		for (int i = 0; i < m_roomList.size(); ++i)
		{
			int roomdis = m_roomList.at(i).GetY() - y;
			if (distance > roomdis)
			{
				nearRoomNo = i;
				distance = roomdis;
			}
		}
		return &m_roomList.at(nearRoomNo);
	case ROAD_DIRECTION::DOWN:
		//下側
		for (int i = 0; i < m_roomList.size(); ++i)
		{
			int roomdis = y - (m_roomList.at(i).GetY() + m_roomList.at(i).GetH());
			if (distance > roomdis)
			{
				nearRoomNo = i;
				distance = roomdis;
			}
		}
		return &m_roomList.at(nearRoomNo);
	}

	return nullptr;
}




/// <summary>
/// 道を生成する関数
/// </summary>
void DungeonTile::CreateRoad()
{
	for (int i = 0; i < m_roomList.size() - 1; i++)
	{
		//=====================================
		//デバッグ用
		//道を1つ1つ生成させる
		//Draw();
		//(void)getchar();
		//=====================================

		DungeonRoom* room1 = &m_roomList.at(i);
		DungeonRoom* room2 = &m_roomList.at(i + 1);

		//道を作る
		if (IsHorizontal(room1->GetParentRect(), room2->GetParentRect()))
		{
			CreateRoadWorking(room1, room2, true);
		}
		else
		{
			CreateRoadWorking(room1, room2, false);
		}
	}
}

/// <summary>
/// 実際に道を作る処理をしている関数
/// </summary>
/// <param name="room1">部屋クラス1</param>
/// <param name="room2">部屋クラス2/param>
/// <param name="isHorizontal">横に並んでいるならtrue</param>
void DungeonTile::CreateRoadWorking(DungeonRoom* room1, DungeonRoom* room2, bool isHorizontal)
{
	if (isHorizontal)
	{
		//境界位置取得
		int border = room1->GetParentRect()->GetX() + room1->GetParentRect()->GetW();

		//部屋から通路を伸ばす位置生成 (上下1マスは生成されないように)
		int roadY1 = rand() % (room1->GetH() - 2) + room1->GetY() + 1;
		int roadY2 = rand() % (room2->GetH() - 2) + room2->GetY() + 1;

		//部屋から境界に通路を伸ばす
		int distance1 = abs(room1->GetX() + room1->GetW() - border);
		int distance2 = abs(room2->GetX() - border);

		//部屋1つ目のループ
		for (int x = 0; x < distance1; x++)
		{
			m_tileData[roadY1][room1->GetX() + room1->GetW() + x] = MAPCHIP_DEBUG_ROAD;
		}
		//部屋2つ目のループ
		for (int x = 0; x < distance2; x++)
		{
			m_tileData[roadY2][room2->GetX() - x - 1] = MAPCHIP_DEBUG_ROAD;
		}

		//境界線上で道を結ぶ

		int startY;//開始位置取得(Y位置が上の道)
		if (roadY1 < roadY2)
			startY = roadY1;
		else
			startY = roadY2;

		//道間の距離
		int roadDistance = abs(roadY1 - roadY2) + 1;

		//マップデータの書き換え
		for (int y = 0; y < roadDistance; y++)
		{
			m_tileData[startY + y][border] = MAPCHIP_DEBUG_ROAD;
		}
	}
	else
	{
		//縦に並んでいる

		//境界位置取得
		int border = room1->GetParentRect()->GetY() + room1->GetParentRect()->GetH();

		//部屋から通路を伸ばす位置生成 (左右1マスは生成されないように)
		int roadX1 = rand() % (room1->GetW() - 2) + room1->GetX() + 1;
		int roadX2 = rand() % (room2->GetW() - 2) + room2->GetX() + 1;

		//部屋から境界に通路を伸ばす
		int distance1 = abs(room1->GetY() + room1->GetH() - border);
		int distance2 = abs(room2->GetY() - border);

		//部屋1つ目のループ
		for (int y = 0; y < distance1; y++)
		{
			m_tileData[room1->GetY() + room1->GetH() + y][roadX1] = MAPCHIP_DEBUG_ROAD;
		}
		//部屋2つ目のループ
		for (int y = 0; y < distance2; y++)
		{
			m_tileData[room2->GetY() - y - 1][roadX2] = MAPCHIP_DEBUG_ROAD;
		}

		//境界線上で道を結ぶ

		int startX;//開始位置取得(X位置が左の道)
		if (roadX1 < roadX2)
			startX = roadX1;
		else
			startX = roadX2;

		//道間の距離
		int roadDistance = abs(roadX1 - roadX2) + 1;

		//マップデータの書き換え
		for (int x = 0; x < roadDistance; x++)
		{
			m_tileData[border][startX + x] = MAPCHIP_DEBUG_ROAD;
		}
	}
}



/// <summary>
/// 区画がどの縦横どちらに並んでいるのかを返す関数
/// </summary>
/// <param name="rect1">区画1</param>
/// <param name="rect2">区画2</param>
/// <returns>横に並んでいたらtrue</returns>
bool DungeonTile::IsHorizontal(DungeonRect* rect1, DungeonRect* rect2)
{
	//部屋がある区画のY座標が同じなら
	if (rect1->GetY() == rect2->GetY())
	{
		//横に並んでいる
		return true;
	}
	else if (rect1->GetX() == rect2->GetX())
	{
		//縦に並んでいる
		return false;
	}
	else
	{
		//どちらも違うので再帰的に同じのがあるか探す
		return IsHorizontal(rect1->GetParent(), rect2);
	}
}
