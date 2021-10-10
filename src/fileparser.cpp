#include "fileparser.h"


PlayerInfo::PlayerInfo(string lineContents) {
	stringstream playerStream(lineContents);
	playerStream >> score;
}