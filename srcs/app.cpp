#include <ctime>
#include <DxLib.h>
#include "app.h"
#include "util.h"

#define MAX_TURN	12	// �ő�^�[����

namespace {

// �����������Ƃ��̕\��
void drawLast(bool ret1, bool ret2)
{
	Util::DrawFill(Zone(170, 390, 470, 460), 2);

	string str;
	if (ret1 && !ret2) {
		str = "���Ȃ��̏����ł�";
	} else if (!ret1 && ret2) {
		str = "���Ȃ��̕����ł�";
	} else {
		str = "���������ł�";
	}

	// �������_�ŕ\������
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
		if (blink > 2 && CheckHitKeyAll()) break; // �����L�[���������܂Ń��[�v����
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
	// �S���̐��������͂����܂ő҂�
	if (!mPanel.onEventLoop()) return true;

	const Number &nums = mPanel.GetNumber();
	if (mTurnCnt == 0) {
		// �Q�[���J�n
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

	// �R���s���[�^�̎v�l
	mCompTurn = true;
	redraw();
	Number compNums = mCompThink.Think();
	bool ret2 = mComputer.Add(compNums);
	mCompTurn = false;

	if (ret1 || ret2 || mTurnCnt == MAX_TURN) { // ����������
		mPlayer.Draw(true);
		drawLast(ret1, ret2);
		mTurnCnt = 0; // ���̃Q�[��
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
		DrawString(120, 400, "�ŏ��ɂS���̐�������͂��Ă�������", white);
	} else {
		const uint blue = GetColor(0, 255, 255);
		DrawString(20, 20, "���Ȃ�", blue);
		DrawString(480, 20, "�R���s���[�^", blue);
		if (mCompTurn) {
			DrawString(200, 400, "�R���s���[�^�̎v�l��", white);
		} else {
			DrawString(230, 400, "���Ȃ��̔Ԃł�", white);
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
