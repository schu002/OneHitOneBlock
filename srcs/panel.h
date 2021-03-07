#ifndef panel_h
#define panel_h 1

#include "zone.h"
#include "number.h"

// �����{�^��
enum ButtonIdx {
	L_Button_None = -1,
	L_Button_0,
	L_Button_1,
	L_Button_2,
	L_Button_3,
	L_Button_4,
	L_Button_5,
	L_Button_6,
	L_Button_7,
	L_Button_8,
	L_Button_9,
	L_Button_Clear,
	L_Button_Auto,
	L_Button_OK,
};

// �L�[
enum {
	L_KEY_0			= 0x0001,
	L_KEY_1			= 0x0002,
	L_KEY_2			= 0x0004,
	L_KEY_3			= 0x0008,
	L_KEY_4			= 0x0010,
	L_KEY_5			= 0x0020,
	L_KEY_6			= 0x0040,
	L_KEY_7			= 0x0080,
	L_KEY_8			= 0x0100,
	L_KEY_9			= 0x0200,
	L_KEY_LEFT		= 0x0400,
	L_KEY_RIGHT		= 0x0800,
	L_KEY_DEL		= 0x1000,
	L_KEY_ENTER		= 0x2000,
	L_KEY_A			= 0x4000,

	L_KEY_DIR_X		= 0x0c00,
	L_KEY_NUMBER	= 0x03ff,
};

//--------------------
// �����p�l��
//--------------------
class NumberPanel
{
public:
	NumberPanel(const Zone &zone);
	const Number & GetNumber() const { return mNums; }
	void Reset();
	bool OnKeyPressed(int key);
	bool OnBtnClicked(ButtonIdx btn);
	void OnClicked(int x, int y);
	void Draw() const;

private:
	int getSizeX() const { return (mZone.width()-30)/4; }
	int getSizeY() const { return mZone.height(); }

private:
	Number mNums;	// �S���̐���
	int mCurIdx;	// ���݂̃J�[�\���ʒu
	Zone mZone;		// �`��̈�
};

//--------------------
// �����{�^���N���X
//--------------------
class NumberButton
{
public:
	NumberButton(int num, int x, int y);
	int GetNumber() const { return mNum; }
	const Zone & GetZone() const { return mZone; }
	bool IsOverlap(int x, int y) const { return mZone.isOverlap(x, y); }
	void Draw() const;

private:
	int mNum;	// ����
	Zone mZone;	// �`��̈�
};

typedef vector<NumberButton>	NumberButtonList;


//-------------
// ����{�^��
//-------------
class CtrlButton
{
public:
	CtrlButton(int x, int y, int key);
	bool IsOverlap(int x, int y) const { return mZone.isOverlap(x, y); }
	void Draw() const;

private:
	int mKey;
	Zone mZone;	// �`��̈�
};

//--------------
// �����p�l��
//--------------
class CenterPanel
{
public:
	CenterPanel(const Zone &zone);
	const Number & GetNumber() const { return mNumPanel.GetNumber(); }
	bool onEventLoop();
	void Draw() const;
	void Clear() { mNumPanel.Reset(); }

private:
	ButtonIdx getClickNumber(int x, int y) const;

private:
	Zone mZone;						// �`��̈�
	NumberPanel mNumPanel;			// �����p�l��
	NumberButtonList mNumBtnList;	// �����{�^��
	CtrlButton mClearButton;		// Clear�{�^��
	CtrlButton mAutoButton;			// Auto�{�^��
	CtrlButton mOKButton;			// OK�{�^��
};

#endif
