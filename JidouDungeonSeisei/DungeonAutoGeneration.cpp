#include "DungeonAutoGeneration.h"
#include "DungeonRect.h"
#include "DungeonRoom.h"
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
	int cnt = 0;
	DungeonRect rect(nullptr, nullptr, nullptr, 0, 0, MAP_WIDTH_MAX, MAP_HEIGHT_MAX);	//�ő�T�C�Y�̋��

	rect.RandomSplitting();	//����
	rect.SortMostChild(&m_childList);//������������T��

	int c=0;
	//���������
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
	system("cls");

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
			case TILE_DEBUG_ROAD:
				std::cout << "�Z";
				break;
			default:
				std::cout << m_mapData[y][x] - TILE_MAX << " ";
				break;
			}
		}
		std::cout << std::endl;
	}
}

/// <summary>
/// ���𐶐�����֐�
/// </summary>
void DungeonAutoGeneration::CreateRoad()
{
	for (int i = 0; i < m_roomList.size() - 1; i++)
	{
		//=====================================
		//�f�o�b�O�p
		Draw();
		(void)getchar();
		//=====================================

		DungeonRoom room1 = m_roomList.at(i);
		DungeonRoom room2 = m_roomList.at(i + 1);

		//�������������Y���W�������Ȃ牡�ɕ���ł���
		if (room1.GetParent()->GetY() == room2.GetParent()->GetY())
		{
			//���E�ʒu�擾
			int border = room1.GetParent()->GetX() + room1.GetParent()->GetW();

			//��������ʘH��L�΂��ʒu���� (�㉺1�}�X�͐�������Ȃ��悤��)
			int roadY1 = rand() % (room1.GetH() - 2) + room1.GetY() + 1;
			int roadY2 = rand() % (room2.GetH() - 2) + room2.GetY() + 1;

			//�������狫�E�ɒʘH��L�΂�
			int distance1 = abs(room1.GetX() + room1.GetW() - border);
			int distance2 = abs(room2.GetX() - border);

			//����1�ڂ̃��[�v
			for (int x = 0; x < distance1; x++)
			{
				m_mapData[roadY1][room1.GetX() + room1.GetW() + x] = TILE_DEBUG;
			}
			//����2�ڂ̃��[�v
			for (int x = 0; x < distance2; x++)
			{
				m_mapData[roadY2][room2.GetX() - x - 1] = TILE_DEBUG;
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
				m_mapData[startY + y][border] = TILE_DEBUG;
			}
		}
		//�c�ɕ���ł���
		else if (room1.GetParent()->GetX() == room2.GetParent()->GetX())
		{
			//���E�ʒu�擾
			int border = room1.GetParent()->GetY() + room1.GetParent()->GetH();

			//��������ʘH��L�΂��ʒu���� (���E1�}�X�͐�������Ȃ��悤��)
			int roadX1 = rand() % (room1.GetW() - 2) + room1.GetX() + 1;
			int roadX2 = rand() % (room2.GetW() - 2) + room2.GetX() + 1;

			//�������狫�E�ɒʘH��L�΂�
			int distance1 = abs(room1.GetY() + room1.GetH() - border);
			int distance2 = abs(room2.GetY() - border);

			//����1�ڂ̃��[�v
			for (int y = 0; y < distance1; y++)
			{
				m_mapData[room1.GetY() + room1.GetH() + y][roadX1] = TILE_DEBUG_ROAD;
			}
			//����2�ڂ̃��[�v
			for (int y = 0; y < distance2; y++)
			{
				m_mapData[room2.GetY() - y - 1][roadX2] = TILE_DEBUG_ROAD;
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
				m_mapData[border][startX + x] = TILE_DEBUG_ROAD;
			}
		}
		//X��Y�������l���Ȃ��ꍇ
		else
		{
			//����1�̐e�̐e���ƕ���2�̐e����Y���W�������Ȃ牡�ɕ���ł���
			if (room1.GetParent()->GetParent()->GetY() == room2.GetParent()->GetY())
			{
				//���E�ʒu�擾
				int border = room1.GetParent()->GetX() + room1.GetParent()->GetW();
			}
			//X���W�������Ȃ�c�ɕ���ł���
			else
			{

			}
		}
	}
}