#include <iostream>
#include "game.h"

#define NO_OF_WORDS_TO_REMOVE 2
std::string projectDir = SDL_GetBasePath();

int main(int argc, char* args[])
{
    for (char i = 0; i < NO_OF_WORDS_TO_REMOVE; i++) {
        char currentChar = 'a';
        while (currentChar != '\\') {
            projectDir.pop_back();
            currentChar = projectDir.back();
        }
    }

	//	MEMORY LEAK THINGY
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(30131);
	//_CrtDumpMemoryLeaks();

	Game game = Game();
	if (!game.Init()) {
		std::cout << "Error could not init SDL!" << "\n";
	}
	game.Start();

	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	return 0;
}