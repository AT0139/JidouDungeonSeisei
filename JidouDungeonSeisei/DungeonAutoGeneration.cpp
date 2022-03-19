#include "DungeonAutoGeneration.h"
#include "DungeonTile.h"
#include <iostream>

DungeonAutoGeneration::DungeonAutoGeneration()
{
	//•Ç‚Å–„‚ß‚é
	FillAllWall();
}

void DungeonAutoGeneration::Init()
{
	//•Ç‚Å–„‚ß‚é
	FillAllWall();
}

void DungeonAutoGeneration::Generate()
{
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			DungeonTile* tile = new DungeonTile();
			tile->Generate();
			tile->MapWriting(m_mapData, TILE_WIDTH_MAX * x, TILE_HEIGHT_MAX * y);
		}
	}
}

//‘S‚Ä‚ð•Ç‚Å–„‚ß‚é
void DungeonAutoGeneration::FillAllWall()
{
	for (int y = 0; y < MAP_HEIGHT_MAX; y++)
	{
		for (int x = 0; x < MAP_WIDTH_MAX; x++)
		{
			m_mapData[y][x] = MAPCHIP_WALL;
		}
	}
}

//•`‰æ
void DungeonAutoGeneration::Draw()
{
	system("cls");

	for (int y = 0; y < MAP_HEIGHT_MAX; y++)
	{
		for (int x = 0; x < MAP_WIDTH_MAX; x++)
		{
			switch (m_mapData[y][x])
			{
			case MAPCHIP_NONE:
				std::cout << "  ";
				break;
			case MAPCHIP_WALL:
				std::cout << "¡";
				break;
			case MAPCHIP_DEBUG:
				std::cout << "Z";
				break;
			case MAPCHIP_DEBUG_ROAD:
				std::cout << "Z";
				break;
			default:
				std::cout << m_mapData[y][x] - MAPCHIP_MAX -1 << " ";
				break;
			}
		}
		std::cout << std::endl;
	}
}



