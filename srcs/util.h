#ifndef util_h
#define util_h 1

#include "zone.h"
#include "number.h"

//------------------------
// ���[�e�B���e�B�N���X
//------------------------
class Util
{
public:
	// �����_���ȂS���̐������擾����B
	static Number GetRandomNumber();

	// �w��̈�������h��Ԃ��B
	static void DrawFill(const Zone &zone, int sizing = 0);
};

#endif
