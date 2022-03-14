#include <iostream>
#include "DungeonAutoGeneration.h"
#include "DungeonRoom.h"

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