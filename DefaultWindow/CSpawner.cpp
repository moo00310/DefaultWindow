#include "pch.h"
#include "CSpawner.h"
#include "CSquare.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CSpawner::CSpawner()
	:m_ullLastSpawnTime(0), m_pLeftSquare(nullptr), m_pRightSquare(nullptr)
{
}

CSpawner::~CSpawner()
{
	Release();
}

void CSpawner::Initialize()
{
	m_eRender = RENDER_GAMEOBJECT;
}

int CSpawner::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (!m_pLeftSquare && !m_pRightSquare)
	{
		if (m_ullLastSpawnTime + 5000 < GetTickCount64())
		{
			m_ullLastSpawnTime = GetTickCount64();
			Spawn();
		}
	}

	return OBJ_NOEVENT;
}

void CSpawner::Late_Update()
{
}

void CSpawner::Render(HDC hDC)
{
	TCHAR cBuffer[64]; //저장할 문자열 버퍼

	_stprintf_s(cBuffer, _T("Speed: %.2f"), m_fSpeed);
	TextOut(hDC, int(WINCX * 0.5f), int(WINCY * 0.3f), cBuffer, (int)_tcslen(cBuffer));

}

void CSpawner::Release()
{
}

void CSpawner::Spawn()
{
	m_fSpeed = 4.f;//SPEED_MIN + (rand() % (SPEED_MAX - SPEED_MIN + 1));

	m_pLeftSquare = CAbstractFactory<CSquare>::Create(11 * SIDE, WINCY * 0.5f - SIDE * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pLeftSquare);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(m_pLeftSquare))
	{
		pSquare->Set_RollLeft(true);
		pSquare->Set_Speed(m_fSpeed);
	}

	m_pRightSquare = CAbstractFactory<CSquare>::Create(SIDE, WINCY * 0.5f - SIDE * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pRightSquare);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(m_pRightSquare))
	{
		pSquare->Set_RollLeft(false);
		pSquare->Set_Speed(m_fSpeed);
	}
}
