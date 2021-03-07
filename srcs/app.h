#ifndef app_h
#define app_h 1

#include "common.h"

class App
{
public:
	static bool New();
	static void Destroy();

	static void Redraw() { if (mMyself) mMyself->redraw(); }

	static bool OnEventLoop() { return (mMyself)? mMyself->onEventLoop() : false; }
	static bool IsFullScreenMode() { return mMyself->mFullMode; }

	// ウィンドウの最大化状態が変わったときに呼ばれる関数
	static void OnWindowModeChanged();

private:
	App();
	~App();
	void init();
	void redraw();
	bool onEventLoop();

private:
	bool mFullMode;		// フルスクリーンモードかどうか
	int mX, mY; // テスト用

	static App *mMyself;
};

#endif
