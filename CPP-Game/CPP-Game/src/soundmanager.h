#pragma once
#include <SDL_mixer.h>
#include <iostream>


class SoundManager {
public:
	static Mix_Music* loadMusic(const char* filename);
	static Mix_Chunk* loadSFX(const char* filename);
	static void playMusic(Mix_Music* music);
	static void playSFX(Mix_Chunk* chunk);
};

class SoundError : public std::exception {
public:
	const char* what() const throw() { return "Sound Error"; }
};

