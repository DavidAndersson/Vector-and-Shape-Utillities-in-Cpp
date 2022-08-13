#pragma once
#include "Vec2.h"

class Rect;

template<typename T>
class Circle_
{
public:
	Circle(Vec2 center, float radius) :
		center(center),
		radius(radius) {};

	bool IsOverlappingWith(const Circle& other)const {
		return (center.GetLengthToSq(other.GetCenter()) <= (GetRadius() * GetRadius() + other.GetRadius() * other.GetRadius()));
	};
	bool IsOverlappingWith(const Rect& other)const {
		return other.IsOverlappingWith(*this);
	};
	bool Contains(const Vec2& point)const {
		return std::abs(GetCenter().GetLengthToSq(point)) <= GetRadius() * GetRadius();
	};


	// Getters
	float GetRadius()const { return radius; }
	Vec2 GetCenter()const { return center; }

private: 

	T radius; 
	Vec2 center;

};

typedef Circle_<float> Cirlce;