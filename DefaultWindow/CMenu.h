#pragma once
#include "CScene.h"
class CMenu : public CScene
{
public:
	CMenu() {}
	~CMenu() {}

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

