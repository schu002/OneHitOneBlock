#ifndef app_h
#define app_h 1

#include "panel.h"
#include "answer.h"
#include "computer.h"

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
	bool mCompTurn;		// コンピュータの思考中かどうか
	int mTurnCnt;		// ターン数
	CenterPanel mPanel;	// 中央パネル
	Answer mPlayer;		// プレーヤーの答え管理
	Answer mComputer;	// コンピュータの答え管理
	Computer mCompThink;	// コンピュータの思考用

	static App *mMyself;
};

#endif
