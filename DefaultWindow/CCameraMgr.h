#pragma once
#include "Define.h"
#include "CObj.h"

class CCameraMgr
{
private:
	CCameraMgr() : m_eCameraState(CS_END), m_pPlayer(nullptr), m_bIsReverce(false), m_Camera{}, m_ulTime(0), m_ePreCameraState(CS_END)
	{}
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
	void Initailize();
	void Update();
	void Render(HDC _hDc, HDC _memDC);

public:
	void Set_State(CarmeraState _eState) { m_eCameraState = _eState; }
	void Is_Reverce(bool _reverce) { m_bIsReverce = _reverce; }

private:
	void ZoomIn();
	void Slow_ZoomIn();
	void Force_ZoomIn();

public:
	static CCameraMgr* m_pInstance;
	CarmeraState m_eCameraState;
	CarmeraState m_ePreCameraState;
	CObj* m_pPlayer;
	POINT m_Camera[C_End];

	bool m_bIsReverce;
	ULONG64 m_ulTime;
};


