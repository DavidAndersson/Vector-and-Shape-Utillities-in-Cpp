#pragma once
#include "Vec2.h"

class Circle;

template<typename T>
class Rect_
{
public:

	Rect_() = default;

	Rect_(T left_in, T right_in, T top_in, T bottom_in)
		:
		left(left_in),
		right(right_in),
		top(top_in),
		bottom(bottom_in)
	{}

	Rect_(const Vec2_<T>& topLeft, const Vec2_<T>& bottomRight)
		:
		Rect_(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
	{
	}

	Rect_(const Vec2_<T>& topLeft, int width, int height)
		:
		Rect_(topLeft, topLeft + Vei2(width, height))
	{}


	bool IsOverlappingWith(const Rect_& other) const
	{
		return right > other.left && left < other.right
			&& bottom > other.top && top < other.bottom;
	}


	bool IsOverlappingWith(const Circle& other) const
	{
		return right > (T)other.GetCenter().x - (T)other.GetRadius() && left < (T)other.GetCenter().x + (T)other.GetRadius()
			&& bottom >(T)other.GetCenter().y - (T)other.GetRadius() && top < (T)other.GetCenter().y + (T)other.GetRadius();
	}


	bool IsContainedBy(const Rect_ & other) const
	{
		return left >= other.left && right <= other.right &&
			top >= other.top && bottom <= other.bottom;
	}

	bool Contains(const Vec2_<T>& point) const
	{
		return point.x >= left && point.x <= right && point.y >= top && point.y <= bottom;
	}

	Rect_ GetExpanded(int offset) const
	{
		return Rect_(left - offset, right + offset, top - offset, bottom + offset);
	}

	Vec2_<T> GetCenter() const
	{
		return Vec2((left + right) / 2, (top + bottom) / 2);
	}

	T GetWidth()const { return right - left; };
	T GetHeight()const { return bottom - top; };

	T GetLeft()const { return left; }
	T GetRight()const { return right; }
	T GetTop()const { return top; }
	T GetBottom()const { return bottom; }

public:
	T left;
	T right;
	T top;
	T bottom;
};

typedef Rect_<int> RectI; 
typedef Rect_<float> Rect; 