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

COrbit_or_bit::COrbit_or_bit() : m_pPlayer(nullptr), m_pOrbit(nullptr), m_iHitCount(0), m_BGM(nullptr), m_iBeatCount(0),
m_bRightTimeBeat(false), m_llTimeChecker(0), m_eLevel(L_END)
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

	CCameraMgr::Get_Instance()->Initailize();
	m_eLevel = L1;
}

int COrbit_or_bit::Update()
{
	CObjMgr::Get_Instance()->Update();

	CheckBpm();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
		CObjMgr::Get_Instance()->Dead_Thorn(D_RIght);
		CObjMgr::Get_Instance()->Dead_Thorn(D_LEFT);
		m_eLevel = L1;
		CObjMgr::Get_Instance()->Get_Player()->SetSpeed(4.9f);
		CObjMgr::Get_Instance()->Get_Player()->Set_Angle(300.f);
		m_BGM->setTimelinePosition(17400);
		CSoundMgr::Get_Instance()->Update();
		m_iBeatCount = 59;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	{
	
	}

	return 0;
}

void COrbit_or_bit::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	if (CObjMgr::Get_Instance()->Collision_Check(OBJ_MOUSE, 10, 10))
	{
		//LevelDown(m_eLevel);
		m_iBeatCount;
		m_iHitCount++;
	}
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
	_stprintf_s(szBuffer1, _T("HitCount : %d"), m_iHitCount);
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
	if (m_eLevel == L1)
	{
		if (_count % 4 == 1)
		{
			CObjMgr::Get_Instance()->Dead_Thorn(D_RIght);
			DrawRight(_count / 4);
		}
		if (_count % 4 == 3)
		{
			CObjMgr::Get_Instance()->Dead_Thorn(D_LEFT);
			DrawLeft(_count / 4);
		}
	}
	else if (m_eLevel == L2)
	{
		if (_count % 8 == 2)
		{
			CObjMgr::Get_Instance()->Dead_Thorn(D_RIght);
			DrawRight(_count / 4);
		}
		if (_count % 8 == 6)
		{
			CObjMgr::Get_Instance()->Dead_Thorn(D_LEFT);
			DrawLeft(_count / 4);
		}
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

	// 64 / 4 = 16
	// 64 / 8 = 8
		if (_count == 16)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(340, 100.f, D_RIght)); // 11시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3시 30분 안
		}
		if (_count == 17)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght));
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght));

			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(340, 80.f, D_RIght)); // 11시 밖
		}
		if (_count == 18)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3시 30분 밖
			
		}
		if (_count == 20)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200, 190, D_RIght)); // 10시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 90.f, D_RIght)); // 12시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3시 30분 안
		}

		if (_count == 22)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3시 30분 밖
		}

		if (_count == 24)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200, 190, D_RIght)); // 10시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 90.f, D_RIght)); // 12시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3시 30분 안
		}
		if (_count == 26)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3시 30분 밖
		}
		if (_count == 28)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200, 190, D_RIght)); // 10시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 90.f, D_RIght)); // 12시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3시 30분 안
		}
		if (_count == 30)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12시 밖
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1시 안
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3시 30분 밖
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
	if (_count == 15)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5시30분 밖
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(270.f, 461.f, D_LEFT)); // 7시 안
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(170.f, 280.f, D_LEFT)); //9시 밖
	}
	if (_count == 16)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(290.f, 475.f, D_LEFT)); // 7시 안
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8시 30분 밖
	}
	if (_count == 17)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(290.f, 475.f, D_LEFT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT));
	}
	if (_count == 19)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5시 30분 안
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7시 밖
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8시 30분 안
	}

	if (_count == 21)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5시30분 밖
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(300.f, 483.f, D_LEFT)); // 7시 안
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8시 30분 밖

	}
	if (_count == 23)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5시 30분 안
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7시 밖
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8시 30분 안
	}

	if (_count == 25)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5시30분 밖
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(300.f, 483.f, D_LEFT)); // 7시 안
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8시 30분 밖
	}
	if (_count == 27)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5시 30분 안
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7시 밖
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8시 30분 안
	}
	if (_count == 29)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5시30분 밖
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(300.f, 483.f, D_LEFT)); // 7시 안
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8시 30분 밖
	}
	if (_count == 31)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5시 30분 안
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7시 밖
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8시 30분 안
	}
	

}

void COrbit_or_bit::SetSpeed(int _count)
{
	if (_count == 64)
	{
		CObjMgr::Get_Instance()->Get_Player()->SetSpeed(2.45f);
		m_eLevel = L2;
	}
	
}

void COrbit_or_bit::LevelDown(Level m_eLevel)
{

	CObjMgr::Get_Instance()->Dead_Thorn(D_RIght);
	CObjMgr::Get_Instance()->Dead_Thorn(D_LEFT);
	switch (m_eLevel)
	{
	case L1:
		m_eLevel = L1;
		m_BGM->setTimelinePosition(0);
		CObjMgr::Get_Instance()->Get_Player()->SetSpeed(4.9f);
		CObjMgr::Get_Instance()->Get_Player()->Set_Angle(-120.f);
		m_iBeatCount = 0;
		break;
	case L2:
		m_eLevel = L1;
		m_BGM->setTimelinePosition(17400);
		CObjMgr::Get_Instance()->Get_Player()->SetSpeed(4.9f);
		CObjMgr::Get_Instance()->Get_Player()->Set_Angle(300.f);
		m_iBeatCount = 59;
		break;
	case L3:
		break;
	case L4:
		break;
	case L_END:
		break;
	default:
		break;
	}

	CSoundMgr::Get_Instance()->Update();
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
	else if (_count < 128)
	{
		if (_count % 4 == 0)
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

