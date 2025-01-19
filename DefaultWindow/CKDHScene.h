#pragma once
#include "CScene.h"
#include "CKDHPlayer.h"
#include "CHexaPad.h"

#define ROTATE_SPEED 1.f

extern float g_RevolAngle;
extern bool g_bRotateAngle;

class CKDHScene : public CScene
{
public:
	CKDHScene();
	virtual ~CKDHScene();

	// CScene을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void CreatePattern();
	void AddPad(kDIRECTION _direction);
	float m_fChangeCount;
	DWORD m_dwTick;
};

