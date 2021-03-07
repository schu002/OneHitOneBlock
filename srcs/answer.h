#ifndef answer_h
#define answer_h 1

#include "zone.h"
#include "number.h"

//-------------
// 答えクラス
//-------------
class Answer
{
public:
	Answer(const Zone &zone, bool compFlg = false);

	// 履歴を取得する
	const NumberList & GetNumberList() const { return mNumList; }

	// 結果を取得する
	void GetResult(const Number &nums, int &h, int &b) const;

	// 正解を設定する
	void SetCorrect(const Number &nums) { mCorrect = nums; }

	bool Add(const Number &nums);
	void Clear();
	void Draw(bool finishFlg = false);

private:
	bool isFinish() const;

private:
	Zone mZone;				// 表示領域
	bool mCompFlg;			// コンピュータかどうか
	Number mCorrect;		// 正解（相手の暗証番号）
	NumberList mNumList;	// 履歴
};

#endif
