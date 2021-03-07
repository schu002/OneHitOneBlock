#include <DxLib.h>
#include "panel.h"
#include "util.h"

namespace {

int getKeyState()
{
	char buf[256];
	GetHitKeyStateAll(buf);
	int key = 0;
	if (buf[KEY_INPUT_BACK] || buf[KEY_INPUT_DELETE]) {
		key |= L_KEY_DEL;
	} else if (buf[KEY_INPUT_RETURN] || buf[KEY_INPUT_SPACE]) {
		key |= L_KEY_ENTER;
	} else if (buf[KEY_INPUT_A]) {
		key |= L_KEY_A;
	} else if (buf[KEY_INPUT_NUMPAD0] || buf[KEY_INPUT_0]) {
		key |= L_KEY_0;
	} else if (buf[KEY_INPUT_NUMPAD1] || buf[KEY_INPUT_1]) {
		key |= L_KEY_1;
	} else if (buf[KEY_INPUT_NUMPAD2] || buf[KEY_INPUT_2]) {
		key |= L_KEY_2;
	} else if (buf[KEY_INPUT_NUMPAD3] || buf[KEY_INPUT_3]) {
		key |= L_KEY_3;
	} else if (buf[KEY_INPUT_NUMPAD4] || buf[KEY_INPUT_4]) {
		key |= L_KEY_4;
	} else if (buf[KEY_INPUT_NUMPAD5] || buf[KEY_INPUT_5]) {
		key |= L_KEY_5;
	} else if (buf[KEY_INPUT_NUMPAD6] || buf[KEY_INPUT_6]) {
		key |= L_KEY_6;
	} else if (buf[KEY_INPUT_NUMPAD7] || buf[KEY_INPUT_7]) {
		key |= L_KEY_7;
	} else if (buf[KEY_INPUT_NUMPAD8] || buf[KEY_INPUT_8]) {
		key |= L_KEY_8;
	} else if (buf[KEY_INPUT_NUMPAD9] || buf[KEY_INPUT_9]) {
		key |= L_KEY_9;
	} else if (buf[KEY_INPUT_LEFT]) {
		key |= L_KEY_LEFT;
	} else if (buf[KEY_INPUT_RIGHT]) {
		key |= L_KEY_RIGHT;
	}
	return key;
}

// ボタン枠を描画する
void drawFrame(const Zone &zone, uint color = 0xffffffff, int thick = 1)
{
	DrawLine(zone[0].x+2, zone[0].y, zone[1].x-2, zone[0].y, color, thick);
	DrawLine(zone[0].x+2, zone[1].y, zone[1].x-2, zone[1].y, color, thick);
	DrawLine(zone[0].x, zone[0].y+2, zone[0].x, zone[1].y-2, color, thick);
	DrawLine(zone[1].x, zone[0].y+2, zone[1].x, zone[1].y-2, color, thick);

	DrawLine(zone[0].x, zone[0].y+2, zone[0].x+2, zone[0].y, color, thick);
	DrawLine(zone[0].x, zone[1].y-2, zone[0].x+2, zone[1].y, color, thick);
	DrawLine(zone[1].x, zone[0].y+2, zone[1].x-2, zone[0].y, color, thick);
	DrawLine(zone[1].x, zone[1].y-2, zone[1].x-2, zone[1].y, color, thick);
}

int getKeyNumber(int key)
{
	switch (key) {
	case L_KEY_0: return 0;
	case L_KEY_1: return 1;
	case L_KEY_2: return 2;
	case L_KEY_3: return 3;
	case L_KEY_4: return 4;
	case L_KEY_5: return 5;
	case L_KEY_6: return 6;
	case L_KEY_7: return 7;
	case L_KEY_8: return 8;
	case L_KEY_9: return 9;
	default: return -1;
	}
}

Number getRandomNums()
{
	Number nums;
	for (int i = 0; i < 4; i++) {
		int num = rand() % 10;
		if (i > 0) {
			bool ok = true;
			for (int j = 0; j < i; j++) {
				if (nums[j] == num) { ok = false; break; }
			}
			if (!ok) { // やり直し
				i--;
				continue;
			}
		}
		nums[i] = num;
	}
	return nums;
}

};


NumberPanel::NumberPanel(const Zone &zone)
 : mCurIdx(0), mZone(zone)
{
}

void NumberPanel::Reset()
{
	mCurIdx = 0;
	mNums.clear();
}

bool NumberPanel::OnKeyPressed(int key)
{
	if (key & L_KEY_NUMBER) {
		const int num = getKeyNumber(key);
		return OnBtnClicked((ButtonIdx)num);
	} else if (key & L_KEY_DEL) {
		OnBtnClicked(L_Button_Clear);
	} else if (key & L_KEY_ENTER) {
		OnBtnClicked(L_Button_OK);
	} else if (key & L_KEY_DIR_X) {
		if (key & L_KEY_LEFT) {
			mCurIdx = (mCurIdx > 0)? mCurIdx-1 : 3;
		} else if (key & L_KEY_RIGHT) {
			mCurIdx = (mCurIdx < 3)? mCurIdx+1 : 0;
		}
		Draw();
		ScreenFlip();
		Sleep(100);
	}
	return false;
}

