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
/// �^�C���𐶐�
/// </summary>
void DungeonTile::Generate()
{
	int cnt = 0;
	DungeonRect rect(nullptr, nullptr, nullptr, 0, 0, TILE_WIDTH_MAX, TILE_HEIGHT_MAX);	//�ő�T�C�Y�̋��

	rect.RandomSplitting();	//����
	rect.SortMostChild(&m_childList);//������������T��

	int c = 0;
	//���������
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
/// �����Ɏ󂯎�����}�b�v�f�[�^�Ƀ^�C���f�[�^����������
/// </summary>
/// <param name="mapData">�}�b�v�f�[�^</param>
/// <param name="xPos">�^�C������X���W</param>
/// <param name="yPos">�^�C������Y���W</param>
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
/// ����������W�Ɉ�ԋ߂�������T��
/// </summary>
/// <param name="x">x���W</param>
/// <param name="y">y���W</param>
/// <param name="dir">����</param>
/// <returns>��ԋ߂������|�C���^</returns>
DungeonRoom* DungeonTile::SeekNearestRoom(int x,int y, ROAD_DIRECTION dir)
{
	int distance = 10000;
	int nearRoomNo = 0;
	//���E�ʒu
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
		//�㑤
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
		//����
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
/// ���𐶐�����֐�
/// </summary>
void DungeonTile::CreateRoad()
{
	for (int i = 0; i < m_roomList.size() - 1; i++)
	{
		//=====================================
		//�f�o�b�O�p
		//����1��1����������
		//Draw();
		//(void)getchar();
		//=====================================

		DungeonRoom* room1 = &m_roomList.at(i);
		DungeonRoom* room2 = &m_roomList.at(i + 1);

		//�������
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
/// ���ۂɓ�����鏈�������Ă���֐�
/// </summary>
/// <param name="room1">�����N���X1</param>
/// <param name="room2">�����N���X2/param>
/// <param name="isHorizontal">���ɕ���ł���Ȃ�true</param>
void DungeonTile::CreateRoadWorking(DungeonRoom* room1, DungeonRoom* room2, bool isHorizontal)
{
	if (isHorizontal)
	{
		//���E�ʒu�擾
		int border = room1->GetParentRect()->GetX() + room1->GetParentRect()->GetW();

		//��������ʘH��L�΂��ʒu���� (�㉺1�}�X�͐�������Ȃ��悤��)
		int roadY1 = rand() % (room1->GetH() - 2) + room1->GetY() + 1;
		int roadY2 = rand() % (room2->GetH() - 2) + room2->GetY() + 1;

		//�������狫�E�ɒʘH��L�΂�
		int distance1 = abs(room1->GetX() + room1->GetW() - border);
		int distance2 = abs(room2->GetX() - border);

		//����1�ڂ̃��[�v
		for (int x = 0; x < distance1; x++)
		{
			m_tileData[roadY1][room1->GetX() + room1->GetW() + x] = MAPCHIP_DEBUG_ROAD;
		}
		//����2�ڂ̃��[�v
		for (int x = 0; x < distance2; x++)
		{
			m_tileData[roadY2][room2->GetX() - x - 1] = MAPCHIP_DEBUG_ROAD;
		}

		//���E����œ�������

		int startY;//�J�n�ʒu�擾(Y�ʒu����̓�)
		if (roadY1 < roadY2)
			startY = roadY1;
		else
			startY = roadY2;

		//���Ԃ̋���
		int roadDistance = abs(roadY1 - roadY2) + 1;

		//�}�b�v�f�[�^�̏�������
		for (int y = 0; y < roadDistance; y++)
		{
			m_tileData[startY + y][border] = MAPCHIP_DEBUG_ROAD;
		}
	}
	else
	{
		//�c�ɕ���ł���

		//���E�ʒu�擾
		int border = room1->GetParentRect()->GetY() + room1->GetParentRect()->GetH();

		//��������ʘH��L�΂��ʒu���� (���E1�}�X�͐�������Ȃ��悤��)
		int roadX1 = rand() % (room1->GetW() - 2) + room1->GetX() + 1;
		int roadX2 = rand() % (room2->GetW() - 2) + room2->GetX() + 1;

		//�������狫�E�ɒʘH��L�΂�
		int distance1 = abs(room1->GetY() + room1->GetH() - border);
		int distance2 = abs(room2->GetY() - border);

		//����1�ڂ̃��[�v
		for (int y = 0; y < distance1; y++)
		{
			m_tileData[room1->GetY() + room1->GetH() + y][roadX1] = MAPCHIP_DEBUG_ROAD;
		}
		//����2�ڂ̃��[�v
		for (int y = 0; y < distance2; y++)
		{
			m_tileData[room2->GetY() - y - 1][roadX2] = MAPCHIP_DEBUG_ROAD;
		}

		//���E����œ�������

		int startX;//�J�n�ʒu�擾(X�ʒu�����̓�)
		if (roadX1 < roadX2)
			startX = roadX1;
		else
			startX = roadX2;

		//���Ԃ̋���
		int roadDistance = abs(roadX1 - roadX2) + 1;

		//�}�b�v�f�[�^�̏�������
		for (int x = 0; x < roadDistance; x++)
		{
			m_tileData[border][startX + x] = MAPCHIP_DEBUG_ROAD;
		}
	}
}



/// <summary>
/// ��悪�ǂ̏c���ǂ���ɕ���ł���̂���Ԃ��֐�
/// </summary>
/// <param name="rect1">���1</param>
/// <param name="rect2">���2</param>
/// <returns>���ɕ���ł�����true</returns>
bool DungeonTile::IsHorizontal(DungeonRect* rect1, DungeonRect* rect2)
{
	//�������������Y���W�������Ȃ�
	if (rect1->GetY() == rect2->GetY())
	{
		//���ɕ���ł���
		return true;
	}
	else if (rect1->GetX() == rect2->GetX())
	{
		//�c�ɕ���ł���
		return false;
	}
	else
	{
		//�ǂ�����Ⴄ�̂ōċA�I�ɓ����̂����邩�T��
		return IsHorizontal(rect1->GetParent(), rect2);
	}
}
