#pragma once
#include "CObj.h"
class COrbit : public CObj
{
public:
	COrbit();
	~COrbit();

public:
	void Initialize() override;
	int Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	// CObj을(를) 통해 상속됨
	void Late_Update() override;
};

