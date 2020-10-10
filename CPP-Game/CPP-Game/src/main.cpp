#include <iostream>
#include "game.h"

//#include "datatypes.h"
//#include "fileparser.h"

int main(int argc, char* args[])
{
	Game game = Game();
	if (!game.Init()) {
		std::cout << "Error could not init SDL!" << std::endl;
	} 
	game.Start();

	return 0;

}