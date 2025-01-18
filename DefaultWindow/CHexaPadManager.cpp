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
	// ���� �ߵ�.	
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
				// �ش� ������ ����.
				m_dwTick = GetTickCount();
				sequence.eSequenceState = SEQUENCE_END;
			}
			else
			{
				// ������ ���� ���̴� ���� ������ ���� ���ϰ� ���Ƴ���.
				return;
			}
		}
	}

	// ��� �������� ���� �ƴ��� Ȯ��.
	int count = 0;
	for (auto& sequence : m_patternSequence)
	{
		if (sequence.eSequenceState == SEQUENCE_END)
		{
			count++;
		}
	}

	// ��� �������� ����Ǹ� �ٽ� ��ȸ�ϰ� ��� �������� wait ���·�.
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
