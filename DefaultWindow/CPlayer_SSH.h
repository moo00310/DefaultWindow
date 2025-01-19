#pragma once
#include "CPlayer.h"

#include "CBitOrbit_SSH.h"

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

	bool        Get_bStart() { return m_bStart; }
	void        Set_bStart(bool _bStart) { m_bStart = _bStart; }

	bool        Get_bEnd() { return m_bEnd; }
	void        Set_bEnd(bool _bEnd) { m_bEnd = _bEnd; }

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
	bool  m_bStart;
	bool  m_bEnd;

	int   m_iRevCount;
	float m_fMaxAngle;
	float m_fRevSpeed;

	CObj* m_pBitOrbit;
};

