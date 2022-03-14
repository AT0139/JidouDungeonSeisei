#pragma once

#include<vector>
#include "DungeonAutoGeneration.h"

class DungeonRoom;

/// <summary>
///	�����Ǘ�����N���X  
/// ���𕪊����Ă����ă_���W���������  
/// �񕪖؂ŕ������Ă����̂Őe�ƍő�2�̎q�������Ă���  
/// ���̒��ɕ��������C���[�W
/// </summary>
class DungeonRect
{
public:
	DungeonRect() = delete;

	DungeonRect(DungeonRect* parent, DungeonRect* child1, DungeonRect* child2, int x, int y, int w, int h)
		:m_parent(parent), m_x(x), m_y(y), m_w(w), m_h(h) {
		m_child[0] = child1;
		m_child[1] = child2;
	}

	~DungeonRect();

	void RandomSplitting();

	void SortMostChild(std::vector<DungeonRect*>* mostChildList);

	DungeonRoom CreateRoom();
	
	void Draw(int mapData[][MAP_WIDTH_MAX]);

private:
	const int MIN_RECT = 5;	//�ŏ����T�C�Y
	const int MIN_ROOM_SIZE = 2;	//�ŏ������T�C�Y

	bool SplitRectX(int splitX);
	bool SplitRectY(int splitY);


	int m_x, m_y;//��捶����W
	int m_w, m_h;//���̍����A��

	DungeonRect* m_parent;		//�e���
	DungeonRect* m_child[2];
};