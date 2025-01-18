#include "pch.h"
#include "CHexaPadManager.h"

CHexaPadManager* CHexaPadManager::m_pInstance = nullptr;

void CHexaPadManager::AddPattern(CSequence _sequence)
{
	m_patternSequence.push_back(_sequence);
	m_dwTick = GetTickCount();
}

void CHexaPadManager::ClearPattern()
{
	m_patternSequence.clear();
}

void CHexaPadManager::OnPattern()
{
	// 패턴 발동.	
	for (auto& sequence : m_patternSequence)
	{
		if (sequence.eSequenceState == SEQUENCE_WAIT)
		{
			sequence.eSequenceState = SEQUENCE_PLAY;
			sequence.sequence();
		}

		if (sequence.eSequenceState == SEQUENCE_PLAY)
		{
			if (GetTickCount() > m_dwTick + (1000.f * sequence.fCount))
			{
				// 해당 시퀀스 종료.
				m_dwTick = GetTickCount();
				sequence.eSequenceState = SEQUENCE_END;
			}
			else
			{
				// 시퀀스 진행 중이니 다음 시퀀스 진행 못하게 막아놓음.
				return;
			}
		}
	}

	// 모든 시퀀스가 종료 됐는지 확인.
	int count = 0;
	for (auto& sequence : m_patternSequence)
	{
		if (sequence.eSequenceState == SEQUENCE_END)
		{
			count++;
		}
	}

	// 모든 시퀀스가 종료되면 다시 순회하게 모든 시퀀스를 wait 상태로.
	if (count >= m_patternSequence.size())
	{
		for (auto& sequence : m_patternSequence)
		{
			sequence.eSequenceState = SEQUENCE_WAIT;
		}
	}
}

list<CSequence> CHexaPadManager::GetPatternList()
{
	return m_patternSequence;
}

void CHexaPadManager::StopPattern()
{
	for (auto& sequence : m_patternSequence)
	{
		if (sequence.eSequenceState == SEQUENCE_PLAY)
		{
			sequence.eSequenceState = SEQUENCE_END;
			return;
		}
	}
}

CHexaPadManager::CHexaPadManager()
{
}

CHexaPadManager::~CHexaPadManager()
{
}
