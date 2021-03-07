#ifndef computer_h
#define computer_h 1

#include "answer.h"

//------------------------------
// �R���s���[�^�̎v�l�p�N���X
//------------------------------
class Computer
{
private:
	// mState�Ŏg�p���郊�e����
	enum State {
		State_Unknown = 0,	// �����������Ă��Ȃ�
		State_NoUse,		// �g���Ă��Ȃ����Ƃ��m��
		State_Block,		// �ꏊ�͕s�������A�g���Ă���
		State_Hit,			// �ꏊ�܂Ŋm��
	};

public:
	Computer(const Answer &answer);
	Number Think();
	void Clear();

private:
	void checkLastNum();
	bool checkTwoNum(const Number &num1, const Number &num2);
	bool checkNoUseNum(const Number &num);
	bool checkAllFound();
	bool isAllFound() const;
	bool isBadNum(const Number &num) const;
	int getUseCount(const Number &num, int *useCnt = NULL, int *noUseCnt = NULL) const;
	Number decideNextNum() const;
	Number decideFinalNum();
	bool setBlock(int n, int idx = -1);
	bool setHit(int n, int idx);
	bool setNoUse(int n);
	void setAnswerNum(const Number &num);

private:
	bool mIsAnswer[10];	// �e��������x�ł��g�p�������ǂ���
	State mState[10];	// �e�����̕��͏�
	Number mResultNum;
	vector<IntVector> mAllCombList; // �ꏊ�����m��̐����̂��ׂĂ̑g�ݍ��킹���X�g
	IntVector mBadNumList[4];		// ���̏ꏊ�ł͂Ȃ������̃��X�g
	const Answer &mAnswer;
};

#endif
