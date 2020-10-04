#include <iostream>
#include "game.h"

#include "fontmanager.h"
#include "texturemanager.h"
#include "soundmanager.h"

int main(int argc, char* args[])
{
	Game game = Game();
	if (!game.Init()) {
		std::cout << "Error could not init SDL!" << std::endl;
	}
	game.Start();

	return 0;
}