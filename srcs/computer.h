#ifndef computer_h
#define computer_h 1

#include "answer.h"

//------------------------------
// コンピュータの思考用クラス
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
