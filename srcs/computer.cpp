#include "computer.h"
#include "util.h"
#include <windows.h>
#include <algorithm>

Computer::Computer(const Answer &answer)
 : mAnswer(answer)
{
}

// �R���s���[�^�̎v�l���C���֐�
Number Computer::Think()
{
	Sleep(1000);

	// �Ƃ肠���������_���ɂS�̐�����Ԃ������B
	return Util::GetRandomNumber();
}
