#include <DxLib.h>
#include <stdio.h>
#include "sound.h"

Sound *Sound::mMyself = NULL;

const char *mp3FileName[] = {
	"sound/button.mp3",
	"sound/blip.mp3",
	"sound/turn.mp3",
	"sound/win.mp3",
	"sound/lose.mp3",
	"sound/draw.mp3",
};

bool Sound::New()
{
	if (!mMyself) {
		mMyself = new Sound();
		if (!mMyself->loadFile()) return false;
	}
	return true;
}

void Sound::Destroy()
{
	if (mMyself) {
		delete mMyself;
		mMyself = NULL;
	}
}

bool Sound::loadFile()
{
	mHandle.resize(L_Sound_All);
	for (int i = 0; i < L_Sound_All; i++) {
		const char *fnm = mp3FileName[i];
		mHandle[i] = LoadSoundMem(fnm);
		if (mHandle[i] == -1) return false;
		ChangeVolumeSoundMem(80, mHandle[i]); // ‰¹—Ê’²®
	}
	return true;
}

bool Sound::Play(SoundIdx idx)
{
	if (!mMyself || idx < 0) return false;
	mMyself->mLastIdx = idx;
	PlaySoundMem(mMyself->mHandle[idx], DX_PLAYTYPE_BACK);
	return true;
}

void Sound::Stop()
{
	if (!mMyself || mMyself->mLastIdx == L_Sound_None) return;

	StopSoundMem(mMyself->mHandle[mMyself->mLastIdx]);
	mMyself->mLastIdx = L_Sound_None;
}
