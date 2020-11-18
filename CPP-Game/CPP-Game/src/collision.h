#pragma once
#include <SDL.h>

class Collision {
public:
	static bool boxCollision(SDL_Rect& a, SDL_Rect& b) {
		if (
			a.x + a.w >= b.x &&
			b.x + b.w >= a.x &&
			a.y + a.h >= b.y &&
			b.y + b.h >= a.y
			) return true;

		return false;
	}
};