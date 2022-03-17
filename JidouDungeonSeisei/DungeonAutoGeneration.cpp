#include "DungeonAutoGeneration.h"
#include "DungeonRect.h"
#include "DungeonRoom.h"
#include <iostream>

DungeonAutoGeneration::DungeonAutoGeneration()
{
	//壁で埋める
	FillAllWall();
}

void DungeonAutoGeneration::Init()
{
	//壁で埋める
	FillAllWall();
}

void DungeonAutoGeneration::Generate()
{
	int cnt = 0;
	DungeonRect rect(nullptr, nullptr, nullptr, 0, 0, MAP_WIDTH_MAX, MAP_HEIGHT_MAX);	//最大サイズの区画

	rect.RandomSplitting();	//分割
	rect.SortMostChild(&m_childList);//部屋を作る区画を探す

	int c=0;
	//部屋を作る
	for (auto it : m_childList)
	{
		c++;
		m_roomList.push_back(it->CreateRoom());
		
		m_roomList.at(cnt).Generate(m_mapData);
		it->Draw(m_mapData, c+ TILE_MAX);
		cnt++;
	}

	CreateRoad();
}

//全てを壁で埋める
void DungeonAutoGeneration::FillAllWall()
{
	for (int y = 0; y < MAP_HEIGHT_MAX; y++)
	{
		for (int x = 0; x < MAP_WIDTH_MAX; x++)
		{
			m_mapData[y][x] = TILE_WALL;
		}
	}
}

//描画
void DungeonAutoGeneration::Draw()
{
	system("cls");

	for (int y = 0; y < MAP_HEIGHT_MAX; y++)
	{
		for (int x = 0; x < MAP_WIDTH_MAX; x++)
		{
			switch (m_mapData[y][x])
			{
			case TILE_NONE:
				std::cout << "  ";
				break;
			case TILE_WALL:
				std::cout << "■";
				break;
			case TILE_DEBUG:
				std::cout << "〇";
				break;
			case TILE_DEBUG_ROAD:
				std::cout << "〇";
				break;
			default:
				std::cout << m_mapData[y][x] - TILE_MAX -1 << " ";
				break;
			}
		}
		std::cout << std::endl;
	}
}

/// <summary>
/// 道を生成する関数
/// </summary>
void DungeonAutoGeneration::CreateRoad()
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
		if (IsHorizontal(room1->GetParent(),room2->GetParent()))
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
void DungeonAutoGeneration::CreateRoadWorking(DungeonRoom* room1, DungeonRoom* room2, bool isHorizontal)
{
	if(isHorizontal)
	{
		//境界位置取得
		int border = room1->GetParent()->GetX() + room1->GetParent()->GetW();

		//部屋から通路を伸ばす位置生成 (上下1マスは生成されないように)
		int roadY1 = rand() % (room1->GetH() - 2) + room1->GetY() + 1;
		int roadY2 = rand() % (room2->GetH() - 2) + room2->GetY() + 1;

		//部屋から境界に通路を伸ばす
		int distance1 = abs(room1->GetX() + room1->GetW() - border);
		int distance2 = abs(room2->GetX() - border);

		//部屋1つ目のループ
		for (int x = 0; x < distance1; x++)
		{
			m_mapData[roadY1][room1->GetX() + room1->GetW() + x] = TILE_DEBUG;
		}										  
		//部屋2つ目のループ
		for (int x = 0; x < distance2; x++)
		{
			m_mapData[roadY2][room2->GetX() - x - 1] = TILE_DEBUG;
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
			m_mapData[startY + y][border] = TILE_DEBUG;
		}
	}
	else
	{
		//縦に並んでいる

		//境界位置取得
		int border = room1->GetParent()->GetY() + room1->GetParent()->GetH();

		//部屋から通路を伸ばす位置生成 (左右1マスは生成されないように)
		int roadX1 = rand() % (room1->GetW() - 2) + room1->GetX() + 1;
		int roadX2 = rand() % (room2->GetW() - 2) + room2->GetX() + 1;

		//部屋から境界に通路を伸ばす
		int distance1 = abs(room1->GetY() + room1->GetH() - border);
		int distance2 = abs(room2->GetY() - border);

		//部屋1つ目のループ
		for (int y = 0; y < distance1; y++)
		{
			m_mapData[room1->GetY() + room1->GetH() + y][roadX1] = TILE_DEBUG_ROAD;
		}
		//部屋2つ目のループ
		for (int y = 0; y < distance2; y++)
		{
			m_mapData[room2->GetY() - y - 1][roadX2] = TILE_DEBUG_ROAD;
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
			m_mapData[border][startX + x] = TILE_DEBUG_ROAD;
		}
	}
}

/// <summary>
/// 区画がどの縦横どちらに並んでいるのかを返す関数
/// </summary>
/// <param name="rect1">区画1</param>
/// <param name="rect2">区画2</param>
/// <returns>横に並んでいたらtrue</returns>
bool DungeonAutoGeneration::IsHorizontal(DungeonRect* rect1, DungeonRect* rect2)
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
		IsHorizontal(rect1->GetParent(), rect2);
	}
}
