#include "pch.h"
#include "CCameraMgr.h"
#include "CObjMgr.h"
#include "CKeyMgr.h"

CCameraMgr* CCameraMgr::m_pInstance = nullptr;

void CCameraMgr::Initailize()
{
	ZeroMemory(&m_Camera, sizeof(POINT));
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
}

void CCameraMgr::Update()
{
	switch (m_eCameraState)
	{
	case CS_ZoomAndFollow:
		m_Camera[C_Zoom_LT] = { (int)m_pPlayer->Get_Info().vPos.x - 100, min(max(0,(int)m_pPlayer->Get_Info().vPos.y - 100),400) };
		m_Camera[C_Zoom_size] = { 200, 200 };
		break;

	case CS_Shake1:
	{
		int shakeIntensity = 20;
		m_Camera[C_Move_LT].x = min(max(0, rand() % (2 * shakeIntensity) - shakeIntensity),600); // -10 ~ 10 Èçµé¸²
		m_Camera[C_Move_LT].y = min(max(0, rand() % (2 * shakeIntensity) - shakeIntensity),600);
		break;
	}
	case CS_Slow_ZoomIN:
		Slow_ZoomIn();
		break;
	case CS_ZoomIN:
		ZoomIn();
		break;

	case CS_Force_ZoomIN:
		Force_ZoomIn();
		break;

	case CS_ZoomOUT:
		if (m_ulTime + 1000 < GetTickCount64())
		{
			// ZoomOut
			m_Camera[C_Move_LT] = { 75 , 50 };
			m_Camera[C_Move_size] = { WINCX - 150 ,WINCY - 100 };
			m_ulTime = GetTickCount64();
		}
		else if (m_ulTime + 500 < GetTickCount64())
		{
			m_Camera[C_Move_LT] = { 0 , 0 };
			m_Camera[C_Move_size] = { WINCX ,WINCY };
			m_Camera[C_Zoom_LT] = { 0 , 0 };
			m_Camera[C_Zoom_size] = { WINCX, WINCY };
		}
		break;

	case CS_END:
		m_Camera[C_Move_LT]	 =	{ 0 , 0 };
		m_Camera[C_Move_size] = { WINCX ,WINCY };
		m_Camera[C_Zoom_LT]	 =	{ 0 , 0 };
		m_Camera[C_Zoom_size] = { WINCX, WINCY };
		break;
	default:
		break;
	}
}

void CCameraMgr::Render(HDC _hDc, HDC _memDC)
{
	if(m_bIsReverce)
		StretchBlt(_hDc, 0, 0, WINCX, WINCY, _memDC, WINCX - 1, 0, -WINCX, WINCY, SRCCOPY);
	else
	{
		GdiTransparentBlt(_hDc,
			m_Camera[C_Move_LT].x,  m_Camera[C_Move_LT].y,
			m_Camera[C_Move_size].x, m_Camera[C_Move_size].y,
			_memDC,
			m_Camera[C_Zoom_LT].x, m_Camera[C_Zoom_LT].y,
			m_Camera[C_Zoom_size].x, m_Camera[C_Zoom_size].y,
			RGB(0, 2, 0));
	}
}

void CCameraMgr::ZoomIn()
{
	if (m_ulTime + 500 < GetTickCount64())
	{
		// ZoomIn
		m_Camera[C_Zoom_LT] = { 35 , 35 };
		m_Camera[C_Zoom_size] = { WINCX - 70, WINCY - 70 };
		m_ulTime = GetTickCount64();
	}
	else if (m_ulTime + 350 < GetTickCount64())
	{
		m_eCameraState = CS_END;
	}

	else if (m_ulTime + 300 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 15 , 15 };
		m_Camera[C_Zoom_size] = { WINCX - 30, WINCY - 30 };
	}
	else if (m_ulTime + 250 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 20 , 20 };
		m_Camera[C_Zoom_size] = { WINCX - 40, WINCY - 40 };
	}
	else if (m_ulTime + 200 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 25 , 25 };
		m_Camera[C_Zoom_size] = { WINCX - 50, WINCY - 50 };
	}
	else if (m_ulTime + 150 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 28 , 28 };
		m_Camera[C_Zoom_size] = { WINCX - 56, WINCY - 56 };
	}
	else if (m_ulTime + 100 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 30 , 30 };
		m_Camera[C_Zoom_size] = { WINCX - 60, WINCY - 60 };
	}
	else if (m_ulTime + 50 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 33 , 33 };
		m_Camera[C_Zoom_size] = { WINCX - 66, WINCY - 66 };
	}
}

void CCameraMgr::Slow_ZoomIn()
{
	if (m_ulTime + 3000 < GetTickCount64())
	{
		m_ulTime = GetTickCount64();
	}
	else if (m_ulTime + 2000 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 75 , 75 };
		m_Camera[C_Zoom_size] = { WINCX - 150, WINCY - 150 };
		m_ulTime = 0;
		m_eCameraState = CS_END;
	}
	else if (m_ulTime + 1800 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 72 , 72 };
		m_Camera[C_Zoom_size] = { WINCX - 144, WINCY - 144 };
	}
	else if (m_ulTime + 1600 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 68 , 68 };
		m_Camera[C_Zoom_size] = { WINCX - 136, WINCY - 136 };
	}
	else if (m_ulTime + 1400 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 65 , 65 };
		m_Camera[C_Zoom_size] = { WINCX - 130, WINCY - 130 };
	}
	else if (m_ulTime + 1200 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 60 , 60 };
		m_Camera[C_Zoom_size] = { WINCX - 120, WINCY - 120 };
	}
	else if (m_ulTime + 1000 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 50 , 50 };
		m_Camera[C_Zoom_size] = { WINCX - 100, WINCY - 100 };
	}
	else if (m_ulTime + 800 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 40 , 40 };
		m_Camera[C_Zoom_size] = { WINCX - 80, WINCY - 80 };
	}
	else if (m_ulTime + 600 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 30 , 30 };
		m_Camera[C_Zoom_size] = { WINCX - 60, WINCY - 60 };
	}
	else if (m_ulTime + 400 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 20 , 20 };
		m_Camera[C_Zoom_size] = { WINCX - 40, WINCY - 40 };
	}
	else if (m_ulTime + 200 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 10 , 10 };
		m_Camera[C_Zoom_size] = { WINCX - 20, WINCY - 20 };
	}
}

void CCameraMgr::Force_ZoomIn()
{
	if (m_ulTime + 500 < GetTickCount64())
	{
		// ZoomIn
		m_Camera[C_Zoom_LT] = { 75 , 75 };
		m_Camera[C_Zoom_size] = { WINCX - 150, WINCY - 150 };
		m_ulTime = GetTickCount64();
	}
	else if (m_ulTime + 300 < GetTickCount64())
	{
		m_eCameraState = CS_END;
	}

	else if (m_ulTime + 250 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 20 , 20 };
		m_Camera[C_Zoom_size] = { WINCX - 40, WINCY - 40 };
	}
	else if (m_ulTime + 200 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 25 , 25 };
		m_Camera[C_Zoom_size] = { WINCX - 50, WINCY - 50 };
	}
	else if (m_ulTime + 100 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 30 , 30 };
		m_Camera[C_Zoom_size] = { WINCX - 60, WINCY - 60 };
	}
	else if (m_ulTime + 50 < GetTickCount64())
	{
		m_Camera[C_Zoom_LT] = { 45 , 45 };
		m_Camera[C_Zoom_size] = { WINCX - 90, WINCY - 90 };
	}
}

