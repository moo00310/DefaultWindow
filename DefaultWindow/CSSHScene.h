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
	void Create_Block();
	void Adjust_RevSpeed();
	void Rev_Auto();
	void Rev_Play();


private:
	bool  m_bChange;

	float m_fCheckAngle;
	float m_fMaxAngle;

	int   m_iBlockCount;
	int   m_iStartTime;

	list<CObj*>::iterator m_IterBlock;
};

