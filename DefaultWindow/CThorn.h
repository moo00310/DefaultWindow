#pragma once
#include "CObj.h"
class CThorn :  public CObj
{
public:
	CThorn();
	CThorn(Direction _dir);
	virtual ~CThorn();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	float TranceAngle();
	Direction GetDir() { return m_eDir; }

private:
	D3DXVECTOR3 m_vPoints[3];
	D3DXVECTOR3 m_vTransformVertex[3];
	D3DXVECTOR3 m_vMidPoint;

	POINT m_tPoints[3];

	Direction m_eDir;
};

