#include <ctime>
#include <DxLib.h>
#include "app.h"

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
 : mFullMode(false), mX(250), mY(200)
{
}

App::~App()
{
}

void App::init()
{
	redraw();
}

bool App::onEventLoop()
{
	const int state = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if		(state & PAD_INPUT_LEFT)  mX -= 2;
	else if (state & PAD_INPUT_RIGHT) mX += 2;
	if		(state & PAD_INPUT_UP)	  mY -= 2;
	else if (state & PAD_INPUT_DOWN)  mY += 2;

	redraw();
	return true;
}

void App::redraw()
{
	ClearDrawScreen();

	DrawBox(mX-1, mY-1, 200, 30, 0, TRUE);
	DrawString(mX, mY, "‚Í‚ë[‚í[‚é‚ÇB", 0xffffffff);

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
