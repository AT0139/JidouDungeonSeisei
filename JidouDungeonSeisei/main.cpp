#include <iostream>
#include "DungeonAutoGeneration.h"
#include "DungeonRoom.h"

/*
task 
X��Y�������ɂȂ�Ȃ��ꍇ������@�i���X�g�Ɋi�[���鏇�Ԃ���邢�����j
�c���ѕ����ɓ�


*/

int main(void)
{
	srand((unsigned int)time(NULL));

	DungeonAutoGeneration dag;

	dag.Init();

	dag.Generate();

	dag.Draw();

	(void)getchar();
	return 0;
}