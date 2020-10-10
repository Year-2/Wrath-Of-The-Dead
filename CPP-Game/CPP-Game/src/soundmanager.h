#pragma once
#include <SDL_mixer.h>
#include <iostream>

class SoundManager {
public:
	static Mix_Music* LoadMusic(const char* filename);
	static Mix_Chunk* LoadSFX(const char* filename);
	static void PlayMusic(Mix_Music* music);
	static void PlaySFX(Mix_Chunk* chunk);
};

class SoundError : public std::exception {
public:
	const char* what() const throw() { return "Sound Error"; }
};

