#pragma once
#include "CObj.h"
class CThorn :  public CObj
{
public:
	CThorn();
	virtual ~CThorn();

public:

public:
	void Initialize() override;
	int Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	D3DXVECTOR3 points[3];
	D3DXVECTOR3 transformVertex[3];

	// CObj��(��) ���� ��ӵ�
	void Late_Update() override;
};

