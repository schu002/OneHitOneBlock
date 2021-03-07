#ifndef computer_h
#define computer_h 1

#include "answer.h"

//------------------------------
// コンピュータの思考用クラス
//------------------------------
class Computer
{
private:
	// mStateで使用するリテラル
	enum State {
		State_Unknown = 0,	// 何も判明していない
		State_NoUse,		// 使われていないことが確定
		State_Block,		// 場所は不明だが、使われている
		State_Hit,			// 場所まで確定
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
	bool mIsAnswer[10];	// 各数字を一度でも使用したかどうか
	State mState[10];	// 各数字の分析状況
	Number mResultNum;
	vector<IntVector> mAllCombList; // 場所が未確定の数字のすべての組み合わせリスト
	IntVector mBadNumList[4];		// その場所ではない数字のリスト
	const Answer &mAnswer;
};

#endif
