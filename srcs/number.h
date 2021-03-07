#ifndef number_h
#define number_h 1

#include "common.h"

//--------------------
// ４桁の数字クラス
//--------------------
class Number
{
public:
	Number();
	Number(const int nums[]);
	Number(const IntVector &nums);
	Number(const Number &nums);

	// 初期化する
	void clear() { mNums[0] = mNums[1] = mNums[2] = mNums[3] = -1; }

	// numが使われているインデックスを取得する。使われていないときは-1を返す。
	int find(int num) const;

	// 桁数を取得する
	int size() const { return 4; }

	// 数字が正しく設定されているか
	bool isValid() const;

	// 同じ数字が使われている
	bool isDuplicate() const;

	// 比較演算子
	bool operator == (const Number &nums) const;
	bool operator != (const Number &nums) const;

	// 代入演算子
	const Number & operator = (const Number &nums);

	// 参照演算子
	int operator [] (int idx) const { return mNums[idx]; }
	int & operator [] (int idx) { return mNums[idx]; }

public:
	// num1とnum2を比較し、ヒットの個数を返す。
	static int hit(const Number &num1, const Number &num2);

	// num1とnum2を比較し、ブロックの個数を返す。
	static int block(const Number &num1, const Number &num2);

	// num1とnum2を比較し、ヒット＋ブロックの個数を返す。
	static int count(const Number &num1, const Number &num2);

private:
	int mNums[4];
};

typedef vector<Number>	NumberList;


#endif
