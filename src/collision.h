#pragma once
#include <SDL.h>
#include "circle.h"

#include <iostream>

//	Circle, Complex collision - https://lazyfoo.net/tutorials/SDL/index.php
class Collision {
public:
	static bool BoxCollision(SDL_Rect& a, SDL_Rect& b) {
		if (
			a.x + a.w >= b.x &&
			b.x + b.w >= a.x &&
			a.y + a.h >= b.y &&
			b.y + b.h >= a.y
			) return true;

		return false;
	}

	static bool CircleCollision(Circle& a, Circle& b) {
		if (DistanceSquared(a, b) < (a.r + b.r) * (a.r + b.r))
			return true;
		return false;
	}

	//	TODO: Check this shit actually works
	static bool ComplexCollision(Circle& a, SDL_Rect& b) {
		int cX, cY;

		if (a.x < b.x)
			cX = b.x;
		else if (a.x > b.x + b.w)
			cX = b.x + b.w;
		else
			cX = a.x;

		if (a.y < b.y)
			cY = b.y;
		else if (a.y > b.y + b.h)
			cY = b.y + b.h;
		else
			cY = a.y;

		Circle one = { a.x, a.y, 0 };
		Circle two = { cX, cY, 0 };

		if (DistanceSquared(one, two) < a.r * a.r)
			return true;

		return false;
	}

	inline static int DistanceSquared(Circle& a, Circle& b) {
		int x = b.x - a.x;
		int y = b.y - a.y;
		return x * x + y * y;
	}
};