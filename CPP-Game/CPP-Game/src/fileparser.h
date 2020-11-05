#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <exception>

#include <iostream>

class PlayerInfo {
public:
	PlayerInfo(std::string lineContents);

	int GetScore() { return score; }
	std::string GetUsername() { return username; }
	std::string GetTime() { return time; }

	void PrintPlayerInfo() { std::cout << username << " " << time << " " << score << "\n"; }

private:
	std::string username;
	std::string time;
	int score;
};

class FileParserPlayer {
public:
	FileParserPlayer() {};
	std::vector<PlayerInfo> GetList();

	void GetFile(std::string filename);
	void SetFile() {};

	void PrintList();

private:
	std::vector<PlayerInfo> items;
};

class TextFileError : public std::exception {
public:
	const char* what() const throw() { return "TextFile Error"; }
};

