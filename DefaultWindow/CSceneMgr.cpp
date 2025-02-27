#include "pch.h"
#include "CSceneMgr.h"

#include "COrbit_or_bit.h"
#include "CRhythmWorld.h"
#include "CSSHScene.h"
#include "CKDHScene.h"
#include "CMenu.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_pScene(nullptr), 
m_eCurScene(SC_MOO), m_ePreScene(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Set_Scene(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case SC_START:
			m_pScene = new CStart;
			break;

		case SC_MOO:
			m_pScene = new COrbit_or_bit;
			break;
        
		case SC_HERO:
			m_pScene = new CRhythmWorld;
			break;

		case SC_SSH:
			m_pScene = new CSSHScene;
			break;

		case SC_KDH:
			m_pScene = new CKDHScene();
			break;

		case SC_MENU:
			m_pScene = new CMenu;
			break;
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

int CSceneMgr::Update()
{
	m_pScene->Update();

	return 0;
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	Safe_Delete(m_pScene);
}
