#pragma once
#include "Define.h"

class CSequence
{
public:
	CSequence();

	/// <summary>
	/// 실행 시킬 이벤트.
	/// </summary>
	function<void()> sequence;

	/// <summary>
	/// 이번 시퀀스 진행 시간.
	/// </summary>
	float fCount;

	/// <summary>
	/// 해당 시퀀스 플레이 중이거나, 완료했는가?.
	/// </summary>
	kSEQUENCE eSequenceState;
};

