#include "soundManager.h"

using std::cout;
using std::endl;
using std::string;

Mix_Music* SoundManager::LoadMusic(const char* filename) {
	try {
		const char* dir = "assets/sounds/";
		Mix_Music* result = Mix_LoadMUS(string(string(dir) + string(filename)).c_str());
		if (result == nullptr) throw SoundError();
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << std::endl;
		std::cout << "\t" << e.what() << ": " << "\t" << Mix_GetError();
	}
}

void SoundManager::PlayMusic(Mix_Music* music) {
	if (Mix_PlayingMusic() == 0) Mix_PlayMusic(music, -1);
}

Mix_Chunk* SoundManager::LoadSFX(const char* filename) {
	try {
		const char* dir = "assets/sounds/";
		Mix_Chunk* result = Mix_LoadWAV(string(string(dir) + string(filename)).c_str());
		if (result == nullptr) throw SoundError();
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << std::endl;
		std::cout << "\t" << e.what() << ": " << "\t" << Mix_GetError();
	}
}

void SoundManager::PlaySFX(Mix_Chunk* chunk) {
	Mix_PlayChannel(-1, chunk, 0);
}