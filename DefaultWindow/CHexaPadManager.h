#pragma once
#include "CSequence.h"

class CHexaPadManager
{
public:
    static CHexaPadManager* Get_Instance()
    {
        if (nullptr == m_pInstance)
            m_pInstance = new CHexaPadManager;

        return m_pInstance;
    }
    static void Destroy_Instance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

public:
	/// <summary>
	/// 패턴 추가.
	/// </summary>	
	void AddPattern(CSequence _sequence);

	/// <summary>
	/// 모든 패턴 제거.
	/// </summary>
	void ClearPattern();

	/// <summary>
	/// 패턴 발동.
	/// </summary>
	void OnPattern();

	/// <summary>
	/// 패턴 리스트 컨테이너 반환.
	/// </summary>
	/// <returns></returns>
	list<CSequence> GetPatternList();

	/// <summary>
	/// 현재 진행중인 패턴을 종료하고 다음 패턴으로 강제로 넘어감.
	/// </summary>
	void StopPattern();

private:
	CHexaPadManager();
    ~CHexaPadManager();

private:
    static CHexaPadManager* m_pInstance;

	// 패턴 시퀀스 리스트.
	list<CSequence> m_patternSequence;

	DWORD m_dwTick;
};

