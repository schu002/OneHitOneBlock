#ifndef answer_h
#define answer_h 1

#include "zone.h"
#include "number.h"

//-------------
// �����N���X
//-------------
class Answer
{
public:
	Answer(const Zone &zone, bool compFlg = false);

	// �������擾����
	const NumberList & GetNumberList() const { return mNumList; }

	// ���ʂ��擾����
	void GetResult(const Number &nums, int &h, int &b) const;

	// ������ݒ肷��
	void SetCorrect(const Number &nums) { mCorrect = nums; }

	bool Add(const Number &nums);
	void Clear();
	void Draw(bool finishFlg = false);

private:
	bool isFinish() const;

private:
	Zone mZone;				// �\���̈�
	bool mCompFlg;			// �R���s���[�^���ǂ���
	Number mCorrect;		// �����i����̈Ïؔԍ��j
	NumberList mNumList;	// ����
};

#endif
