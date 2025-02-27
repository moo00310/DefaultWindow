#pragma once

#include "Define.h" 

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool		Key_Pressing(int _iKey);
	bool		Key_Down(int _iKey);		// �� �� �� ������ ��
	bool		Key_Up(int _iKey);			// �����ٰ� ���� ��
	void		Update();

public:
	bool GetKeyState(int _iKey) { return m_bKeyState[_iKey]; }

public:
	static CKeyMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CKeyMgr;

		return m_pInstance;
	}

	static void	Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CKeyMgr* m_pInstance;
	bool	m_bKeyState[VK_MAX];

};