bool NumberPanel::OnBtnClicked(ButtonIdx btn)
{
	DrawBox(160, 50, 500, 80, 0, TRUE);

	Sleep(150);
	const uint red = GetColor(255, 0, 0);
	if (btn >= 0 && btn <= 9) {
		if (mNums[mCurIdx] == btn) return false;
		mNums[mCurIdx] = btn;
		if (mCurIdx < 3) mCurIdx++;
	} else if (btn == L_Button_Clear) {
		Reset();
	} else if (btn == L_Button_Auto) {
		mNums = Util::GetRandomNumber();
	} else if (btn == L_Button_OK) {
		if (mNums.isDuplicate()) {
			SetFontSize(24);
			const uint red = GetColor(255, 0, 0);
			DrawString(180, 50, "同じ数字が使われています", red);
			ScreenFlip();
			return false;
		} else if (!mNums.isValid()) {
			SetFontSize(24);
			DrawString(250, 50, "未入力です", red);
			ScreenFlip();
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}

	Draw();
	ScreenFlip();
	return false;
}

void NumberPanel::OnClicked(int x, int y)
{
	if (!mZone.isOverlap(x, y)) return;

	const int sizeX = getSizeX();
	const int pitchX = sizeX+10;
	const int idx = (x-mZone[0].x) / pitchX;
	if (idx == mCurIdx) return;
	const int mod = (x-mZone[0].x) % pitchX;
	if (mod > sizeX) return;

	mCurIdx = idx;
	Draw();
	ScreenFlip();
}

void NumberPanel::Draw() const
{
	SetFontSize(68);
	const uint white = 0xffffffff;
	DrawBox(mZone[0].x-2, mZone[0].y-2, mZone[1].x+2, mZone[1].y+2, 0, TRUE);
	const int sizeX = getSizeX(), sizeY = getSizeY();
	int x = mZone[0].x, y = mZone[0].y;
	for (int i = 0; i < 4; i++) {
		const uint color = (i == mCurIdx)? GetColor(255, 255, 0) : white;
		const int thick = (i == mCurIdx)? 3 : 2;
		drawFrame(Zone(x, y, x+sizeX, y+sizeY), color, thick);
		if (mNums[i] >= 0) {
			DrawFormatString(x+8, y+10, white, "%d", mNums[i]);
		}
		x += (sizeX+10);
	}
}


NumberButton::NumberButton(int num, int x, int y)
 : mNum(num), mZone(x, y, x+40, y+40)
{
	Draw();
}

void NumberButton::Draw() const
{
	drawFrame(mZone);

	// 数字の描画
	const uint white = 0xffffffff;
	SetFontSize(28);
	DrawFormatString(mZone[0].x+12, mZone[0].y+6, white, "%d", mNum);
}

CtrlButton::CtrlButton(int x, int y, int key)
 : mZone(x, y, x+74, y+40), mKey(key)
{
}

void CtrlButton::Draw() const
{
	drawFrame(mZone);

	const uint white = 0xffffffff;
	SetFontSize(20);
	if (mKey == L_KEY_DEL) {
		DrawString(mZone[0].x+10, mZone[0].y+11, "Clear", white);
	} else if (mKey == L_KEY_A)	{
		DrawString(mZone[0].x+15, mZone[0].y+11, "Auto", white);
	} else {
		DrawString(mZone[0].x+30, mZone[0].y+11, "OK", white);
	}
}


CenterPanel::CenterPanel(const Zone &zone)
 : mZone(zone), 
   mNumPanel(Zone(zone[0].x, zone[0].y, zone[1].x, zone[0].y+80)),
   mClearButton(zone[0].x, zone[0].y+200, L_KEY_DEL),
   mAutoButton(zone[0].x+83, zone[0].y+200, L_KEY_A),
   mOKButton(zone[0].x+166, zone[0].y+200, L_KEY_ENTER)
{
	// 数字ボタンを作成
	int x = mZone[0].x, y = mZone[0].y+100;
	for (int i = 0; i < 10; i++) {
		NumberButton btn(i, x, y);
		mNumBtnList.push_back(btn);
		if (i == 4) {
			x = mZone[0].x;
			y += 50;
		} else {
			x += 50;
		}
	}
}

void CenterPanel::Draw() const
{
	mNumPanel.Draw();
	for (size_t i = 0; i < mNumBtnList.size(); i++) {
		mNumBtnList[i].Draw();
	}
	mClearButton.Draw();
	mAutoButton.Draw();
	mOKButton.Draw();
}

bool CenterPanel::onEventLoop()
{
	bool ret = false;
	const int key = getKeyState();
	if (key) { // キー入力
		ret = mNumPanel.OnKeyPressed(key);
	} else if (GetMouseInput() & MOUSE_INPUT_LEFT) { // マウスクリック
		int x, y;
		GetMousePoint(&x, &y);
		const ButtonIdx btn = getClickNumber(x, y);
		if (btn != L_Button_None) {
			ret = mNumPanel.OnBtnClicked(btn);
		} else {
			mNumPanel.OnClicked(x, y);
		}
	}
	Sleep(50);
	return ret;
}

ButtonIdx CenterPanel::getClickNumber(int x, int y) const
{
	if (x < mZone[0].x || y < mZone[0].y) return L_Button_None;

	const Zone &numBtn0Zone = mNumBtnList[0].GetZone();
	const Zone &numBtn9Zone = mNumBtnList[9].GetZone();
	if (numBtn0Zone[0].y <= y && y <= numBtn9Zone[1].y) {
		const int row = (y <= numBtn0Zone[1].y)? 0 : 1;
		int num = (x - mZone[0].x)/50;
		if (num > 4) return L_Button_None;
		if (row == 1) num += 5;
		if (mNumBtnList[num].IsOverlap(x, y)) return (ButtonIdx)num;
	} else {
		if (mClearButton.IsOverlap(x, y)) return L_Button_Clear;
		if (mAutoButton.IsOverlap(x, y)) return L_Button_Auto;
		if (mOKButton.IsOverlap(x, y)) return L_Button_OK;
	}
	return L_Button_None;
}
