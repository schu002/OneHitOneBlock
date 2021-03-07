#include "computer.h"
#include "util.h"
#include <windows.h>
#include <algorithm>

Computer::Computer(const Answer &answer)
 : mAnswer(answer)
{
}

// コンピュータの思考メイン関数
Number Computer::Think()
{
	Sleep(1000);

	// とりあえずランダムに４つの数字を返すだけ。
	return Util::GetRandomNumber();
}
