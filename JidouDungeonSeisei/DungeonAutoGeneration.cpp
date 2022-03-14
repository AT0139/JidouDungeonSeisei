#include "DungeonAutoGeneration.h"
#include "DungeonRect.h"
#include "DungeonRoom.h"
#include <iostream>

DungeonAutoGeneration::DungeonAutoGeneration()
{
}

void DungeonAutoGeneration::Init()
{
	//�ǂŖ��߂�
	FillAllWall();
}

void DungeonAutoGeneration::Generate()
{
	int cnt = 0;
	DungeonRect rect(nullptr, nullptr, nullptr, 0, 0, MAP_WIDTH_MAX, MAP_HEIGHT_MAX);	//�ő�T�C�Y�̋��

	rect.RandomSplitting();	//����
	rect.SortMostChild(&m_childList);//������������T��

	for (auto it : m_childList)
	{
		m_roomList.push_back(it->CreateRoom());
		
		m_roomList.at(cnt).Generate(m_mapData);
		it->Draw(m_mapData);
		cnt++;
	}
}

//�S�Ă�ǂŖ��߂�
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

//�`��
void DungeonAutoGeneration::Draw()
{
	for (int y = 0; y < MAP_HEIGHT_MAX; y++)
	{
		for (int x = 0; x < MAP_WIDTH_MAX; x++)
		{
			switch (m_mapData[y][x])
			{
			case TILE_NONE:
				std::cout << "��";
				break;
			case TILE_WALL:
				std::cout << "��";
				break;
			case TILE_DEBUG:
				std::cout << "��";
				break;
			}
		}
		std::cout << std::endl;
	}
}

