#include "zone.h"

Zone::Zone(int x1, int y1, int x2, int y2)
 : mPnt1(x1, y1), mPnt2(x2, y2)
{
	// �K���P�_�ڂ��Q�_�ڂ̂ق������W�l���傫���Ȃ�悤�Ɏ���
	if (x1 > x2) {
		mPnt1.x = x2, mPnt2.x = x1;
	}
	if (y1 > y2) {
		mPnt1.y = y2, mPnt2.y = y1;
	}
}

void Zone::set(int x1, int y1, int x2, int y2)
{
	if (x1 < x2) {
		mPnt1.x = x1, mPnt2.x = x2;
	} else {
		mPnt1.x = x2, mPnt2.x = x1;
	}
	if (y1 < y2) {
		mPnt1.y = y1, mPnt2.y = y2;
	} else {
		mPnt1.y = y2, mPnt2.y = y1;
	}
}

bool Zone::isOverlap(int x, int y) const
{
	return (mPnt1.x <= x && mPnt1.y <= y && x <= mPnt2.x && y <= mPnt2.y)? true : false;
}
