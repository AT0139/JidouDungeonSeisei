#include "DungeonAutoGeneration.h"
#include "DungeonTile.h"
#include "DungeonRect.h"
#include <iostream>


DungeonAutoGeneration::DungeonAutoGeneration()
{
	//�ǂŖ��߂�
	FillAllWall();
}

void DungeonAutoGeneration::Init()
{
	//�ǂŖ��߂�
	FillAllWall();
}

void DungeonAutoGeneration::Generate()
{
	//�^�C������
	for (int y = 0; y < TILE_VERTICAL_NUM; y++)
	{
		for (int x = 0; x < TILE_HORIZONTAL_NUM; x++)
		{
			DungeonTile* tile = new DungeonTile();
			tile->Generate();
			tile->MapWriting(m_mapData, TILE_WIDTH_MAX * x, TILE_HEIGHT_MAX * y);
			m_tileList.push_back(tile);
		}
	}
	ConnectTiles();
}

//�S�Ă�ǂŖ��߂�
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

/// <summary>
/// �^�C�����m�𓹂Ō��Ԋ֐�
/// </summary>
void DungeonAutoGeneration::ConnectTiles()
{
	int room1Y = 0;
	int room2Y = 0;
	int room1X = 0;
	int room2X = 0;
	int temp = 0;
	int border = 0;
	int cor = 0;

	DungeonRoom* room1;
	DungeonRoom* room2;

	//���Ȃ��^�C���̌���
	//for (int i = 0; i < roadNum; i++)
	//{
	//	int nonRoadTile = rand() % (TILE_HORIZONTAL_NUM* TILE_VERTICAL_NUM);
	//}

	for (int y = 0; y < TILE_VERTICAL_NUM; y++)
	{
		for (int x = 0; x < TILE_HORIZONTAL_NUM; x++)
		{

#ifdef _DEBUG
			//=====================================
			//�f�o�b�O�p
			//����1��1����������
			//Draw();
			//(void)getchar();
			//=====================================
#endif //_DEBUG

			//�^�C���ԍ�
			int tileNum = x + (y * TILE_HORIZONTAL_NUM);

			//���Ȃ��^�C���ԍ��Ɠ����Ȃ�continue
			//if (tileNum == roadNum)
			//	continue;


			//�����o����������
			ROAD_DIRECTION dir = DirectionDetermining(tileNum);
			
			//��ԋ߂��������m������
			switch (dir)
			{
			case ROAD_DIRECTION::UP:
				//��ԋ߂������T��
				room1 = m_tileList.at(tileNum)->SeekNearestRoom(0, TILE_HEIGHT_MAX * y, ROAD_DIRECTION::UP);
				m_tileList.at(tileNum)->isUpRoad = true;
				room2 = m_tileList.at((size_t)tileNum - TILE_HORIZONTAL_NUM)->SeekNearestRoom(0, TILE_HEIGHT_MAX * y, ROAD_DIRECTION::DOWN);
				m_tileList.at((size_t)tileNum - TILE_HORIZONTAL_NUM)->isDownRoad = true;
				
				//���̕����̂ǂ�X�ʒu���瓹��L�΂���(����)
				room1X = rand() % (room1->GetW() - 2) + room1->GetX() + 1;
				room2X = rand() % (room2->GetW() - 2) + room2->GetX() + 1;

				cor = tileNum % TILE_HORIZONTAL_NUM;
				temp = tileNum / TILE_HORIZONTAL_NUM;

				//����L�΂�
				CreateRoadTileVertical(room2X + (cor * TILE_WIDTH_MAX), room2->GetY() + room2->GetH() + (temp - 1) * TILE_HEIGHT_MAX,
					room1X + (cor * TILE_WIDTH_MAX), room1->GetY() + (temp * TILE_HEIGHT_MAX));

				break;
			case ROAD_DIRECTION::RIGHT:
				room1 = m_tileList.at(tileNum)->SeekNearestRoom((x + 1) * TILE_WIDTH_MAX, 0, ROAD_DIRECTION::RIGHT);
				m_tileList.at(tileNum)->isRightRoad = true;
				room2 = m_tileList.at((size_t)tileNum + 1)->SeekNearestRoom(x * TILE_WIDTH_MAX, 0, ROAD_DIRECTION::LEFT);
				m_tileList.at((size_t)tileNum + 1)->isLeftRoad = true;

				room1Y = rand() % (room1->GetH() - 2) + room1->GetY() + 1;
				room2Y = rand() % (room2->GetH() - 2) + room2->GetY() + 1;

				cor = tileNum / TILE_HORIZONTAL_NUM;
				temp = tileNum % TILE_HORIZONTAL_NUM + 1;

				CreateRoadTileHorizontal(room1->GetX() + room1->GetW() + ((temp - 1)  * TILE_WIDTH_MAX), room1Y + (cor * TILE_HEIGHT_MAX),
					room2->GetX() + (temp * TILE_WIDTH_MAX), room2Y + (cor * TILE_HEIGHT_MAX));

				break;
			case ROAD_DIRECTION::DOWN:
				//��ԋ߂������T��
				room1 = m_tileList.at(tileNum)->SeekNearestRoom(0, TILE_HEIGHT_MAX * y, ROAD_DIRECTION::DOWN);
				m_tileList.at(tileNum)->isDownRoad = true;
				room2 = m_tileList.at((size_t)tileNum + TILE_HORIZONTAL_NUM)->SeekNearestRoom(0, TILE_HEIGHT_MAX * y, ROAD_DIRECTION::UP);
				m_tileList.at((size_t)tileNum + TILE_HORIZONTAL_NUM)->isUpRoad = true;
				
				//���̕����̂ǂ�X�ʒu���瓹��L�΂���(����)
				room1X = rand() % (room1->GetW() - 2) + room1->GetX() + 1;
				room2X = rand() % (room2->GetW() - 2) + room2->GetX() + 1;
				
				cor = tileNum % TILE_HORIZONTAL_NUM;
				temp = tileNum / TILE_HORIZONTAL_NUM + 1;
				
				//����L�΂�
				CreateRoadTileVertical(room1X + (cor * TILE_WIDTH_MAX), room1->GetY() + room1->GetH() +(temp - 1) * TILE_HEIGHT_MAX, room2X+ (cor * TILE_WIDTH_MAX),
					room2->GetY() +  (temp * TILE_HEIGHT_MAX));

				break;
			case ROAD_DIRECTION::LEFT:
				//-X�����ɓ���L�΂�(���ɐL�΂�)
				//�n�_�^�C��(�E��)
				room1 = m_tileList.at(tileNum)->SeekNearestRoom(x * TILE_WIDTH_MAX, 0, ROAD_DIRECTION::LEFT);
				m_tileList.at(tileNum)->isLeftRoad = true;
				//�I�_�^�C��(����) 
				room2 = m_tileList.at((size_t)tileNum - 1)->SeekNearestRoom(x * TILE_WIDTH_MAX, 0, ROAD_DIRECTION::RIGHT);
				m_tileList.at((size_t)tileNum - 1)->isRightRoad = true;

				room1Y = rand() % (room1->GetH() - 2) + room1->GetY() + 1;
				room2Y = rand() % (room2->GetH() - 2) + room2->GetY() + 1;

				cor = tileNum / TILE_HORIZONTAL_NUM;
				temp = tileNum % TILE_HORIZONTAL_NUM;

				CreateRoadTileHorizontal(room2->GetX() + room2->GetW() + (temp - 1) * TILE_WIDTH_MAX, room2Y + (cor * TILE_HEIGHT_MAX),
					room1->GetX() + (temp * TILE_WIDTH_MAX), room1Y + (cor * TILE_HEIGHT_MAX));

				break;
			}
		}
	}
}

