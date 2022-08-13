#pragma once
#include <cmath>

template<typename T>
class Vec2_
{
public:
	Vec2_(T x_in, T y_in)
		:
		x(x_in),
		y(y_in)
	{
	}

	template<typename S>
	Vec2_(const Vec2_<S>& src)
		:
		x((T)src.x),
		y((T)src.y)
	{};

	Vec2_() = default; 

	Vec2_ operator+(const Vec2_& rhs) const
	{
		return Vec2_(x + rhs.x, y + rhs.y);
	}

	Vec2_& operator+=(const Vec2_& rhs)
	{
		return *this = *this + rhs;
	}

	bool operator==(const Vec2_& rhs)const {
		return x == rhs.x && y == rhs.y; 
	}

	bool operator!= (const Vec2_& rhs) const {
		return !(*this == rhs); 
	}

	Vec2_ operator*(T rhs) const
	{
		return Vec2_(x * rhs, y * rhs);
	}

	Vec2_ operator*(Vec2_ rhs) const
	{
		return Vec2_(x * rhs.x, y * rhs.y);
	}

	template<typename S>
	Vec2_ operator/(S rhs) const
	{
		return Vec2_((T) (x / rhs), (T) (y / rhs));
	}
	
	template<typename S>
	Vec2_ operator/= (S rhs) {
		return *this = *this / rhs;
	}


	Vec2_& operator*=(T rhs)
	{
		return *this = *this * rhs;
	}

	Vec2_ operator-(const Vec2_& rhs) const
	{
		return Vec2_(x - rhs.x, y - rhs.y);
	}

	Vec2_ operator- ()const {
		return Vec2_(-x, -y);
	}

	Vec2_& operator-=(const Vec2_& rhs)
	{
		return *this = *this - rhs;
	}

	T GetLength() const
	{
		return (T)std::sqrt(GetLengthSq());
	}

	T GetLengthSq() const
	{
		return x * x + y * y;
	}

	Vec2_& Normalize()
	{
		return *this = GetNormalized();
	}

	Vec2_ GetNormalized() const
	{
		const T len = GetLength();
		if (len != (T)0)
		{
			return *this * ((T)1 / len);
		}
		return *this;
	}

	void SetMagnitude(float mag) {

		T len = GetLength(); 
		if (len > 0) {
			*this *= (mag / GetLength());
		}
	}

	Vec2_ GetAbsolute() {
		return { std::abs(x), std::abs(y) };
	}

	T GetLengthToSq(const Vec2_& base)const {
		return (base - *this).GetLengthSq();
	}

	T GetLengthTo(const Vec2_& base)const {
		return (T) std::sqrt(GetLengthToSq(base));
	}

	Vec2_ GetNormalTo(const Vec2_& target)const {
		return (target - *this).Normalize();
	}

	// Is the point on the line between the two parameters
	bool IsLinearlyContainedBy(Vec2_& p1, Vec2_& p2)const {

		if (p1.x > p2.x)
			std::swap(p1, p2); 

		// x within bounds
		if (x >= p1.x && x <= p2.x) {

			const float slope = float(p2.y - p1. y) / float(p2.x - p1.x);
			const float intcpt = p2.y - slope * float(p2.x);

			// check to see so the given points are not on a vertical line (no good soloution)
			if (p1.x != p2.x) {

				if (std::abs(float(y) - slope * float(x) - intcpt) < 0.1f)
					return true;
				else
					return false;
			}
			else {
				if (p1.y > p2.y)
					std::swap(p1, p2);

				// Handles the vertical case 
				if (y >= p1.y && y <= p2.y)
					return true;
			}
		}
		return false;
	}

	bool IsWithinBounds(const Vec2_& lower, const Vec2_& upper)const {
		return (x > lower.x && x < upper.x && y > lower.y && y < upper.y);
	}
	
	void Clamp(const Vec2_& lower, const Vec2_& upper) {
		
		if (x > upper.x) {
			x = upper.x; 
		}
		else if (x < lower.x) {
			x = lower.x; 
		}

		if (y > upper.y) {
			y = upper.y;
		}
		else if (y < lower.y) {
			y = lower.y;
		}
	}

	Vec2_ FindMiddleTo(const Vec2_& p)const {
		return Vec2_((T)round(float(x + p.x) / 2), (T)round(float(y + p.y) / 2));
	}

	Vec2_& Rotate(const T angle) {
		const T cosTheta = cos(angle); 
		const T sinTheta = sin(angle);

		const T new_x = x * cosTheta - y * sinTheta; 
		y = x * sinTheta + y * cosTheta; 
		x = new_x; 
		return *this; 
	}

	Vec2_ GetRotated(const T angle) {
		return Vec2_(*this).Rotate(angle);
	}

	Vec2_ Get_Perpendicular_Dir(const Vec2_& p)const {

		Vec2_ line_dir = (*this - p).Normalize();
		return Vec2_(line_dir.y, -line_dir.x);

	}

	Vec2_ Get_Perpendicular_Dir()const {
		return Vec2_(y, -x);
	}

	static T Dot(Vec2_& p1, Vec2_& p2) {
		return (p1.x * p2.x + p1.y * p2.y);
	}

	float FindAngleTo_Rad(const Vec2_& p) const{
		// Angle in radians
		return (std::atan(float(p.y - y) / float(p.x - x)));
	}
	
	float FindAngleTo(const Vec2_& p) const {
		// Angle in Degrees
		return  (180.0f / 3.14159265f) * FindAngleTo_Rad(p);
	}

	Vec2_ LimitMagnitude(T min, T max) {
		T len = GetLengthSq(); 
		if (len < min * min)
			SetMagnitude(min);
		else if (len > max * max)
			SetMagnitude(max);
		return *this;
	}

	Vec2_ Limit(T max) {
		return Limit(0, max);
	}

public:
	T x;
	T y;
};

typedef Vec2_<float> Vec2; 
typedef Vec2_<int> Vei2; 