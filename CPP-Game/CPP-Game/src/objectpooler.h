#pragma once
#include <iostream>
#include <vector>

#include "datatypes.h"

template<typename T>
class ObjectPool {
public:
	ObjectPool(const int POOL_SIZE) : POOL_SIZE(POOL_SIZE) {};

	template <typename ...Args>
	void Init(Args && ...args) {
		for (int i = 0; i < POOL_SIZE; i++)
			arr.push_back(new T(std::forward<Args>(args)...));
	}

	~ObjectPool() {
		for (T* item : arr) {
			item->Free();
			delete item;
		}
	}

	void Draw() {
		for (T* item : arr)
			item->Draw();
	}

	void Update() {
		for (T* item : arr)
			item->Update();
	}

	template <typename ...Args>
	void Create(Args && ...args) {
		for (T* item : arr) {
			if (!item->Active()) {
				item->Init(std::forward<Args>(args)...);
				return;
			}
		}
	}

	std::vector<T*>& GetObjects(){
		return arr;
	}



protected:
	std::vector<T*> arr;
	const int POOL_SIZE;
};

class ObjectPoolBase {
public:
	virtual void Init() = 0;
	virtual void Free() = 0;
	virtual bool Active() const = 0;
	virtual void Deactivate() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};