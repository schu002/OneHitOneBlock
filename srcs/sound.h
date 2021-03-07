#ifndef sound_h
#define sound_h 1

#include <DxLib.h>
#include <map>
#include "common.h"

enum SoundIdx {
	L_Sound_None = -1,
	L_Sound_Button,
	L_Sound_Blip,
	L_Sound_Turn,
	L_Sound_Win,
	L_Sound_Lose,
	L_Sound_Draw,

	L_Sound_All,
};

class Sound
{
public:
	static bool New();
	static void Destroy();
	static bool Play(SoundIdx idx);
	static void Stop();

private:
	Sound() : mLastIdx(L_Sound_None) {}
	bool loadFile();

private:
	vector<int> mHandle;
	SoundIdx mLastIdx;	// ç≈å„Ç…èoóÕÇµÇΩâπ
	static Sound *mMyself;
};

#endif
