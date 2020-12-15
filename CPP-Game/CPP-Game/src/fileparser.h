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
	TextFileParser(const std::string filename, void(*func)(std::vector<T*>&) = [](std::vector<T*>&){}) {
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

	//	RETURN READ ITEMS?
	void ReadFile(string filename) {
		string dir = "assets/files/bin/";
		int* arr = new int[LENGTH];
		
		ifstream file;
		file.open(dir + filename, ios::in | ios::binary);
		if (!file) cout << "ERROR\n";
		
		file.read(reinterpret_cast<char*>(arr), LENGTH * sizeof(int));
		file.close();

		cout << "FILE READ!\n";

		delete[] arr;
	}
};



