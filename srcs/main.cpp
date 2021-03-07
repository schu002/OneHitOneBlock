#include <DxLib.h>
#include "app.h"

// ��ʃ��[�h�ύX���ɌĂ΂��R�[���o�b�N�֐�
void ChangeCallback(void *Data)
{
	App::OnWindowModeChanged();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ő剻�{�^����L���ɂ���
	SetUseASyncChangeWindowModeFunction(TRUE, ChangeCallback, NULL);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;

	// �`����ʂ𗠂ɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	SetMouseDispFlag(TRUE);

	// �f�[�^�ǂݍ��݂Ȃ�
	if (!App::New()) return -1;

	// ���C�����[�v
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		if (ProcessMessage() == -1) break;
		if (!App::OnEventLoop()) break;
	}

	App::Destroy();
	DxLib_End();
	return 0;
}
