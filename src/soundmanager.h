#pragma once
#include <SDL_mixer.h>
#include <SDL.h>
#include <iostream>

class SoundManager {
public:
	static Mix_Music* LoadMusic(const char* filename);
	static Mix_Chunk* LoadSFX(const char* filename);
	static void PlayMusic(Mix_Music* music);
	static void PlaySFX(Mix_Chunk* chunk);

	static inline std::string ProjectDirectory() {
		std::string projectDir = SDL_GetBasePath();
		std::string projectName = "Wrath-Of-The-Dead";
		auto deleteExcess = projectDir.find(projectName, 0) + projectName.size();
		projectDir.erase(begin(projectDir) + deleteExcess, end(projectDir));
		return projectDir;
	}
};

class SoundError : public std::exception {
public:
	const char* what() const throw() { return "Sound Error"; }
};

