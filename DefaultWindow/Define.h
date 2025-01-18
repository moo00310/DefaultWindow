#pragma once

#define WINCX		800
#define WINCY		600

#define VK_MAX				0xff
#define OBJ_NOEVENT			0
#define OBJ_DEAD			1	

#define	PURE		= 0
#define PI			3.141592f

#define sqrt_3    1.732f

#define SSH_FIRE dynamic_cast<CPlayer_SSH*>(CObjMgr::Get_Instance()->Get_LastPlayer())
#define SSH_ICE  dynamic_cast<CPlayer_SSH*>(CObjMgr::Get_Instance()->Get_Player())

#define REV_SPEED 3.f

extern HWND		g_hWnd;

enum SCENEID { SC_START, SC_MENU, SC_MOO, SC_KDH, SC_SSH,  SC_HERO, SC_END };
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_SHIELD, OBJ_BUTTON, OBJ_BLOCK, OBJ_END };
enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_UI, RENDER_EFFECT, RENDER_END };

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

static D3DXVECTOR3		Get_Mouse()
{
	POINT		pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f );
}

typedef struct tagInfo
{
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vNormal;	// ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½(ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½)

	D3DXVECTOR3		vPos;

	D3DXMATRIX		matWorld;

}INFO;


// ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ ï¿½Ô¼ï¿½

// ï¿½×µï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö´ï¿?ï¿½Ô¼ï¿½
// D3DXMatrixIdentity(ï¿½×µï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Ö¼ï¿½)
// D3DXMatrixIdentity(&m_tInfo.matWorld);

// Å©ï¿½ï¿½ ï¿½ï¿½È¯ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Ô¼ï¿½
// D3DXMatrixScaling(ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Ö¼ï¿½, Xï¿½ï¿½ï¿½ï¿½, Yï¿½ï¿½ï¿½ï¿½, Zï¿½ï¿½ï¿½ï¿½)
// D3DXMATRIX		matScale;
// D3DXMatrixScaling(&matScale, 1.f, 2.f, 1.f);

// È¸ï¿½ï¿½ ï¿½ï¿½È¯ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Ô¼ï¿½
// D3DXMatrixRotationZ(ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Ö¼ï¿½, È¸ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½(ï¿½ï¿½ï¿½ï¿½))
// D3DXMATRIX		matRotZ, matRevZ;
// D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(angle));

// ï¿½ï¿½Ä¡ ï¿½ï¿½È¯ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Ô¼ï¿½
// D3DXMatrixTranslation(ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Ö¼ï¿½, xï¿½ï¿½Ä¡, yï¿½ï¿½Ä¡, zï¿½ï¿½Ä¡)
// D3DXMATRIX		matTrans;
// D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

// dxï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ï´ï¿½ ï¿½ï¿½Ä°ï¿½ï¿½ï¿?ï¿½Ô¼ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ Ã¹ï¿½ï¿½Â° ï¿½Û¾ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½×µï¿½ ï¿½ï¿½Ä·ï¿?ï¿½ï¿½ï¿½ï¿½ï¿?

// D3DXMATRIX		matScale, matRotZ, matTrans;
// 
// D3DXMatrixScaling(&matScale, 1.f, 2.f, 1.f);
// D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(angle));
// D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
// 
// m_tInfo.matWorld = matScale * matRotZ * matTrans;

// ï¿½ï¿½ï¿½Í¿ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö´ï¿?ï¿½Ô¼ï¿½
// D3DXVec3TransformCoord(ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö¼ï¿½(ï¿½ï¿½Ä¡), ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ä¡ ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿?;
// D3DXVec3TransformNormal(ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö¼ï¿½(ï¿½ï¿½ï¿½ï¿½), ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿?;
