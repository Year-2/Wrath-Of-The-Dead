#include <iostream>
#include "game.h"


#include "fileparser.h"

void Test(int* a) {
	*a = 10000;
}


int main(int argc, char* args[])
{
	Game game = Game();
	if (!game.Init()) {
		std::cout << "Error could not init SDL!" << std::endl;
	} 
	game.Start();

	return 0;
}