/// <summary>
/// ���������̓��Ń^�C�������Ԋ֐��@����1�ɍ��ɂ��镔����n��
/// </summary>
/// <param name="x1">����1 X���W</param>
/// <param name="y1">����1 Y���W</param>
/// <param name="x2">����2 X���W</param>
/// <param name="y2">����2 Y���W</param>
void DungeonAutoGeneration::CreateRoadTileHorizontal(int x1, int y1, int x2, int y2)
{
	int borderX = abs((x2 - x1) / 2);
	//���������ɓ���L�΂�
	//1�߂̍��W���狫�E����
	for (int i = 0; i < borderX; i++)
	{
		m_mapData[y1][x1 + i] = MAPCHIP_DEBUG_ROAD;
	}
	//2�߂̍��W���狫�E����
	for (int i = 0; i < borderX; i++)
	{
		m_mapData[y2][x2 - i - 1] = MAPCHIP_DEBUG_ROAD;
	}

	//���E�ʒu�Ō���
	int dis;
	if (y1 <= y2)
	{
		dis = y2 - y1 + 1;	
		for (int i = 0; i < dis; i++)
		{
			m_mapData[y1 + i][x1 + borderX] = MAPCHIP_DEBUG;
		}
	}
	else
	{
		dis = y1 - y2 + 1;
		for (int i = 0; i < dis; i++)
		{
			m_mapData[y2 + i][x1 + borderX] = MAPCHIP_DEBUG;
		}
	}
}

