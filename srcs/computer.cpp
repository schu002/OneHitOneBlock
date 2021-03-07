#include "computer.h"
#include "util.h"
#include <windows.h>
#include <algorithm>

namespace {

// num1とnum2で共通しない数をそれぞれ取得する
void getDiffList(const Number &num1, const Number &num2, IntVector &diffList1, IntVector &diffList2)
{
	diffList1.clear();
	diffList2.clear();

	for (int i = 0; i < 4; i++) {
		if (num2.find(num1[i]) < 0) diffList1.push_back(num1[i]);
	}
	for (int i = 0; i < 4; i++) {
		if (num1.find(num2[i]) < 0) diffList2.push_back(num2[i]);
	}
}

// numListにnumと同じ４つの数字を使ったものがあるか調べる
bool IsSameCombination(const Number &num, const NumberList &numList, bool hitFlg = false)
{
	for (size_t i = 0; i < numList.size(); i++) {
		if (hitFlg) {
			if (numList[i] == num) return true;
		} else {
			if (Number::count(num, numList[i]) == 4) return true;
		}
	}
	return false;
}

// listの要素順をランダムに並び替える
void sortListAtRandom(IntVector &list)
{
	const size_t size = list.size();
	if (size < 2) return;

	IntVector newList;
	while (!list.empty()) {
		const int idx = rand() % list.size();
		newList.push_back(list[idx]);
		list.erase(list.begin()+idx);
	}
	list = newList;
}

// listのidx1とidx2の要素を入れ替える
void swapList(IntVector &list, int idx1, int idx2)
{
	int tmp = list[idx1];
	list[idx1] = list[idx2];
	list[idx2] = tmp;
}

// listの要素順のすべての組み合わせを取得する。
void getAllCombinationList(vector<IntVector> &allCombList, const IntVector &list)
{
	allCombList.clear();
	allCombList.push_back(list);
	if (list.size() == 1) return;

	IntVector wklist(list);
	while (next_permutation(wklist.begin(), wklist.end())) {
		allCombList.push_back(wklist);
	}
}

};

Computer::Computer(const Answer &answer)
 : mAnswer(answer)
{
	for (int i = 0; i < 10; i++) {
		mState[i] = State_Unknown;
		mIsAnswer[i] = false;
	}
}

// 初期状態に戻す
void Computer::Clear()
{
	for (int i = 0; i < 10; i++) {
		mState[i] = State_Unknown;
		mIsAnswer[i] = false;
	}
	for (int i = 0; i < 4; i++) {
		mBadNumList[i].clear();
	}
	mResultNum.clear();
	mAllCombList.clear();
}

// コンピュータの思考メイン関数
Number Computer::Think()
{
	Sleep(1000);
	checkLastNum();

	if (isAllFound()) { // ４つの数字がすべて判明したとき
		return decideFinalNum();
	} else {
		Number num = decideNextNum();
		setAnswerNum(num);
		return num;
	}
}

void Computer::setAnswerNum(const Number &num)
{
	for (int i = 0; i < 4; i++) {
		const int n = num[i];
		mIsAnswer[n] = true;
	}
}

