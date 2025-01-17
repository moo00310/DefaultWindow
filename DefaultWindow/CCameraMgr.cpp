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
		int shakeIntensity = 30;
		m_Camera[C_Move_LT].x = min(max(0, rand() % (2 * shakeIntensity) - shakeIntensity),600); // -10 ~ 10 Èçµé¸²
		m_Camera[C_Move_LT].y = min(max(0, rand() % (2 * shakeIntensity) - shakeIntensity),600);
		break;
	}
	case CS_Shake2:
		m_Camera[C_Move_LT] = { +100 , 0 };
		m_Camera[C_Move_size] = { WINCX-200 ,WINCY };
		m_Camera[C_Zoom_LT] = { 0 , 0 };
		m_Camera[C_Zoom_size] = { WINCX, WINCY };
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

