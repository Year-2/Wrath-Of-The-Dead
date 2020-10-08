#include "fileparser.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::stringstream;

PlayerInfo::PlayerInfo(string lineContents) {
	stringstream playerStream(lineContents);
	playerStream >> username;
	playerStream >> time;
	playerStream >> score;
}

void FileParserPlayer::GetFile(std::string filename) {
	try {
		const char* dir = "assets/files/";
		ifstream scoreFile(string(string(dir) + string(filename)));
		if (!scoreFile) throw TextFileError();

		string lineContents;
		while (!scoreFile.eof())
		{
			getline(scoreFile, lineContents);
			PlayerInfo s(lineContents);
			items.push_back(s);
		}
		scoreFile.close();
		sort(items.begin(), items.end(), [](PlayerInfo& i1, PlayerInfo& i2)
			{
				return i1.GetScore() > i2.GetScore();
			});
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << std::endl;
		std::cout << "\t" << e.what();
	}
}

std::vector<PlayerInfo> FileParserPlayer::GetList() {
	return items;
}

void FileParserPlayer::PrintList() {
	for (auto& player : items) player.PrintPlayerInfo();
}
