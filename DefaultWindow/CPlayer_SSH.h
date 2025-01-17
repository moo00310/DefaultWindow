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

	bool        Get_bChange() { return m_bChange; }
	void        Set_bChange(bool _bChange) { m_bChange = _bChange; }

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

	bool m_bChange;
};

