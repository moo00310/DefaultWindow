#pragma once

#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	float			Get_ScrollX() { return m_fScrollX; }
	float			Get_ScrollY() { return m_fScrollY; }

	void			Set_ScrollX(float _fX) { m_fScrollX += _fX; }
	void			Set_ScrollY(float _fY) { m_fScrollY += _fY; }

	void            Set_ScrollXEx(float _fX) { m_fScrollX = _fX; }
	void            Set_ScrollYEx(float _fY) { m_fScrollY = _fY; }

	void			Scroll_Lock();
	void			Init_Scroll(float _x, float _y) { m_fScrollX = _x; m_fScrollY = _y; }

public:
	static CScrollMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CScrollMgr;

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
	static CScrollMgr* m_pInstance;

	float			    m_fScrollX;
	float			    m_fScrollY;
};

