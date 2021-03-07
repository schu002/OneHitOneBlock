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

	// �E�B���h�E�̍ő剻��Ԃ��ς�����Ƃ��ɌĂ΂��֐�
	static void OnWindowModeChanged();

private:
	App();
	~App();
	void init();
	void redraw();
	bool onEventLoop();

private:
	bool mFullMode;		// �t���X�N���[�����[�h���ǂ���
	int mX, mY; // �e�X�g�p

	static App *mMyself;
};

#endif