// 最後のナンバーを手がかりに推測する
void Computer::checkLastNum()
{
	const NumberList &numList = mAnswer.GetNumberList();
	if (numList.empty()) return;

	const Number &last = numList.back();
	int h, b;
	mAnswer.GetResult(last, h, b);

	if (h + b == 4) {
		for (int n = 0; n < 10; n++) {
			if (mState[n] == State_NoUse || mState[n] == State_Hit) continue;
			const int idx = last.find(n);
			if (idx < 0) {
				mState[n] = State_NoUse;
			} else if (b == 4) {
				setBlock(n, idx);
			} else if (h == 4) {
				mState[n] = State_Hit;
				setHit(n, idx);
			} else {
				mState[n] = State_Block;
			}
		}
		return;
	} else if (h + b == 0) {
		for (int i = 0; i < 4; i++) {
			const int n = last[i];
			if (mState[n] != State_Unknown) continue;
			mState[n] = State_NoUse;
		}
	}

	// 新たな発見がなくなるまで繰り返し行う
	for (;;) {
		Sleep(500);
		bool ret = false;
		if (checkAllFound()) return; // ４つの数字がすべて判明した。

		for (size_t idx = 0; idx < numList.size(); idx++) {
			if (checkNoUseNum(numList[idx])) ret = true;
		}

		// 最後とそれ以外の結果を比較してチェックする
		const Number &last = numList.back();
		for (size_t i = 0; i < numList.size()-1; i++) {
			if (checkTwoNum(last, numList[i])) ret = true;
		}
		if (!ret) break; // 新たな判明なし
	}
}

// ４つの数字がすべて判明したかどうか
bool Computer::isAllFound() const
{
	int cnt = 0;
	for (int n = 0; n < 10; n++) {
		if (mState[n] >= State_Block) {
			if (++cnt >= 4) return true;
		}
	}
	return false;
}

// ４つの数字がすべて判明したかチェックする
bool Computer::checkAllFound()
{
	int useCnt = 0, noUseCnt = 0;
	for (int n = 0; n < 10; n++) {
		if		(mState[n] == State_NoUse) noUseCnt++;
		else if (mState[n] >= State_Block) useCnt++;
	}
	if (useCnt == 4 && noUseCnt == 6) return true;

	if (useCnt == 4 || noUseCnt == 6) {
		for (int n = 0; n < 10; n++) {
			if (mState[n] == State_Unknown) {
				mState[n] = (useCnt == 4)? State_NoUse : State_Block;
			}
		}
	}
	return isAllFound();
}

// 使われていない数による推測
bool Computer::checkNoUseNum(const Number &num)
{
	int useCnt, noUseCnt;
	if (getUseCount(num, &useCnt, &noUseCnt) == 0) return false;

	bool ret = false;
	int h, b;
	mAnswer.GetResult(num, h, b);

	if (useCnt > 0 && useCnt == h+b) {
		for (int idx = 0; idx < 4; idx++) {
			const int n = num[idx];
			if (mState[n] == State_Unknown) {
				mState[n] = State_NoUse;
				ret = true;
			}
		}
	}
	if (noUseCnt > 0 && noUseCnt+h+b == 4) {
		for (int idx = 0; idx < 4; idx++) {
			const int n = num[idx];
			if (mState[n] == State_NoUse || mState[n] == State_Hit) continue; // 既に確定済み
			if (b == 0 && h > 0) {
				setHit(n, idx);
				ret = true;
			} else if (h == 0 && b > 0) {
				if (setBlock(n, idx))
					ret = true;
			}
		}
	}
	return ret;
}

