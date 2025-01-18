#pragma once
#include "CPlayer.h"
class CPlayer_SSH : public CPlayer
{
public:
	CPlayer_SSH();
	virtual ~CPlayer_SSH();

public:
	D3DXVECTOR3 Get_vPoint() { return m_vPoint; }
	void        Set_vPoint(D3DXVECTOR3 _vPos) { m_vPoint = _vPos; }

	bool        Get_bRev() { return m_bRev; }
	void        Set_bRev(bool _bChange) { m_bRev = _bChange; }

	float       Get_MaxAngle() { return m_fMaxAngle; }
	void        Set_MaxAngle(float _fMaxAngle) { m_fMaxAngle = _fMaxAngle; }

	float       Get_RevSpeed() { return m_fRevSpeed; }
	void        Set_RevSpeed(float _fRevSpeed) { m_fRevSpeed = _fRevSpeed; }

public:
	void Initialize() PURE;
	int  Update() PURE;
	void Late_Update() PURE;
	void Render(HDC hDC) PURE;
	void Release() PURE;
	void Key_Input() PURE;

protected:
	D3DXVECTOR3 m_vPoint;
	D3DXVECTOR3 m_vOriginPoint;

	bool  m_bRev;
	float m_fMaxAngle;
	float m_fRevSpeed;
};

