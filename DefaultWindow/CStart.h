#pragma once
#include "CScene.h"
class CStart : public CScene
{
public:
	CStart() {}
	~CStart() {}

	// CScene��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

