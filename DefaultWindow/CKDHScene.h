#pragma once
#include "CScene.h"
#include "CKDHPlayer.h"
#include "CHexaPad.h"

class CKDHScene : public CScene
{
public:
	CKDHScene();
	virtual ~CKDHScene();

	// CScene��(��) ���� ��ӵ�
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void CreatePattern();
};

