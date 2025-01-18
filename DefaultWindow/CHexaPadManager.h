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
	/// ���� �߰�.
	/// </summary>	
	void AddPattern(CSequence _sequence);

	/// <summary>
	/// ��� ���� ����.
	/// </summary>
	void ClearPattern();

	/// <summary>
	/// ���� �ߵ�.
	/// </summary>
	void OnPattern();

	/// <summary>
	/// ���� ����Ʈ �����̳� ��ȯ.
	/// </summary>
	/// <returns></returns>
	list<CSequence> GetPatternList();

	/// <summary>
	/// ���� �������� ������ �����ϰ� ���� �������� ������ �Ѿ.
	/// </summary>
	void StopPattern();

private:
	CHexaPadManager();
    ~CHexaPadManager();

private:
    static CHexaPadManager* m_pInstance;

	// ���� ������ ����Ʈ.
	list<CSequence> m_patternSequence;

	DWORD m_dwTick;
};

