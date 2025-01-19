#pragma once
#include "CObj.h"

class CBitOrbit_SSH : public CObj
{
public:
	enum PLAYERTYPE { PT_FIRE, PT_ICE, PT_END };

public:
	CBitOrbit_SSH();
	virtual ~CBitOrbit_SSH();

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	D3DXVECTOR3 m_vPoint;
	D3DXVECTOR3 m_vOriginPoint;

	float       m_fScale[PT_END];
	float       m_fMaxScale;
};

