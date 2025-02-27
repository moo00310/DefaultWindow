#pragma once
#include "CPlayer_SSH.h"

class CPlayer_SSH_Fire : public CPlayer_SSH
{
public:
	CPlayer_SSH_Fire();
	~CPlayer_SSH_Fire();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Key_Input() override;
};

