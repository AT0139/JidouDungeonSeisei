#include "DungeonRoom.h"
#include "DungeonAutoGeneration.h"

void DungeonRoom::Generate(int mapData[][TILE_WIDTH_MAX])
{
	for (int y = 0; y < m_h; y++)
	{
		for (int x = 0; x < m_w; x++)
		{
			mapData[m_y + y][m_x + x] = MAPCHIP_NONE;
		}
	}
}