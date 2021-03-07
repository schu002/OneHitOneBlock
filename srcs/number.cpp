#include "number.h"

Number::Number()
 : mNums{ -1, -1, -1, -1 }
{
}

Number::Number(const int nums[])
{
	for (int i = 0; i < 4; i++) mNums[i] = nums[i];
}

Number::Number(const IntVector &nums)
{
	for (int i = 0; i < 4; i++) mNums[i] = nums[i];
}

Number::Number(const Number &nums)
{
	for (int i = 0; i < 4; i++) mNums[i] = nums[i];
}

bool Number::isDuplicate() const
{
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < i; j++) {
			if (mNums[j] >= 0 && mNums[j] == mNums[i]) return true; // 同じ数字が使われている
		}
	}
	return false;
}

bool Number::isValid() const
{
	for (int i = 0; i < 4; i++) {
		if (mNums[i] < 0 || mNums[i] > 9) return false; // 値が不正
		if (i > 0) {
			for (int j = 0; j < i; j++) {
				if (mNums[j] == mNums[i]) return false; // 同じ数字が使われている
			}
		}
	}
	return true;
}

int Number::find(int num) const
{
	for (int i = 0; i < 4; i++) {
		if (mNums[i] == num) return i;
	}
	return -1;
}

bool Number::operator == (const Number &nums) const
{
	for (int i = 0; i < 4; i++) {
		if (mNums[i] != nums[i]) return false;
	}
	return true;
}

bool Number::operator != (const Number &nums) const
{
	return (*this == nums)? false : true;
}

const Number & Number::operator = (const Number &nums)
{
	for (int i = 0; i < 4; i++) mNums[i] = nums[i];
	return *this;
}

int Number::hit(const Number &num1, const Number &num2)
{
	int h = 0;
	for (int i = 0; i < num1.size(); i++) {
		if (num1[i] == num2[i]) h++;
	}
	return h;
}

int Number::block(const Number &num1, const Number &num2)
{
	int b = 0;
	for (int i = 0; i < num1.size(); i++) {
		if (num1[i] == num2[i]) continue;
		for (int j = 0; j < num2.size(); j++) {
			if (num1[i] == num2[j]) {
				b++;
				break;
			}
		}
	}
	return b;
}

int Number::count(const Number &num1, const Number &num2)
{
	int c = 0;
	for (int i = 0; i < num1.size(); i++) {
		for (int j = 0; j < num2.size(); j++) {
			if (num1[i] == num2[j]) {
				c++;
				break;
			}
		}
	}
	return c;
}
