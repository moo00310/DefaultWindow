#pragma once
#include "CScene.h"
#include "CObj.h"

class COrbit_or_bit : public CScene
{
public:
	COrbit_or_bit();
	~COrbit_or_bit();

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	CObj* m_pPlayer;
	CObj* m_pOrbit;

};

