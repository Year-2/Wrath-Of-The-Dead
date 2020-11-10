#pragma once
#include <iostream>
#include <vector>

#include "datatypes.h"

template<typename T>
class ObjectPool {
public:
	ObjectPool(SDL_Renderer* renderer, SDL_Texture* texture, const int POOL_SIZE) {
		for (int i = 0; i < POOL_SIZE; i++)
			arr.push_back(T(renderer, texture, i));
	}

	//	TODO:
	//template <typename ...Args>
	//ObjectPool(Args && ...args) {
	//	for (int i = 0; i < 10; i++)
	//		arr.push_back(T(std::forward<Args>(args)...);
	//}

	~ObjectPool() {
		for (T& item : arr) {
			item.Free();
		}
	}

	void Draw() {
		for (T& item : arr)
			item.Draw();
	}

	void Update() {
		for (T& item : arr)
			item.Update();
	}

	template <typename ...Args>
	void Create(Args && ...args) {
		for (T& item : arr) {
			if (!item.Active()) {
				item.Init(std::forward<Args>(args)...);
				return;
			}
		}
	}
protected:
	std::vector<T> arr;
};

class ObjectPoolBase {
public:
	virtual void Init() = 0;
	virtual void Free() = 0;
	virtual bool Active() const = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};