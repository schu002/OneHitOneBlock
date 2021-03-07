#include <DxLib.h>
#include "answer.h"
#include "util.h"

namespace {

void drawNumber(const Number &nums, int x, int y, uint color, bool hideFlg = false)
{
	SetFontSize(20);
	for (int i = 0; i < 4; i++) {
		if (hideFlg) {
			DrawString(x, y, "?", color);
		} else {
			DrawFormatString(x, y, color, "%d", nums[i]);
		}
		x += 18;
	}
}

void drawResult(int x, int y, int h, int b)
{
	const uint red = GetColor(255, 0, 0), green = GetColor(0, 255, 100);
	SetFontSize(16);
	DrawFormatString(x, y, (h > 0)? red : green, "%d", h);
	DrawString(x+16, y, "H", green);
	DrawFormatString(x+34, y, (b > 0)? red : green, "%d", b);
	DrawString(x+50, y, "B", green);
}

};

Answer::Answer(const Zone &zone, bool compFlg)
 : mZone(zone), mCompFlg(compFlg)
{
}

// —š—ğ‚É”š‚ğ’Ç‰Á‚·‚é
bool Answer::Add(const Number &nums)
{
	if (!nums.isValid()) return false;

	mNumList.push_back(nums);
	Draw();
	return (mCorrect == nums)? true : false;
}

// ‚·‚×‚ÄƒNƒŠƒA‚·‚é
void Answer::Clear()
{
	mCorrect.clear();
	mNumList.clear();
}

void Answer::GetResult(const Number &nums, int &h, int &b) const
{
	h = Number::hit(mCorrect, nums);
	b = Number::block(mCorrect, nums);
}

void Answer::Draw(bool finishFlg)
{
	SetFontSize(20);
	const uint yellow = GetColor(255, 255, 0), white = 0xffffffff, orange = GetColor(255, 165, 0);
	int x = mZone[0].x, y = mZone[0].y;
	bool hideFlg = (mCompFlg)? false : true;
	if (hideFlg && finishFlg) {
		Util::DrawFill(Zone(x, y, x+100, y+30), 2);
		hideFlg = false;
	}
	drawNumber(mCorrect, x, y, yellow, hideFlg);

	y += 40;
	for (size_t i = 0; i < mNumList.size(); i++) {
		const Number &nums = mNumList[i];
		int h, b;
		GetResult(nums, h, b);
		const uint color = (h == 4)? orange : white;
		drawNumber(nums, x, y, color);
		const int x2 = (mZone[0].x < 300)? x+90 : x-80;
		drawResult(x2, y+2, h, b);
		y += 30;
	}
}
