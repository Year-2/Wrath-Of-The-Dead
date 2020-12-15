#include "fileparser.h"


PlayerInfo::PlayerInfo(string lineContents) {
	stringstream playerStream(lineContents);
	playerStream >> username;
	playerStream >> score;
}

//TilemapInfo::TilemapInfo(string linecontents) {
//	for (int y = 0; y < MAP_SIZE_Y; y++)
//		for (int x = 0; x < MAP_SIZE_X; x++)
//			file >> MAP_DATA[y][x];
//}