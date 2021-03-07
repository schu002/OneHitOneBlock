#include <ctime>
#include <DxLib.h>
#include "app.h"
#include "util.h"

#define MAX_TURN	12	// 最大ターン数

namespace {

// 勝負がついたときの表示
void drawLast(bool ret1, bool ret2)
{
	Util::DrawFill(Zone(170, 390, 470, 460), 2);

	string str;
	if (ret1 && !ret2) {
		str = "あなたの勝ちです";
	} else if (!ret1 && ret2) {
		str = "あなたの負けです";
	} else {
		str = "引き分けです";
	}

	// 文字列を点滅表示する
	SetFontSize(30);
	int width = GetDrawStringWidth(str.c_str(), (int)str.size());
	const Zone zone(320-width/2, 400, 320+width/2, 430);
	int x = zone[0].x, y = zone[0].y, cnt = 0, blink = 0;
	const uint white = 0xffffffff;
	while (ProcessMessage() == 0) {
		if (cnt < 5) {
			if (cnt == 0) {
				++blink;
				DrawString(x, y, str.c_str(), white);
				ScreenFlip();
			}
		} else {
			if (cnt == 5) {
				Util::DrawFill(zone, 3);
				ScreenFlip();
			}
		}
		if (++cnt >= 8) cnt = 0;
		if (blink > 2 && CheckHitKeyAll()) break; // 何かキーが押されるまでループする
		Sleep(120);
	}

	Util::DrawFill(zone, 3);
}

};

App *App::mMyself = NULL;


bool App::New()
{
	if (mMyself) return true;
	mMyself = new App();
	mMyself->init();
	return true;
}

void App::Destroy()
{
	if (mMyself) {
		delete mMyself;
		mMyself = NULL;
	}
}

App::App()
 : mFullMode(false), mCompTurn(false), mTurnCnt(0), mPanel(Zone(200, 100, 440, 380)),
   mPlayer(Zone(20, 80, 120, 450)), mComputer(Zone(560, 80, 620, 450), true),
   mCompThink(mComputer)
{
}

App::~App()
{
}

void App::init()
{
	std::srand((uint)time(NULL));

	redraw();
}

bool App::onEventLoop()
{
	// ４桁の数字が入力されるまで待つ
	if (!mPanel.onEventLoop()) return true;

	const Number &nums = mPanel.GetNumber();
	if (mTurnCnt == 0) {
		// ゲーム開始
		mTurnCnt = 1;
		mComputer.SetCorrect(nums);
		mPanel.Clear();
		Number compNums;
		compNums = Util::GetRandomNumber();
		mPlayer.SetCorrect(compNums);
		redraw();
		return true;
	}

	bool ret1 = mPlayer.Add(nums);
	mPanel.Clear();

	// コンピュータの思考
	mCompTurn = true;
	redraw();
	Number compNums = mCompThink.Think();
	bool ret2 = mComputer.Add(compNums);
	mCompTurn = false;

	if (ret1 || ret2 || mTurnCnt == MAX_TURN) { // 勝負がついた
		mPlayer.Draw(true);
		drawLast(ret1, ret2);
		mTurnCnt = 0; // 次のゲーム
		mPanel.Clear();
		mPlayer.Clear();
		mComputer.Clear();
	} else {
		++mTurnCnt;
	}

	redraw();
	return true;
}

void App::redraw()
{
	ClearDrawScreen();

	mPanel.Draw();

	SetFontSize(24);
	const uint white = 0xffffffff;
	if (mTurnCnt == 0) {
		DrawString(120, 400, "最初に４桁の数字を入力してください", white);
	} else {
		const uint blue = GetColor(0, 255, 255);
		DrawString(20, 20, "あなた", blue);
		DrawString(480, 20, "コンピュータ", blue);
		if (mCompTurn) {
			DrawString(200, 400, "コンピュータの思考中", white);
		} else {
			DrawString(230, 400, "あなたの番です", white);
		}
		mPlayer.Draw();
		mComputer.Draw();
	}
	ScreenFlip();
}

void App::OnWindowModeChanged()
{
	if (mMyself) {
		mMyself->mFullMode = (mMyself->mFullMode)? false : true;
		SetMouseDispFlag(TRUE);
		Redraw();
	}
}
