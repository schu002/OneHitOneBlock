#ifndef zone_h
#define zone_h 1

#include "common.h"

// 点クラス
class Point
{
public:
	Point() : x(0), y(0) {}
	Point(int px, int py) : x(px), y(py) {}

public:
	int x, y;
};

// 矩形領域クラス
class Zone
{
public:
	Zone() {}
	Zone(int x1, int y1, int x2, int y2);

	int width() const { return M_ABS(mPnt2.x-mPnt1.x); }
	int height() const { return M_ABS(mPnt2.y-mPnt1.y); }
	void set(int x1, int y1, int x2, int y2);
	bool isOverlap(int x, int y) const;

	const Point & operator [](int idx) const { return (idx == 0)? mPnt1 : mPnt2; }
	Point & operator [](int idx) { return (idx == 0)? mPnt1 : mPnt2; }

private:
	Point mPnt1;
	Point mPnt2;
};

#endif
