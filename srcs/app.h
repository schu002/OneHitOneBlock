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
	bool mCompTurn;		// �R���s���[�^�̎v�l�����ǂ���
	int mTurnCnt;		// �^�[����
	CenterPanel mPanel;	// �����p�l��
	Answer mPlayer;		// �v���[���[�̓����Ǘ�
	Answer mComputer;	// �R���s���[�^�̓����Ǘ�
	Computer mCompThink;	// �R���s���[�^�̎v�l�p

	static App *mMyself;
};

#endif
