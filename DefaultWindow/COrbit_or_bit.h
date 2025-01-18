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
	void CameraMovement(int _count);
	void CheckBpm();

private:
	CObj* m_pPlayer;
	CObj* m_pOrbit;

	FMOD::Studio::EventInstance* m_BGM;
	int m_iTimeLine;

	chrono::system_clock::time_point m_tBeatStart; // 다음 박자 (마이크로초)와 비교할 직전 타임 스탬프
	chrono::microseconds m_llTimeChecker;
	bool        m_bRightTimeBeat;
	chrono::system_clock::time_point m_tTimerRightTime; 

	int m_iBeatCount;

};