// ２つの数字の結果を比較することによる推測
bool Computer::checkTwoNum(const Number &num1, const Number &num2)
{
	// num1とnum2で共通しない数をそれぞれ取得する
	IntVector diffList1, diffList2;
	getDiffList(num1, num2, diffList1, diffList2);
	if (diffList1.empty() || diffList1.size() == 4) return false;

	const int swapCnt = (int)diffList1.size();
	// num1とnum2の共通の数字はすべて場所も一致してるかどうか
	const bool isFixCommon = (Number::hit(num1, num2) == 4-swapCnt)? true : false;

	int h1, b1, h2, b2;
	mAnswer.GetResult(num1, h1, b1);
	mAnswer.GetResult(num2, h2, b2);

	bool ret = false;
	const int diff = (h1+b1) - (h2+b2);
	const bool sameResult = (h1 == h2 && b1 == b2)? true : false;
	// １つだけ数字を入れ替えて、同じ結果になったとき
	if (isFixCommon && sameResult && swapCnt == 1) {
		const int n1 = diffList1[0], n2 = diffList2[0];
		// 例えば、num1：0123 → 1H0B、num12：0124 → 1H0B のとき、
		// 3と4はどちらも使われていない。
		if (h1 == 1 && b1 == 0) {
			if (setNoUse(n1)) ret = true;
			if (setNoUse(n2)) ret = true;
		}
		// 例えば、num1：0123 → 0H1B、num2：0124 → 0H1B のとき、
		// 3が使われていないならば、4も使われていない。
		else {
			if (mState[n1] == State_NoUse) {
				if (setNoUse(n2)) ret = true;
			} else if (mState[n2] == State_NoUse) {
				if (setNoUse(n1)) ret = true;
			}
		}
	}
	// 例えば、num1：0123 → 0H2B、num2：0124 → 1H1B のとき、
	// 3と4はどちらも使われている。
	else if (isFixCommon && diff == 0 && swapCnt == M_ABS(h1-h2)) {
		const Number &hitNum = (h1 < h2)? num2 : num1;
		const IntVector &hitList = (h1 < h2)? diffList2 : diffList1;
		for (size_t i = 0; i < hitList.size(); i++) {
			const int n = hitList[i]; // nはHit。
			if (mState[n] == State_Unknown || mState[n] == State_Block) {
				const int idx = hitNum.find(n);
				setHit(n, idx);
				ret = true;
			}
		}
		const Number &blockNum = (h1 < h2)? num1 : num2;
		const IntVector &blockList = (h1 < h2)? diffList1 : diffList2;
		for (size_t i = 0; i < blockList.size(); i++) {
			const int n = blockList[i]; // nはBlock。
			if (setBlock(n, blockNum.find(n))) {
				ret = true;
			}
		}
	}
	// 例えば、num1：0123 → 0H1B、num2：0124 → 0H2B のとき、
	// 3は使われていない。4は使われている。
	else if (swapCnt == M_ABS(diff)) {
		const Number &useNum = (diff < 0)? num2 : num1;
		const IntVector &useList = (diff < 0) ? diffList2 : diffList1;
		for (size_t i = 0; i < useList.size(); i++) {
			const int n = useList[i]; // nは使われている。
			int idx = (isFixCommon && swapCnt == M_ABS(h1-h2))? useNum.find(n) : -1;
			if (idx < 0) {
				if (isFixCommon && swapCnt == M_ABS(b1-b2)) idx = useNum.find(n);
				if (setBlock(n, idx)) ret = true;
			} else if (idx >= 0) {
				if (setHit(n, idx)) ret = true;
			}
		}

		const IntVector &noUseList = (diff < 0)? diffList1 : diffList2;
		for (size_t i = 0; i < noUseList.size(); i++) {
			const int n = noUseList[i]; // nは使われていない。
			if (mState[n] == State_Unknown) {
				mState[n] = State_NoUse;
				ret = true;
			}
		}
	}

	return ret;
}

// 使われている数と使われていない数の個数を取得する
int Computer::getUseCount(const Number &num, int *useCnt, int *noUseCnt) const
{
	int wkUseCnt = 0, wkNoUseCnt = 0;
	for (int i = 0; i < 4; i++) {
		const int n = num[i];
		if		(mState[n] == State_NoUse) wkNoUseCnt++;
		else if (mState[n] >= State_Block) wkUseCnt++;
	}
	if (useCnt) *useCnt = wkUseCnt;
	if (noUseCnt) *noUseCnt = wkNoUseCnt;
	return wkUseCnt + wkNoUseCnt;
}

