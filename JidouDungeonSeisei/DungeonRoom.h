#pragma once
#include"DungeonAutoGeneration.h"

class DungeonRect;

/// <summary>
/// �_���W�������̕������Ǘ�����N���X
/// </summary>
class DungeonRoom
{
public:
	DungeonRoom(DungeonRect* parent, int x, int y, int w, int h) :m_parentRect(parent), m_x(x), m_y(y), m_w(w), m_h(h) {}
	DungeonRoom() = delete;

	void Generate(int mapData[][MAP_WIDTH_MAX]);

private:
	DungeonRect* m_parentRect;	//���̕����͂ǂ̋��̒��ɂ��邩

	int m_x;	//�����x���W
	int m_y;	//�����y���W
	int m_w;	//�����̕�
	int m_h;	//�����̍���
};