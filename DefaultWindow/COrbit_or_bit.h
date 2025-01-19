#pragma once
#include "CScene.h"
#include "CObj.h"

enum Level { L1, L2, L3, L4, L_END };

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
	void SwapThron(int  _count);

	void DrawRight(int _count);
	void DrawLeft(int _count);
	void SetSpeed(int _count);

	void LevelDown(Level m_eLevel);

private:
	CObj* m_pPlayer;
	CObj* m_pOrbit;

	FMOD::Studio::EventInstance* m_BGM;


	chrono::system_clock::time_point m_tBeatStart; // 다음 박자 (마이크로초)와 비교할 직전 타임 스탬프
	chrono::microseconds m_llTimeChecker;
	bool        m_bRightTimeBeat;
	chrono::system_clock::time_point m_tTimerRightTime; 

	int m_iBeatCount;
	int m_iHitCount;

	Level m_eLevel;

	//세이브 포인트
	bool isSave[L_END];
};

