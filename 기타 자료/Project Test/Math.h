#pragma once
#include <Windows.h>

struct Point
{
	int _x, _y;

	Point(int x, int y) : _x(x), _y(y) {}
	Point(POINT pt) : _x(pt.x), _y(pt.y) {}
	Point(POINTFLOAT ptf) : _x((int)ptf.x), _y((int)ptf.y) {}

	inline POINT pt(void) { return{ _x, _y }; }
	inline POINTFLOAT ptf(void) { return{ (float)_x, (float)_y }; }

	inline Point operator+ (const Point& pt) { return{ _x + pt._x, _y + pt._y }; }
	inline Point operator- (const Point& pt) { return{ _x - pt._x, _y - pt._y }; }
	inline Point operator* (const Point& pt) { return{ _x * pt._x, _y * pt._y }; }
	inline Point operator/ (const Point& pt) { return{ _x / pt._x, _y / pt._y }; }
	inline Point operator+ (const int num) { return{ _x + num, _y + num }; }
	inline Point operator- (const int num) { return{ _x - num, _y - num }; }
	inline Point operator* (const int num) { return{ _x * num, _y * num }; }
	inline Point operator/ (const int num) { return{ _x / num, _y / num }; }
};

struct PointFloat
{
	float _x, _y;

	PointFloat(float x, float y) : _x(x), _y(y) {}
	PointFloat(POINT pt) : _x((float)pt.x), _y((float)pt.y) {}

	inline POINT pt(void) { return{ (int)_x, (int)_y }; }
	inline POINTFLOAT ptf(void) { return{ _x, _y }; }
};

//값을 제한하는 함수
template<typename T>
inline T Clamp(T value, T min, T max)
{
	T temp = (min > value ? min : value);
	return (temp < max ? temp : max);
}