#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <exception>
#include <iostream>
#include <fstream>

using namespace std;
#define LENGTH 10

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::stringstream;

class PlayerInfo {
public:
	PlayerInfo(std::string lineContents);

	int GetScore() { return score; }
	std::string GetUsername() { return username; }

	void PrintPlayerInfo() { std::cout << username << " " << score << "\n"; }

private:
	std::string username;
	int score;
};

class TextFileError : public std::exception {
public:
	const char* what() const throw() { return "TextFile Error"; }
};

template<typename T>
class TextFileParser {
public:
	TextFileParser(const std::string filename, void(*func)(std::vector<T*>&) = [](std::vector<T*>&) {}) {
		try {
			string dir = "assets/files/";
			ifstream scoreFile(string(dir) + string(filename));
			if (!scoreFile) throw TextFileError();

			string lineContents;
			while (!scoreFile.eof())
			{
				getline(scoreFile, lineContents);
				items.push_back(new T(lineContents));
			}
			scoreFile.close();

			func(items);
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what();
		}
	}

	~TextFileParser() {
		for (T* item : items) {
			delete item;
		}
	}

	void GetFile(const std::string filename) {};
	void SetFile() {};

	void PrintList() {
		for (auto& it : items)
			it->PrintPlayerInfo();
	}

	std::vector<T>& GetList() {
		return items;
	}

private:
	std::vector<T*> items;
};

//TODO: Make this a generic template at some point. T
class BinaryFileParser {
public:

	void GenerateFile(string filename) {
		string dir = "assets/files/bin/";
		int* arr = new int[LENGTH];
		std::fill(arr, arr + LENGTH, 0);

		ofstream file;
		file.open(dir + filename, ios::out | ios::binary);
		if (!file) cout << "ERROR 404\n";

		file.write(reinterpret_cast<char*>(arr), LENGTH * sizeof(int));
		file.close();

		cout << "FILE CREATED!\n";

		delete[] arr;
	}

	void GenerateTilemapFile(string filename) {
		const int yWidth = 18, xWidth = 32;

		string dir = "assets/files/bin/";
		int* arr = new int[yWidth * xWidth];

		int map[yWidth][xWidth] = {
		{ 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		};

		int index = 0;
		for (int y = 0; y < yWidth; y++)
		{
			for (int x = 0; x < xWidth; x++)
			{
				arr[index] = map[y][x];
				index++;
			}
		}

		ofstream file;
		file.open(dir + filename, ios::out | ios::binary);
		if (!file) cout << "ERROR 404\n";

		file.write(reinterpret_cast<char*>(arr), (yWidth * xWidth) * sizeof(int));
		file.close();

		cout << "TILEMAP FILE CREATED!\n";

		delete[] arr;
	}

	int* ReadFile(string filename, int len) {
		string dir = "assets/files/bin/";
		int* arr = new int[len];

		ifstream file;
		file.open(dir + filename, ios::in | ios::binary);
		if (!file) cout << "ERROR\n";

		file.read(reinterpret_cast<char*>(arr), len * sizeof(int));
		file.close();

		cout << "FILE READ!\n";

		return arr;
	}
};



