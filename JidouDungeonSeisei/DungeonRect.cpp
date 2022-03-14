#include "DungeonRect.h"
#include "DungeonRoom.h"

/// <summary>
/// X�����ɕ�������֐�
/// </summary>
/// <param name="splitX">��������X���W</param>
/// <returns>�����o������true</returns>
bool DungeonRect::SplitRectX(int splitX)
{
	if (splitX < MIN_RECT || m_w - splitX < MIN_RECT)
		return false;	//�ŏ��T�C�Y���ł���̂�h��

	m_child[0] = new DungeonRect(this, nullptr, nullptr, m_x, m_y, splitX, m_h);
	m_child[1] = new DungeonRect(this, nullptr, nullptr, m_x + splitX, m_y, m_w - splitX, m_h);

	return true;
}

/// <summary>
/// Y�����ɕ�������֐�
/// </summary>
/// <param name="splitY">��������Y���W</param>
/// <returns>�����o������true</returns>
bool DungeonRect::SplitRectY(int splitY)
{
	if (splitY < MIN_RECT || m_h - splitY < MIN_RECT)
		return false;	//�ŏ��T�C�Y���ł���̂�h��

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
/// ���̃G���A�������_��XY�����ɕ�������֐�
/// </summary>
void DungeonRect::RandomSplitting()
{
	bool isSplit = false;	//�����o������

	//������0��������X�����ɕ���
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
/// ��ԉ��̎q��T���֐�
/// </summary>
/// <param name="mostChildList">��ԉ��̎q���i�[���郊�X�g�|�C���^</param>
void DungeonRect::SortMostChild(std::vector<DungeonRect*>* mostChildList)
{
	//�q��null�Ȃ炱�ꂪ��ԉ��Ȃ̂ŁA�ǉ�
	if (m_child[0] == nullptr)
	{
		mostChildList->push_back(this);
		return;
	}
	//��ԉ�����Ȃ������ꍇ
	else
	{
		m_child[0]->SortMostChild(mostChildList);
		m_child[1]->SortMostChild(mostChildList);
	}
}

/// <summary>
/// ���������֐�
/// ���͈͓̔��Ń����_������
/// </summary>
/// <returns>�쐬���ꂽ�����N���X</returns>
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