/// <summary>
/// ���������̓��Ń^�C�������Ԋ֐��@����1�ɏ�ɂ��镔����n��
/// </summary>
/// <param name="x1">����1 X���W</param>
/// <param name="y1">����1 Y���W</param>
/// <param name="x2">����2 X���W</param>
/// <param name="y2">����2 Y���W</param>
void DungeonAutoGeneration::CreateRoadTileVertical(int x1, int y1, int x2, int y2)
{
	int borderY = abs((y2 - y1) / 2);

	//���������ɓ���L�΂�
	//1�߂̍��W���狫�E����
	for (int i = 0; i < borderY; i++)
	{
		m_mapData[y1 + i][x1] = MAPCHIP_DEBUG_ROAD;
	}
	//2�߂̍��W���狫�E����
	for (int i = 0; i < borderY; i++)
	{
		m_mapData[y2 - i - 1][x2] = MAPCHIP_DEBUG_ROAD;
	}

	//���E�ʒu�Ō���
	int dis;
	if (x1 <= x2)
	{
		dis = x2 - x1 + 1;
		for (int i = 0; i < dis; i++)
		{
			m_mapData[y1 + borderY][x1 + i] = MAPCHIP_DEBUG;
		}
	}
	else
	{
		dis = x1 - x2 + 1;
		for (int i = 0; i < dis; i++)
		{
			m_mapData[y1 + borderY][x2 + i] = MAPCHIP_DEBUG;
		}
	}
}

/// <summary>
/// ����L�΂������������_���ŕԂ��֐�
/// </summary>
/// <param name="tileNum">����L�΂��n�_�̃^�C���ԍ�</param>
/// <returns>����</returns>
ROAD_DIRECTION DungeonAutoGeneration::DirectionDetermining(int tileNum)
{
	ROAD_DIRECTION dir = ROAD_DIRECTION::UP;
	bool isDecide = false;
	
	int randDir = rand() % 4;
	while (!isDecide)
	{
		switch (randDir)
		{
		case 0:
			if (!(tileNum <= TILE_HORIZONTAL_NUM - 1) && !m_tileList.at(tileNum)->isUpRoad)
			{
				dir = ROAD_DIRECTION::UP;
				isDecide = true;
				break;
			}
			randDir++;
			break;
		case 1:
			if (!(tileNum % TILE_HORIZONTAL_NUM == TILE_HORIZONTAL_NUM - 1) && !m_tileList.at(tileNum)->isRightRoad)
			{
				dir = ROAD_DIRECTION::RIGHT;
				isDecide = true;
				break;
			}
			randDir++;
			break;
		case 2:
			if (!(tileNum / TILE_HORIZONTAL_NUM >= TILE_VERTICAL_NUM - 1) && !m_tileList.at(tileNum)->isDownRoad)
			{
				dir = ROAD_DIRECTION::DOWN;
				isDecide = true;
				break;
			}
			randDir++;
			break;
		case 3:
			if (!(tileNum % TILE_HORIZONTAL_NUM == 0) && !m_tileList.at(tileNum)->isLeftRoad)
			{
				dir = ROAD_DIRECTION::LEFT;
				isDecide = true;
				break;
			}
			randDir = 0;
			break;
		}
	}
	return dir;
}


//�`��
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
				std::cout << "��";
				break;
			case MAPCHIP_DEBUG:
				std::cout << "��";
				break;
			case MAPCHIP_DEBUG_ROAD:
				std::cout << "�Z";
				break;
			default:
				std::cout << m_mapData[y][x] - MAPCHIP_MAX -1 << " ";
				break;
			}
		}
		std::cout << std::endl;
	}
}



