#include "pch.h"
#include "CSSHScene.h"

#include "CPlayer_SSH_Fire.h"
#include "CPlayer_SSH_Ice.h"
#include "CBlock_SSH.h"

#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CSoundMgr.h"
#include "CAbstractFactory.h"
#include "CScrollMgr.h"
#include "CSceneMgr.h"

CSSHScene::CSSHScene() 
	: m_bChange(false), m_fCheckAngle(0.f), m_fMaxAngle(190.f),
	m_iBlockCount(0), m_iStartTime(0)
{
}

CSSHScene::~CSSHScene()
{
	Release();
}

void CSSHScene::Initialize()
{
	CSoundMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->PlayEvent("event:/A Dance of Fire and Ice 1-X A Dance of Fire and Ice");
	CSoundMgr::Get_Instance()->Update();

	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SSH_Ice>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer_SSH_Fire>::Create());
	// ??ÁππÎ®Æ?èËã°???????•Ïã≤Í∞?öß?????????????
	CObjMgr::Get_Instance()->Get_Player()->Set_Target(CObjMgr::Get_Instance()->Get_LastPlayer());
	// ???∞Ïî≠?????ÁππÎ®Æ?èËã°?????•Ïã≤Í∞?öß?????????????
	CObjMgr::Get_Instance()->Get_LastPlayer()->Set_Target(CObjMgr::Get_Instance()->Get_Player());

	Create_Block();

	m_IterBlock = CObjMgr::Get_Instance()->Get_ObjList()[OBJ_BLOCK].begin();
	m_IterBlock++;

	m_iStartTime = 110;  
	//if (!SSH_FIRE->Get_bStart())
	//	SSH_FIRE->Set_Angle(0.f);
}

int CSSHScene::Update()
{
	if(!SSH_FIRE->Get_bStart() && !SSH_ICE->Get_bStart())
		--m_iStartTime;

	if (0 >= m_iStartTime)
	{
		SSH_FIRE->Set_bStart(true);
		SSH_ICE->Set_bStart(true);
	}

	CObjMgr::Get_Instance()->Update();

	if (m_IterBlock == CObjMgr::Get_Instance()->Get_List()[OBJ_BLOCK].end())
	{
		SSH_FIRE->Set_bEnd(true);
		SSH_ICE->Set_bEnd(true);
		return 0;
	}
		 
	Key_Input();
	Offset();

	Rev_Auto(); // Auto Ê¥πÎ™ÉÍπ??Î®?£û??Ä?™ÊÄ??Í≥? ?¥ÎÖπ?????Í≥∏Îº±Êø°ÏºÇuto ??®ÌÄ???àÎíóÔßû¬Ä ??ÑÎπê??ÔßèÏÇµÎ∏?ØÉÏ¢äÍΩï   ( ???æÎãøÍª???)

	if (CKeyMgr::Get_Instance()->Key_Down(VK_BACK))
	{
		CSceneMgr::Get_Instance()->Set_Scene(SC_MENU);
	}

	return 0; 
}

void CSSHScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Update();
}

void CSSHScene::Render(HDC hDC)
{
	//Ellipse(hDC,
	//	int(SSH_FIRE->Get_Info().vPos.x - 100.f),
	//	int(SSH_FIRE->Get_Info().vPos.y - 100.f),
	//	int(SSH_FIRE->Get_Info().vPos.x + 100.f),
	//	int(SSH_FIRE->Get_Info().vPos.y + 100.f));

	//Ellipse(hDC,
	//	int(SSH_ICE->Get_Info().vPos.x - 100.f),
	//	int(SSH_ICE->Get_Info().vPos.y - 100.f),
	//	int(SSH_ICE->Get_Info().vPos.x + 100.f),
	//	int(SSH_ICE->Get_Info().vPos.y + 100.f));

	CObjMgr::Get_Instance()->Render(hDC);

	TCHAR szCur[64]{};
	swprintf_s(szCur, L"CurAngle : %.2f", m_fCheckAngle);
	TextOut(hDC, 20, 20, szCur, lstrlen(szCur));
}

void CSSHScene::Release()
{
	CObjMgr::Get_Instance()->Release();
	CSoundMgr::Get_Instance()->Stop_All_Event();
}

void CSSHScene::Key_Input()
{
	if (m_IterBlock == CObjMgr::Get_Instance()->Get_List()[OBJ_BLOCK].end())
		return;

	Rev_Play();
}

