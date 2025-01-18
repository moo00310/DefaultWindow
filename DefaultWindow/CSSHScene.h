#pragma once
#include "CScene.h"
class CSSHScene : public CScene
{
public:
	CSSHScene();
	virtual ~CSSHScene();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Key_Input();

private:
	bool  m_bChange;

	float m_fCheckAngle;
	float m_fMaxAngle;

	int   m_iBlockCount;
	int   m_iBlockSaveCount;
};

