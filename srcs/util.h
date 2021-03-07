#ifndef util_h
#define util_h 1

#include "zone.h"
#include "number.h"

//------------------------
// ユーティリティクラス
//------------------------
class Util
{
public:
	// ランダムな４桁の数字を取得する。
	static Number GetRandomNumber();

	// 指定領域を黒く塗りつぶす。
	static void DrawFill(const Zone &zone, int sizing = 0);
};

#endif
