#include "pch.h"
#include "COrbit_or_bit.h"
#include "CPlayer_moo.h"
#include "COrbit.h"
#include "CSoundMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CThorn.h"
#include "CKeyMgr.h"
#include "CCameraMgr.h"
#include "CScrollMgr.h"

COrbit_or_bit::COrbit_or_bit() : m_pPlayer(nullptr), m_pOrbit(nullptr), m_iTimeLine(0), m_BGM(nullptr), m_iBeatCount(0),
m_bRightTimeBeat(false), m_llTimeChecker(0)
{
}

COrbit_or_bit::~COrbit_or_bit()
{
	Release();
}

void COrbit_or_bit::Initialize()
{
	CSoundMgr::Get_Instance()->Initialize();
	m_BGM = CSoundMgr::Get_Instance()->PlayEvent("event:/TheFatRat - Windfall");
	m_tBeatStart = chrono::system_clock::now();
	CSoundMgr::Get_Instance()->Update();

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_moo>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, CAbstractFactory<COrbit>::Create());


	// 가시
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CThorn>::Create(220.f, 260.f));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CThorn>::Create(180.f, 300.f));
	//CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, CAbstractFactory<CThorn>::Create(120.f, 260.f));

	CCameraMgr::Get_Instance()->Initailize();
}

int COrbit_or_bit::Update()
{
	CObjMgr::Get_Instance()->Update();

	CheckBpm();

	if (CKeyMgr::Get_Instance()->Key_Down('P'))
	{
		CCameraMgr::Get_Instance()->Is_Reverce(true);
	}
	if (CKeyMgr::Get_Instance()->Key_Down('O'))
	{
		CCameraMgr::Get_Instance()->Is_Reverce(false);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
		CCameraMgr::Get_Instance()->Set_State(CS_Force_ZoomIN);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	{
		CCameraMgr::Get_Instance()->Set_State(CS_Force_ZoomIN);
	}

	return 0;
}

void COrbit_or_bit::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	bool isCol = CObjMgr::Get_Instance()->Collision_Check(OBJ_MOUSE, 20, 15);
}

void COrbit_or_bit::Render(HDC hDC)
{
	if (CKeyMgr::Get_Instance()->GetKeyState(VK_RIGHT) ||
		CKeyMgr::Get_Instance()->GetKeyState(VK_UP))
	{
		RECT rect = { 0, 0, WINCX, WINCY };
		HBRUSH hBrush = CreateSolidBrush(RGB(211, 211, 211));
		FillRect(hDC, &rect, hBrush);
		DeleteObject(hBrush);
	}


	TCHAR szBuffer[128];
	_stprintf_s(szBuffer, _T("BeatCount : %d"), m_iBeatCount);
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 450, 50, szBuffer, (int)_tcslen(szBuffer));

	TCHAR szBuffer1[128];
	_stprintf_s(szBuffer1, _T("X : %d \t Y : %d"), (int)Get_Mouse().x, (int)Get_Mouse().y);
	SetTextColor(hDC, RGB(0, 0, 0));
	SetBkMode(hDC, TRANSPARENT);
	TextOut(hDC, 50, 50, szBuffer1, (int)_tcslen(szBuffer1));

	

	CObjMgr::Get_Instance()->Render(hDC);
}

void COrbit_or_bit::Release()
{
	CObjMgr::Get_Instance()->Release();
}


// 대 채 영 선생님의 BPM을 통한 박자 구하기 로직
void COrbit_or_bit::CheckBpm()
{
	using namespace std::chrono;

	// 직전 박자에서 몇 초 지났는지 값을 받음
	m_llTimeChecker = duration_cast<microseconds>(system_clock::now() - m_tBeatStart); 
	
	if (m_llTimeChecker.count() >= STAGE1BPMSEC) // 이전 박자에서 다음 박자가 나와야 하는 (마이크로초) 시간 만큼 지났으면
	{
		if (m_bRightTimeBeat == false) // 아래 구문 1번만 수행되게 하려고 추가함 없어도 될지도
		{
			m_tBeatStart += microseconds(STAGE1BPMSEC); // 이전 타임스탬프에 1박 지난 만큼의 초 더해줌
			m_tTimerRightTime = system_clock::now(); // 밑의 if문 용 **
			CameraMovement(++m_iBeatCount);
			SwapThron(m_iBeatCount);
			SetSpeed(m_iBeatCount);
			m_bRightTimeBeat = true; // 지금 정박입니다~
		}
	}
	if (duration_cast<milliseconds>(system_clock::now() - m_tTimerRightTime).count() > 80) // 80마이크로초만큼 true인 시간 유지 후
	{
		m_bRightTimeBeat = false; // 저희 정박 이제 문 닫습니다~
	}
}


void COrbit_or_bit::SwapThron(int _count)
{
	if (_count % 4 == 1)
	{
		CObjMgr::Get_Instance()->Dead_Thorn(D_RIght);
		DrawRight(_count/4);
	}
	if (_count % 4 == 3)
	{
		CObjMgr::Get_Instance()->Dead_Thorn(D_LEFT);
		DrawLeft(_count/4);
	}
}

void COrbit_or_bit::DrawRight(int _count)
{
	
	
#pragma region 1차
	if (_count >= 1 && _count <= 8)
	{
		if (_count % 2 == 1)
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560.f, 134.f, D_RIght));
		else
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(545.f, 153.f, D_RIght));
	}

	if (_count >= 9 && _count <= 13)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(545.f, 153.f, D_RIght));
	}
#pragma endregion

	if (_count == 16 )
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(340, 100.f, D_RIght));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght));
	}
	if (_count == 17)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(340, 100.f, D_RIght));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght));
	}

	if (_count == 18 || _count == 19)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(340, 100.f, D_RIght));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght));

	}

}

void COrbit_or_bit::DrawLeft(int _count)
{
	
		

#pragma region 1차
	if (_count >= 8 && _count <= 13)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::Create(274.f, 493.f, D_LEFT));
	}

#pragma endregion

	if (_count >= 15 && _count <= 17)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(535, 485.f, D_LEFT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(270.f, 461.f, D_LEFT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(170.f, 280.f, D_LEFT));
	}

}

void COrbit_or_bit::SetSpeed(int _count)
{
	if (_count == 64)
		CObjMgr::Get_Instance()->Get_Player()->SetSpeed(3.f);

}

void COrbit_or_bit::CameraMovement(int _count)
{
	if (_count < 60)
	{
		if (_count % 4 == 0)
			CCameraMgr::Get_Instance()->Set_State(CS_ZoomIN);
	}
	else if (_count < 98)
	{
		if (_count == 60)
			CCameraMgr::Get_Instance()->Set_State(CS_Slow_ZoomIN);
		if (_count == 65)
			CCameraMgr::Get_Instance()->Set_State(CS_END);
	}
	else if (_count < 129)
	{
		if (_count % 4 == 3)
			CCameraMgr::Get_Instance()->Set_State(CS_ZoomIN);
	}
	else if (_count < 178)
	{
		if (_count % 2 == 0)
			CCameraMgr::Get_Instance()->Set_State(CS_Force_ZoomIN);
	}
	else if (_count < 186)
	{
		CCameraMgr::Get_Instance()->Set_State(CS_Force_ZoomIN);
	}
	else if (220)
	{
		CCameraMgr::Get_Instance()->Set_State(CS_END);
	}
	
}

