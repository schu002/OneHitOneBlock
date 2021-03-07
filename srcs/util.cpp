#include <DxLib.h>
#include "util.h"

Number Util::GetRandomNumber()
{
	Number num;
	for (int i = 0; i < 4; i++) {
		int n = rand() % 10;
		if (i > 0) {
			bool ok = true;
			for (int j = 0; j < i; j++) {
				if (num[j] == n) { ok = false; break; }
			}
			if (!ok) { // ‚â‚è’¼‚µ
				i--;
				continue;
			}
		}
		num[i] = n;
	}
	return num;
}

void Util::DrawFill(const Zone &zone, int sizing)
{
	const uint black = 0;
	DrawBox(zone[0].x-sizing, zone[0].y-sizing, zone[1].x+sizing, zone[1].y+sizing, black, true);
}

