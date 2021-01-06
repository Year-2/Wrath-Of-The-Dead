#include <iostream>
#include "game.h"

int main(int argc, char* args[])
{
	//	MEMORY LEAK THINGY
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(380);
	_CrtDumpMemoryLeaks();

	Game game = Game();
	if (!game.Init()) {
		std::cout << "Error could not init SDL!" << "\n";
	} 
	game.Start();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	return 0;

}

//#include "cryptopp/cryptlib.h"
//#include "cryptopp/sha.h"
//#include <iostream>
//
//int main(int argc, char* argv[])
//{
//    using namespace CryptoPP;
//
//    SHA256 hash;
//    std::cout << "Name: " << hash.AlgorithmName() << std::endl;
//    std::cout << "Digest size: " << hash.DigestSize() << std::endl;
//    std::cout << "Block size: " << hash.BlockSize() << std::endl;
//
//    return 0;
//}