#pragma once

#include "Define.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

	void		ShowFps();

private:
	HDC			m_hDC;

	ULONG64		m_longTime;
	int			m_iFPS;
	TCHAR		m_szFPS[16];


	HDC			m_memDC;
	HBITMAP		m_hBit;
};

