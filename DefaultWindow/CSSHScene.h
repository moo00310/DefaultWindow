#pragma once
#include "CScene.h"

class CObj;

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

private:
	void Key_Input();
	void Offset();

private:
	bool  m_bChange;

	float m_fCheckAngle;
	float m_fMaxAngle;

	int   m_iBlockCount;

	list<CObj*>::iterator m_IterBlock;
};

