#ifndef computer_h
#define computer_h 1

#include "answer.h"

//------------------------------
// �R���s���[�^�̎v�l�p�N���X
//------------------------------
class Computer
{
public:
	Computer(const Answer &answer);
	Number Think();
	void Clear();

private:
	const Answer &mAnswer;
};

#endif
