#pragma once
#include "CObj.h"

class CBlock_SSH : public CObj
{
public:
	CBlock_SSH();
	virtual ~CBlock_SSH();

public:
	bool  Get_bSlow() { return m_bSlow; }
	void  Set_bSlow(bool _bSlow) { m_bSlow = _bSlow; }

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	D3DXVECTOR3 m_vPoint[4];
	D3DXVECTOR3 m_vOriginPoint[4];

	bool   m_bSlow;
};

