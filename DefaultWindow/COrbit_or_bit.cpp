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
#include "CSceneMgr.h"

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

	if (CKeyMgr::Get_Instance()->Key_Down(VK_BACK))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_MENU);
	}

	return 0;
}

void COrbit_or_bit::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	if (CObjMgr::Get_Instance()->Collision_Check(OBJ_MOUSE, 10, 10))
	{
		LevelDown(m_eLevel);
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
	CSoundMgr::Get_Instance()->Stop_All_Event();
}


// ?Ä Ï±????†ÏÉù?òÏùò BPM???µÌïú Î∞ïÏûê Íµ¨ÌïòÍ∏?Î°úÏßÅ
void COrbit_or_bit::CheckBpm()
{
	using namespace std::chrono;

	// ÏßÅÏ†Ñ Î∞ïÏûê?êÏÑú Î™?Ï¥?ÏßÄ?¨ÎäîÏßÄ Í∞íÏùÑ Î∞õÏùå
	m_llTimeChecker = duration_cast<microseconds>(system_clock::now() - m_tBeatStart); 
	
	if (m_llTimeChecker.count() >= STAGE1BPMSEC) // ?¥Ï†Ñ Î∞ïÏûê?êÏÑú ?§Ïùå Î∞ïÏûêÍ∞Ä ?òÏ????òÎäî (ÎßàÏù¥?¨Î°úÏ¥? ?úÍ∞Ñ ÎßåÌÅº ÏßÄ?¨ÏúºÎ©?
	{
		if (m_bRightTimeBeat == false) // ?ÑÎûò Íµ¨Î¨∏ 1Î≤àÎßå ?òÌñâ?òÍ≤å ?òÎ†§Í≥?Ï∂îÍ????ÜÏñ¥???†Ï???
		{
			m_tBeatStart += microseconds(STAGE1BPMSEC); // ?¥Ï†Ñ ?Ä?ÑÏä§?¨ÌîÑ??1Î∞?ÏßÄ??ÎßåÌÅº??Ï¥??îÌï¥Ï§?
			m_tTimerRightTime = system_clock::now(); // Î∞ëÏùò ifÎ¨???**
			CameraMovement(++m_iBeatCount);
			SwapThron(m_iBeatCount);
			SetSpeed(m_iBeatCount);
			m_bRightTimeBeat = true; // ÏßÄÍ∏??ïÎ∞ï?ÖÎãà??
		}
	}
	if (duration_cast<milliseconds>(system_clock::now() - m_tTimerRightTime).count() > 80) // 80ÎßàÏù¥?¨Î°úÏ¥àÎßå??true???úÍ∞Ñ ?†Ï? ??
	{
		m_bRightTimeBeat = false; // ?Ä???ïÎ∞ï ?¥Ï†ú Î¨??´Ïäµ?àÎã§~
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
	
#pragma region 1Ï∞?
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

#pragma region L2
		if (_count == 16)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(340, 100.f, D_RIght)); // 11????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3??30Î∂???
		}
		if (_count == 17)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght));
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght));

			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(340, 80.f, D_RIght)); // 11??Î∞?
		}
		if (_count == 18)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3??30Î∂?Î∞?

		}
		if (_count == 20)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200, 190, D_RIght)); // 10??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 90.f, D_RIght)); // 12????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3??30Î∂???
		}

		if (_count == 22)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3??30Î∂?Î∞?
		}

		if (_count == 24)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200, 190, D_RIght)); // 10??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 90.f, D_RIght)); // 12????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3??30Î∂???
		}
		if (_count == 26)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3??30Î∂?Î∞?
		}
		if (_count == 28)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200, 190, D_RIght)); // 10??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 90.f, D_RIght)); // 12????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3??30Î∂???
		}
		if (_count == 30)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3??30Î∂?Î∞?
		}
		if (_count == 32)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200, 190, D_RIght)); // 10??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 90.f, D_RIght)); // 12????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3??30Î∂???
		}
		if (_count == 34)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3??30Î∂?Î∞?
		}
		if (_count == 36)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200, 190, D_RIght)); // 10??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 90.f, D_RIght)); // 12????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3??30Î∂???
		}
		if (_count == 38)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3??30Î∂?Î∞?
		}
		if (_count == 40)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200, 190, D_RIght)); // 10??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 90.f, D_RIght)); // 12????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(560, 133.f, D_RIght)); // 1??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(600, 360.f, D_RIght)); // 3??30Î∂???
		}
		if (_count == 42)
		{
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(221, 191, D_RIght)); // 10????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(396, 72.f, D_RIght)); // 12??Î∞?
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(555, 160.f, D_RIght)); // 1????
			CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(623, 350.f, D_RIght)); // 3??30Î∂?Î∞?
		}



#pragma endregion
}

void COrbit_or_bit::DrawLeft(int _count)
{

#pragma region 1Ï∞?
	if (_count >= 8 && _count <= 13)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::Create(274.f, 493.f, D_LEFT));
	}

#pragma endregion

#pragma region L2
	if (_count == 15)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5??0Î∂?Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(270.f, 461.f, D_LEFT)); // 7????
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(170.f, 280.f, D_LEFT)); //9??Î∞?
	}
	if (_count == 16)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(290.f, 475.f, D_LEFT)); // 7????
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8??30Î∂?Î∞?
	}
	if (_count == 17)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(290.f, 475.f, D_LEFT));
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT));
	}
	if (_count == 19)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5??30Î∂???
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7??Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8??30Î∂???
	}

	if (_count == 21)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5??0Î∂?Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(300.f, 483.f, D_LEFT)); // 7????
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8??30Î∂?Î∞?

	}
	if (_count == 23)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5??30Î∂???
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7??Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8??30Î∂???
	}

	if (_count == 25)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5??0Î∂?Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(300.f, 483.f, D_LEFT)); // 7????
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8??30Î∂?Î∞?
	}
	if (_count == 27)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5??30Î∂???
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7??Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8??30Î∂???
	}
	if (_count == 29)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5??0Î∂?Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(300.f, 483.f, D_LEFT)); // 7????
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8??30Î∂?Î∞?
	}
	if (_count == 31)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5??30Î∂???
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7??Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8??30Î∂???
	}
	if (_count == 33)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5??0Î∂?Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(300.f, 483.f, D_LEFT)); // 7????
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8??30Î∂?Î∞?
	}
	if (_count == 35)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5??30Î∂???
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7??Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8??30Î∂???
	}
	if (_count == 37)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5??0Î∂?Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(300.f, 483.f, D_LEFT)); // 7????
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8??30Î∂?Î∞?
	}
	if (_count == 39)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5??30Î∂???
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7??Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8??30Î∂???
	}
	if (_count == 41)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(495.f, 510.f, D_LEFT)); // 5??0Î∂?Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(300.f, 483.f, D_LEFT)); // 7????
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(180.f, 360.f, D_LEFT)); // 8??30Î∂?Î∞?
	}
	if (_count == 43)
	{
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(475.f, 495.f, D_LEFT)); // 5??30Î∂???
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(310.f, 510.f, D_LEFT)); // 7??Î∞?
		CObjMgr::Get_Instance()->Add_Object(OBJ_MOUSE, CAbstractFactory<CThorn>::CreateThorn(200.f, 360.f, D_LEFT)); // 8??30Î∂???
	}
#pragma endregion

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

