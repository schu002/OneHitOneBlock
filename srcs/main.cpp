#include <DxLib.h>
#include "app.h"

// 画面モード変更時に呼ばれるコールバック関数
void ChangeCallback(void *Data)
{
	App::OnWindowModeChanged();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 最大化ボタンを有効にする
	SetUseASyncChangeWindowModeFunction(TRUE, ChangeCallback, NULL);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;

	// 描画先画面を裏にする
	SetDrawScreen(DX_SCREEN_BACK);

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	SetMouseDispFlag(TRUE);

	// データ読み込みなど
	if (!App::New()) return -1;

	// メインループ
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		if (ProcessMessage() == -1) break;
		if (!App::OnEventLoop()) break;
	}

	App::Destroy();
	DxLib_End();
	return 0;
}
