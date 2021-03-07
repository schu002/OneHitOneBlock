#ifndef number_h
#define number_h 1

#include "common.h"

//--------------------
// �S���̐����N���X
//--------------------
class Number
{
public:
	Number();
	Number(const int nums[]);
	Number(const IntVector &nums);
	Number(const Number &nums);

	// ����������
	void clear() { mNums[0] = mNums[1] = mNums[2] = mNums[3] = -1; }

	// num���g���Ă���C���f�b�N�X���擾����B�g���Ă��Ȃ��Ƃ���-1��Ԃ��B
	int find(int num) const;

	// �������擾����
	int size() const { return 4; }

	// �������������ݒ肳��Ă��邩
	bool isValid() const;

	// �����������g���Ă���
	bool isDuplicate() const;

	// ��r���Z�q
	bool operator == (const Number &nums) const;
	bool operator != (const Number &nums) const;

	// ������Z�q
	const Number & operator = (const Number &nums);

	// �Q�Ɖ��Z�q
	int operator [] (int idx) const { return mNums[idx]; }
	int & operator [] (int idx) { return mNums[idx]; }

public:
	// num1��num2���r���A�q�b�g�̌���Ԃ��B
	static int hit(const Number &num1, const Number &num2);

	// num1��num2���r���A�u���b�N�̌���Ԃ��B
	static int block(const Number &num1, const Number &num2);

	// num1��num2���r���A�q�b�g�{�u���b�N�̌���Ԃ��B
	static int count(const Number &num1, const Number &num2);

private:
	int mNums[4];
};

typedef vector<Number>	NumberList;


#endif
