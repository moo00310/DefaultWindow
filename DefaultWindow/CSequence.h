#pragma once
#include "Define.h"

class CSequence
{
public:
	CSequence();

	/// <summary>
	/// ���� ��ų �̺�Ʈ.
	/// </summary>
	function<void()> sequence;

	/// <summary>
	/// �̹� ������ ���� �ð�.
	/// </summary>
	float fCount;

	/// <summary>
	/// �ش� ������ �÷��� ���̰ų�, �Ϸ��ߴ°�?.
	/// </summary>
	kSEQUENCE eSequenceState;
};

