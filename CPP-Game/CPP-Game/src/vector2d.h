#pragma once
#include <iostream>

template <class T>
class Vector2D {
public:
	Vector2D(T x, T y) : x(x), y(y) {};
	Vector2D() {};

	Vector2D<T>& Add(const Vector2D& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Vector2D<T>& Subtract(const Vector2D& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	Vector2D<T>& Multiply(const Vector2D& rhs) {
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	Vector2D<T>& Divide(const Vector2D& rhs) {
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	friend Vector2D& operator+(Vector2D& lhs, const Vector2D& rhs) {
		return lhs.Add(rhs);
	}
	friend Vector2D& operator-(Vector2D& lhs, const Vector2D& rhs) {
		return lhs.Subtract(rhs);
	}
	friend Vector2D& operator*(Vector2D& lhs, const Vector2D& rhs) {
		return lhs.Multiply(rhs);
	}
	friend Vector2D& operator/(Vector2D& lhs, const Vector2D& rhs) {
		return lhs.Divide(rhs);
	}

	Vector2D& operator+=(const Vector2D& val) {
		return this->Add(val);
	}
	Vector2D& operator-=(const Vector2D& val) {
		return this->Subtract(val);
	}
	Vector2D& operator*=(const Vector2D& val) {
		return this->Multiply(val);
	}
	Vector2D& operator/=(const Vector2D& val) {
		return this->Divide(val);
	}

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& val){	
		return out << "(" << val.x << ", " << val.y << ")\n";
	}

	T x, y;
};