// 次の数字を決める
Number Computer::decideNextNum() const
{
	const NumberList &numList = mAnswer.GetNumberList();
	if (numList.empty()) return Util::GetRandomNumber();

	const Number &last = numList.back();
	int h, b;
	mAnswer.GetResult(last, h, b);

	// まだ判明していない数字のリスト
	IntVector answerList, noanswerList;
	for (int n = 0; n < 10; n++) {
		if (mState[n] != State_Unknown) continue;
		if (!mIsAnswer[n]) noanswerList.push_back(n);
		else			   answerList.push_back(n);
	}
	if (noanswerList.empty() && answerList.empty())
		return Util::GetRandomNumber(); // ありえないはず

	sortListAtRandom(noanswerList);
	sortListAtRandom(answerList);

	IntVector unknownList(noanswerList);
	for (size_t i = 0; i < answerList.size(); i++) {
		unknownList.push_back(answerList[i]);
	}

	// 1個だけ入れ替えても意味がなさそうなときは、総とっかえ
	if (h+b >= 2 && b > 0 && unknownList.size() > 5) {
		for (;;) {
			Number num = Util::GetRandomNumber();
			if (!IsSameCombination(num, numList)) return num;
		}
	}

	// １個だけ数字を入れ替える
	int idx = numList.size() % 4; // 入れ替える位置
	Number num(last);
	for (int tryCnt = 0; tryCnt <= 4; tryCnt++) {
		for (size_t i = 0; i < unknownList.size(); i++) {
			const int n = unknownList[i];
			if (num.find(n) >= 0) continue;
			num[idx] = n;
			// 過去にすべて同じ数字の組み合わせがなければOK
			if (!IsSameCombination(num, numList)) return num;
		}
		idx = (idx == 3)? 0 : idx+1;
	}

	// 上記の組み合わせが見つからなかったときは、unknownListの
	// １つだけを使用したナンバーにする。
	IntVector wkvec;
	wkvec.push_back(unknownList[0]);
	for (int n = 0; n < 10; n++) {
		if (mState[n] != State_NoUse) continue;
		wkvec.push_back(n);
		if (wkvec.size() == 4) break;
	}
	sortListAtRandom(wkvec);
	return Number(wkvec);
}

// ４つの数字がすべて判明後、次の数字を決める
Number Computer::decideFinalNum()
{
	IntVector unknownList;
	for (int n = 0; n < 10; n++) {
		if (mState[n] == State_Block) {
			unknownList.push_back(n); // 場所が未確定
		}
	}
	if (unknownList.empty()) return mResultNum; // 完全に判明した。

	if (mAllCombList.empty()) {
		getAllCombinationList(mAllCombList, unknownList);
	}

	const NumberList &numList = mAnswer.GetNumberList();
	while (!mAllCombList.empty()) {
		Number num(mResultNum);
		const IntVector &combNum = mAllCombList.back();
		int cnt = 0;
		for (int j = 0; j < 4; j++) {
			const int n = num[j];
			if (n >= 0 && mState[n] == State_Hit) continue; // 確定済み
			num[j] =  combNum[cnt++];
		}
		mAllCombList.pop_back();
		if (isBadNum(num)) continue;
		if (IsSameCombination(num, numList, true)) continue;
		return num;
	}
	return mResultNum; // ありえないはず
}

bool Computer::isBadNum(const Number &num) const
{
	for (int i = 0; i < 4; i++) {
		const int n = num[i];
		const IntVector &badList = mBadNumList[i];
		for (size_t j = 0; j < badList.size(); j++) {
			if (badList[j] == n) return true;
		}
	}
	return false;
}

bool Computer::setBlock(int n, int idx)
{
	if (idx >= 0) {
		IntVector &badList = mBadNumList[idx];
		if (find(badList.begin(), badList.end(), n) == badList.end()) {
			badList.push_back(n);
		}
	}
	if (mState[n] != State_Unknown) return false;

	mState[n] = State_Block;
	return true;
}

bool Computer::setHit(int n, int idx)
{
	if (mState[n] == State_Hit) return false;

	mState[n] = State_Hit;
	mResultNum[idx] = n;
	return true;
}

bool Computer::setNoUse(int n)
{
	if (mState[n] != State_Unknown) return false;

	mState[n] = State_NoUse;
	return true;
}