void CSSHScene::Offset()
{
	if (m_IterBlock == CObjMgr::Get_Instance()->Get_List()[OBJ_BLOCK].end())
		return ;

	int		iOffSetX = 400;
	int     iOffSetY = 300;

	int		iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int     iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetX - 50 > (*m_IterBlock)->Get_Info().vPos.x + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(2.f);

	if (iOffSetX + 50 < (*m_IterBlock)->Get_Info().vPos.x  + iScrollX)
		CScrollMgr::Get_Instance()->Set_ScrollX(-2.f);

	if (iOffSetY - 50 > (*m_IterBlock)->Get_Info().vPos.y + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(2.f);

	if (iOffSetY + 50 < (*m_IterBlock)->Get_Info().vPos.y + iScrollY)
		CScrollMgr::Get_Instance()->Set_ScrollY(-2.f);
}

void CSSHScene::Create_Block()
{
	for (int i = 0; i < 48; i++)
	{
		IFD_BLOCK_NORMAL(25.f + i * 50, 300.f, 0.f);
	}

	IFD_BLOCK(2375.f, 350.f, 0.f, 270.f);

	for (int i = 0; i < 15; i++)
	{
		IFD_BLOCK_NORMAL(2425.f + i * 50, 350.f, 0.f);
	}

	IFD_BLOCK(3125.f, 400.f, 0.f, 270.f);

	for (int i = 0; i < 15; i++)
	{
		IFD_BLOCK_NORMAL(3175.f + i * 50, 400.f, 0.f);
	}

	IFD_BLOCK(3875.f, 350.f, 0.f, 90.f);

	for (int i = 0; i < 15; i++)
	{
		IFD_BLOCK_NORMAL(3925.f + i * 50, 350.f, 0.f);
	}

	IFD_BLOCK(4625.f, 300.f, 0.f, 90.f);

	for (int i = 0; i < 13; i++)
	{
		IFD_BLOCK_NORMAL(4675.f + i * 50, 300.f, 0.f);
	}

	IFD_BLOCK(5275.f, 250.f, 0.f, 90.f);
	IFD_BLOCK_NORMAL(5325.f, 250.f, 0.f);
	IFD_BLOCK(5325.f, 200.f, 0.f, 90.f);

	for (int i = 0; i < 9; i++)
	{
		IFD_BLOCK_NORMAL(5375.f + i * 50, 200.f, 0.f);
	}

	IFD_BLOCK(5775.f, 250.f, 0.f, 270.f);
	IFD_BLOCK_NORMAL(5825.f, 250.f, 0.f);
	IFD_BLOCK(5825.f, 300.f, 0.f, 270.f);
	IFD_BLOCK_NORMAL(5875.f, 300.f, 0.f);
	IFD_BLOCK(5875.f, 350.f, 0.f, 270.f);
	IFD_BLOCK_NORMAL(5925.f, 350.f, 0.f);
	IFD_BLOCK(5925.f, 400.f, 0.f, 270.f);

	for (int i = 0; i < 13; i++)
	{
		IFD_BLOCK_NORMAL(5975.f + i * 50, 400.f, 0.f);
	}

	IFD_BLOCK(6575.f, 350.f, 0.f, 90.f);
	IFD_BLOCK_NORMAL(6625.f, 350.f, 0.f);
	IFD_BLOCK(6625.f, 300.f, 0.f, 90.f);

	for (int i = 0; i < 9; i++)
	{
		IFD_BLOCK_NORMAL(6675.f + i * 50, 300.f, 0.f);
	}

	IFD_BLOCK(7075.f, 350.f, 0.f, 270.f);
	IFD_BLOCK_NORMAL(7125.f, 350.f, 0.f);
	IFD_BLOCK(7125.f, 400.f, 0.f, 270.f);

	for (int i = 0; i < 3; i++)
	{
		IFD_BLOCK_NORMAL(7175.f + i * 50, 400.f, 0.f);
	}

	IFD_BLOCK(7275.f, 350.f, 0.f, 90.f);
	IFD_BLOCK_NORMAL(7325.f, 350.f, 0.f);

	for (int i = 0; i < 6; i++)
	{
		IFD_BLOCK_SLOW(7375.f + i * 50, 350.f, 0.f, true);
	}
}

void CSSHScene::Adjust_RevSpeed()
{
	if (dynamic_cast<CBlock_SSH*>(*m_IterBlock)->Get_bSlow())
	{
		SSH_FIRE->Set_RevSpeed(REV_SLOW_SPEED);
		SSH_ICE->Set_RevSpeed(REV_SLOW_SPEED);
	}
}

void CSSHScene::Rev_Auto()
{
	if (0 >= m_iStartTime)
	{

		if (!m_bChange) // ??âÎùæ??????ªÏæ¥????≠Ñ?
		{
			//m_fCheckAngle = SSH_FIRE->Get_Angle();
			Adjust_RevSpeed();

			if ((*m_IterBlock)->Get_Angle() - 5 <= SSH_FIRE->Get_Angle())
			{
				m_fCheckAngle = SSH_FIRE->Get_Angle();
				SSH_FIRE->Set_Angle((*m_IterBlock)->Get_Angle());
				m_bChange = !m_bChange;
				SSH_FIRE->Set_bRev(!m_bChange);
				SSH_ICE->Set_bRev(m_bChange);

				if ((*m_IterBlock)->Get_Angle() <= SSH_ICE->Get_Angle())
				{
					SSH_ICE->Set_Angle((*m_IterBlock)->Get_Angle() - 180.f);
				}
				else
					SSH_ICE->Set_Angle((*m_IterBlock)->Get_Angle() - 180.f);

				++m_IterBlock;
			}
		}
		else if (m_bChange) // ??Ê∫êÎÖøÏæ?????ªÏæ¥????≠Ñ?
		{
			//m_fCheckAngle = SSH_ICE->Get_Angle();
			Adjust_RevSpeed();

			if ((*m_IterBlock)->Get_Angle() - 4 <= SSH_ICE->Get_Angle())
			{
				m_fCheckAngle = SSH_FIRE->Get_Angle();
				SSH_ICE->Set_Angle((*m_IterBlock)->Get_Angle());
				m_bChange = !m_bChange;
				SSH_FIRE->Set_bRev(!m_bChange);
				SSH_ICE->Set_bRev(m_bChange);

				if ((*m_IterBlock)->Get_Angle() <= SSH_FIRE->Get_Angle())
				{
					SSH_FIRE->Set_Angle((*m_IterBlock)->Get_Angle() - 180.f);
				}
				else
					SSH_FIRE->Set_Angle((*m_IterBlock)->Get_Angle() - 180.f);

				++m_IterBlock;
			}
		}
	}
}

void CSSHScene::Rev_Play()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		//m_bChange = !m_bChange; // ??Ï¢äÏ¶≤????bChange???Ë¢Å‚ë∏Ï¶??´Ïìß????Ë¢Å‚ë∏Ï¶????????( ??Ï¢äÏ¶µ???????Ï¢äÏ¶µ????????)
		//SSH_FIRE->Set_bRev(!m_bChange);
		//SSH_ICE->Set_bRev(m_bChange);

		//if (!m_bChange) // ???∞Ïî≠???????¥Ïì¥??
		//{
		//	if (180 < SSH_ICE->Get_Angle())
		//	{
		//		SSH_FIRE->Set_Angle(SSH_ICE->Get_Angle() - 180.f);
		//	}
		//	else
		//		SSH_FIRE->Set_Angle(SSH_ICE->Get_Angle() + 180.f);
		//}
		//else // ??ÁππÎ®Æ?èËã°??????¥Ïì¥??
		//{
		//	if (180 < SSH_FIRE->Get_Angle())
		//	{
		//		SSH_ICE->Set_Angle(SSH_FIRE->Get_Angle() - 180.f);
		//	}
		//	else
		//		SSH_ICE->Set_Angle(SSH_FIRE->Get_Angle() + 180.f);
		//}

		if (!m_bChange) // ?∫Îçâ???®Îì≠??
		{
			Adjust_RevSpeed();

			m_fCheckAngle = SSH_FIRE->Get_Angle();

			if ((*m_IterBlock)->Get_Angle() - SUCSSES_RANGE > m_fCheckAngle || (*m_IterBlock)->Get_Angle() + SUCSSES_RANGE < m_fCheckAngle)
			{
				SSH_FIRE->Set_Dead();
			}

			if ((*m_IterBlock)->Get_Angle() - SUCSSES_RANGE <= SSH_FIRE->Get_Angle() && (*m_IterBlock)->Get_Angle() + SUCSSES_RANGE >= SSH_FIRE->Get_Angle())
			{
				SSH_FIRE->Set_Angle((*m_IterBlock)->Get_Angle());
				m_bChange = !m_bChange;
				SSH_FIRE->Set_bRev(!m_bChange);
				SSH_ICE->Set_bRev(m_bChange);

				if ((*m_IterBlock)->Get_Angle() <= SSH_ICE->Get_Angle())
				{
					SSH_ICE->Set_Angle((*m_IterBlock)->Get_Angle() - 180.f);
				}
				else
					SSH_ICE->Set_Angle((*m_IterBlock)->Get_Angle() - 180.f);

				++m_IterBlock;
			}
		}
		else if (m_bChange) // ??±Ïì¨
		{
			Adjust_RevSpeed();

			m_fCheckAngle = SSH_ICE->Get_Angle();

			if ((*m_IterBlock)->Get_Angle() - SUCSSES_RANGE > m_fCheckAngle || (*m_IterBlock)->Get_Angle() + SUCSSES_RANGE < m_fCheckAngle)
			{
				SSH_ICE->Set_Dead();
			}

			if ((*m_IterBlock)->Get_Angle() - SUCSSES_RANGE <= SSH_ICE->Get_Angle() && (*m_IterBlock)->Get_Angle() + SUCSSES_RANGE >= SSH_ICE->Get_Angle())
			{
				SSH_ICE->Set_Angle((*m_IterBlock)->Get_Angle());
				m_bChange = !m_bChange;
				SSH_FIRE->Set_bRev(!m_bChange);
				SSH_ICE->Set_bRev(m_bChange);

				if ((*m_IterBlock)->Get_Angle() <= SSH_FIRE->Get_Angle())
				{
					SSH_FIRE->Set_Angle((*m_IterBlock)->Get_Angle() - 180.f);
				}
				else
					SSH_FIRE->Set_Angle((*m_IterBlock)->Get_Angle() - 180.f);

				++m_IterBlock;
			}
		}
	}
}
