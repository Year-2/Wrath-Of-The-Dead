#include "soundManager.h"

using std::cout;
using std::endl;
using std::string;

/// <summary>
///		Try's to load a music file if it fails an exception is thrown.
/// </summary>
/// <param name="filename">
///		Sound filename with extension.
/// </param>
/// <returns>
///		Music.
/// </returns>
Mix_Music* SoundManager::LoadMusic(const char* filename) {
	try {
		const char* dir = "assets/sounds/";
		Mix_Music* result = Mix_LoadMUS(string(string(dir) + string(filename)).c_str());
		if (result == nullptr) throw SoundError();
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << "\n";
		std::cout << "\t" << e.what() << ": " << "\t" << Mix_GetError();
		return nullptr;
	}
}

/// <summary>
///		Plays music. 
/// </summary>
/// <param name="music">
///		Music to be played. 
/// </param>
void SoundManager::PlayMusic(Mix_Music* music) {
	if (Mix_PlayingMusic() == 0) Mix_PlayMusic(music, -1);
}

/// <summary>
///		Try's to load a sound file, if it fails and exception is thrown. 
/// </summary>
/// <param name="filename">
///		Sound filename with extension.
/// </param>
/// <returns>
///		Sound. 
/// </returns>
Mix_Chunk* SoundManager::LoadSFX(const char* filename) {
	try {
		const char* dir = "assets/sounds/";
		Mix_Chunk* result = Mix_LoadWAV(string(string(dir) + string(filename)).c_str());
		if (result == nullptr) throw SoundError();
		return result;
	}
	catch (std::exception& e) {
		std::cout << "An exception was thrown." << "\n";
		std::cout << "\t" << e.what() << ": " << "\t" << Mix_GetError();
		return nullptr;
	}
}

/// <summary>
///		Plays sound.
/// </summary>
/// <param name="chunk">
///		Sound to be played.
/// </param>
void SoundManager::PlaySFX(Mix_Chunk* chunk) {
	Mix_PlayChannel(-1, chunk, 0);
}