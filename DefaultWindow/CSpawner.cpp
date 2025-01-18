#include "pch.h"
#include "CSpawner.h"
#include "CSquare.h"
#include "CAbstractFactory.h"
#include "CObjMgr.h"

CSpawner::CSpawner()
	:m_ullLastSpawnTime(0), m_pRightSpawn(nullptr), m_pLeftSpawn(nullptr), m_ullStartTime(0), m_ullNextSpawnTime(0), m_iSpawnIndex(0)
{
	ZeroMemory(&m_arrSpawnTime, sizeof(m_arrSpawnTime));
	ZeroMemory(&m_arrSpawnInfo, sizeof(m_arrSpawnInfo));
}

CSpawner::~CSpawner()
{
	Release();
}

void CSpawner::Initialize()
{
	Set_SpawnTime();

	m_eRender = RENDER_GAMEOBJECT;

	m_ullStartTime = GetTickCount64();

	m_ullNextSpawnTime = m_arrSpawnInfo[0].ullSpawnTime;
}

int CSpawner::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Check_SpawnTime();

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

	_stprintf_s(cBuffer, _T("Spawn Index: %d"), m_iSpawnIndex);
	TextOut(hDC, int(WINCX * 0.5f), int(WINCY * 0.1f), cBuffer, (int)_tcslen(cBuffer));

}

void CSpawner::Release()
{
}

void CSpawner::Spawn()
{
	//소환
	m_fSpeed = 4.f;//SPEED_MIN + (rand() % (SPEED_MAX - SPEED_MIN + 1));

	m_pLeftSpawn = CAbstractFactory<CSquare>::Create(-(SIDE * 0.5f), WINCY * 0.5f - SIDE * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, m_pLeftSpawn);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(m_pLeftSpawn))
	{
		pSquare->Set_RollLeft(false);
		pSquare->Set_Speed(m_fSpeed);
	}

	m_pRightSpawn = CAbstractFactory<CSquare>::Create(SIDE * 9.5f, WINCY * 0.5f - SIDE * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pRightSpawn);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(m_pRightSpawn))
	{
		pSquare->Set_RollLeft(true);
		pSquare->Set_Speed(m_fSpeed);
	}
}

void CSpawner::Spawn(float _fSpeed)
{
	//소환
	m_fSpeed = _fSpeed;//SPEED_MIN + (rand() % (SPEED_MAX - SPEED_MIN + 1));

	m_pLeftSpawn = CAbstractFactory<CSquare>::Create(-(SIDE * 0.5f), WINCY * 0.5f - SIDE * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_BULLET, m_pLeftSpawn);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(m_pLeftSpawn))
	{
		pSquare->Set_RollLeft(false);
		pSquare->Set_Speed(m_fSpeed);
	}

	m_pRightSpawn = CAbstractFactory<CSquare>::Create(SIDE * 9.5f, WINCY * 0.5f - SIDE * 0.5f);
	CObjMgr::Get_Instance()->Add_Object(OBJ_MONSTER, m_pRightSpawn);
	if (CSquare* pSquare = dynamic_cast<CSquare*>(m_pRightSpawn))
	{
		pSquare->Set_RollLeft(true);
		pSquare->Set_Speed(m_fSpeed);
	}
}

void CSpawner::Check_SpawnTime()
{
	if (m_ullStartTime + m_ullNextSpawnTime < GetTickCount64())
	{
		++m_iSpawnIndex;
		m_ullNextSpawnTime = m_arrSpawnInfo[m_iSpawnIndex].ullSpawnTime;
		Spawn(m_arrSpawnInfo[m_iSpawnIndex].fSpeed);
	}

	//if (m_ullLastSpawnTime + 5000 < GetTickCount64())
	//{
	//	m_ullLastSpawnTime = GetTickCount64();
	//	//Remove_OldSquare();
	//	Spawn();
	//}
}

void CSpawner::Remove_OldSquare()
{
	list<CObj*> LeftList = CObjMgr::Get_Instance()->Get_List()[OBJ_MONSTER];
	list<CObj*> RightList = CObjMgr::Get_Instance()->Get_List()[OBJ_BULLET];

	if (LeftList.size())
	{
		CObj* pLeft = *LeftList.begin();
		if (pLeft)
		{
			pLeft->Set_Dead();
		}
	}
	if (RightList.size())
	{
		CObj* pRight = *RightList.begin();
		if (pRight)
		{
			pRight->Set_Dead();
		}
	}

	//이전 사각형 삭제
	/*if (m_pLeftSpawn)
	{
		m_pLeftSpawn->Set_Dead();
		m_pLeftSpawn = nullptr;
	}
	if (m_pRightSpawn)
	{
		m_pRightSpawn->Set_Dead();
		m_pRightSpawn = nullptr;
	}*/
}

void CSpawner::Set_SpawnTime()
{
	/*for (int i = 0; i < SPAWN_COUNT; ++i)
	{
		if (i == 0)
		{
			m_arrSpawnInfo[i].ullSpawnTime = 5000;
			m_arrSpawnInfo[i].fSpeed = 8.f;
		}
		else
		{
			m_arrSpawnInfo[i].ullSpawnTime = m_arrSpawnInfo[i - 1].ullSpawnTime + 5000;
			m_arrSpawnInfo[i].fSpeed = 4.f;
		}
	}*/

	m_arrSpawnInfo[0].ullSpawnTime = 5000;
	m_arrSpawnInfo[0].fSpeed = 4.f;

	m_arrSpawnInfo[1].ullSpawnTime = 10000;
	m_arrSpawnInfo[1].fSpeed = 4.f;

	m_arrSpawnInfo[2].ullSpawnTime = 15000;
	m_arrSpawnInfo[2].fSpeed = 4.f;

	m_arrSpawnInfo[3].ullSpawnTime = 25000;
	m_arrSpawnInfo[3].fSpeed = 4.f;

	m_arrSpawnInfo[4].ullSpawnTime = 35000;
	m_arrSpawnInfo[4].fSpeed = 4.f;
	
}
