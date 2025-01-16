#pragma once
#include "Define.h"
class CCameraMgr
{
private:
	CCameraMgr() {}
	~CCameraMgr() {}

public:
	static CCameraMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CCameraMgr();
		}
		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Update();
	void Render(HDC _hDc, HDC _memDC);

public:
	static CCameraMgr* m_pInstance;
};


