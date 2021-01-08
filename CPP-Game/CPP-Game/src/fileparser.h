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
#include <type_traits>

#include "../lib/HASHING-1.0/xxhash64.h"

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

	void PrintPlayerInfo() { std::cout << score << "\n"; }

private:
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

	void SetFile() {};

	void PrintList() {
		for (auto& it : items)
			it->PrintPlayerInfo();
	}

	std::vector<T*>& GetList() {
		return items;
	}

private:
	std::vector<T*> items;
};

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
			{ 30,  3,  2,  3,  2,  2,  3,  6,  4,  4,  2,  3,  1,  4,  2,  3,  2,  3,  2,  3,  4,  1,  2,  9,  3,  3,  4,  2,  2,  1,  2, 31 },
			{ 34, 26, 27, 19, 23, 21, 23, 12, 28, 19, 18, 25, 25, 23, 28, 24, 25, 21, 25, 28, 20, 25, 26, 15, 28, 24, 25, 26, 23, 24, 28, 35 },
			{ 34, 20, 19, 20, 28, 21, 18, 20, 22, 24, 25, 28, 22, 25, 23, 24, 25, 18, 23, 18, 23, 28, 23, 19, 21, 22, 18, 28, 24, 25, 26, 35 },
			{ 34, 25, 28, 21, 23, 20, 28, 27, 24, 21, 20, 19, 27, 24, 26, 23, 28, 22, 22, 24, 27, 23, 24, 23, 18, 19, 22, 23, 24, 23, 25, 35 },
			{ 34, 22, 18, 26, 22, 22, 18, 21, 21, 23, 26, 22, 25, 26, 20, 18, 26, 25, 25, 22, 19, 23, 20, 25, 27, 18, 24, 21, 26, 22, 19, 35 },
			{ 34, 24, 20, 25, 20, 21, 24, 23, 18, 23, 25, 22, 24, 19, 22, 25, 27, 23, 25, 18, 25, 20, 18, 18, 22, 25, 23, 19, 19, 28, 27, 35 },
			{ 34, 18, 21, 24, 24, 19, 25, 22, 24, 25, 23, 26, 19, 21, 18, 23, 22, 25, 22, 23, 25, 24, 21, 20, 23, 25, 26, 20, 18, 18, 19, 35 },
			{ 34, 23, 22, 27, 26, 25, 26, 21, 22, 21, 23, 21, 25, 26, 23, 22, 19, 18, 24, 21, 25, 21, 22, 22, 23, 26, 20, 26, 26, 24, 20, 35 },
			{ 34, 28, 26, 21, 23, 25, 24, 23, 21, 20, 19, 27, 21, 24, 18, 19, 24, 23, 25, 26, 25, 21, 20, 24, 26, 21, 27, 19, 23, 21, 23, 35 },
			{ 34, 22, 19, 25, 19, 23, 19, 22, 26, 23, 23, 22, 23, 24, 20, 18, 26, 24, 20, 19, 27, 22, 19, 25, 26, 20, 21, 22, 24, 18, 28, 35 },
			{ 34, 22, 26, 25, 20, 22, 27, 22, 20, 22, 25, 26, 21, 21, 21, 22, 18, 26, 21, 22, 18, 24, 21, 24, 26, 19, 18, 18, 27, 21, 25, 35 },
			{ 34, 18, 19, 21, 22, 26, 24, 20, 23, 23, 26, 23, 21, 22, 20, 20, 22, 26, 21, 18, 18, 22, 20, 18, 20, 24, 25, 26, 18, 23, 19, 35 },
			{ 34, 28, 20, 21, 23, 26, 26, 21, 20, 18, 18, 19, 19, 18, 18, 24, 24, 24, 19, 19, 21, 25, 18, 25, 22, 26, 26, 26, 22, 19, 23, 35 },
			{ 34, 20, 19, 26, 23, 23, 18, 20, 24, 23, 22, 25, 26, 27, 20, 26, 26, 26, 23, 19, 22, 18, 23, 24, 24, 23, 24, 18, 21, 28, 25, 35 },
			{ 34, 23, 20, 28, 25, 26, 19, 25, 23, 23, 22, 26, 25, 28, 24, 21, 22, 18, 28, 26, 22, 24, 25, 28, 25, 21, 28, 19, 26, 22, 20, 35 },
			{ 34, 23, 27, 22, 23, 28, 25, 18, 28, 25, 20, 25, 20, 21, 18, 24, 26, 21, 27, 22, 18, 28, 25, 22, 21, 21, 24, 26, 21, 18, 27, 35 },
			{ 34, 20, 20, 18, 20, 27, 19, 20, 22, 21, 28, 21, 26, 24, 25, 28, 26, 24, 21, 25, 19, 19, 23, 24, 27, 24, 21, 27, 28, 21, 23, 35 },
			{ 32,  2,  4,  2,  3,  1,  4,  3,  2,  1,  3,  4,  2,  1,  3,  3,  2,  3,  4,  1,  3,  2,  4,  2,  3,  2,  4,  2,  4,  2,  3, 33 },
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

		uint64_t computedHash = XXHash64::hash(arr, 2304, 21);
		uint64_t storedHash = 10826533516051580595;

		if (computedHash == storedHash) {
			return arr;
		}
		GenerateTilemapFile("tilemap.bin");

		//	Cheaters map.
		for (int i = 0; i < len; i++)
			arr[i] = 27;

		return arr;
	}
};



