#include <iostream>
#include "game.h"

int main(int argc, char* args[])
{
	//	MEMORY LEAK THINGY
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(186 );
	//_CrtSetBreakAlloc(192);
	_CrtDumpMemoryLeaks();

	Game game = Game();
	if (!game.Init()) {
		std::cout << "Error could not init SDL!" << std::endl;
	} 
	game.Start();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	return 0;

}