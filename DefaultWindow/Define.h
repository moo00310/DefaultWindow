#pragma once

#define WINCX		800
#define WINCY		600

#define VK_MAX				0xff
#define OBJ_NOEVENT			0
#define OBJ_DEAD			1	

#define	PURE		= 0
#define PI			3.141592f

#define sqrt_3    1.732f

#define OFFSET	500

#define SSH_FIRE dynamic_cast<CPlayer_SSH*>(CObjMgr::Get_Instance()->Get_LastPlayer())
#define SSH_ICE  dynamic_cast<CPlayer_SSH*>(CObjMgr::Get_Instance()->Get_Player())

#define REV_SPEED 3.f

extern HWND		g_hWnd;


enum SCENEID { SC_START, SC_MENU, SC_MOO, SC_KDH, SC_SSH,  SC_HERO, SC_END };
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_SHIELD, OBJ_BUTTON, OBJ_BLOCK, OBJ_END };
enum RENDERID { RENDER_BACKGROUND, RENDER_GAMEOBJECT, RENDER_GAMEOBJECT_FRONT, RENDER_UI, RENDER_EFFECT, RENDER_END };

enum CarmeraState { CS_ZoomAndFollow, CS_Shake1, CS_Shake2, CS_ZoomIN, CS_Slow_ZoomIN, CS_Force_ZoomIN, CS_ZoomOUT,CS_END };
enum Carmera {C_Move_LT, C_Move_size, C_Zoom_LT, C_Zoom_size, C_End };

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
	D3DXVECTOR3		vNormal;	// ���� ����(���� ����)

	D3DXVECTOR3		vPos;

	D3DXMATRIX		matWorld;

}INFO;



// 시퀀스용.
enum kSEQUENCE
{
	SEQUENCE_WAIT,
	SEQUENCE_PLAY,
	SEQUENCE_END,
};

enum kDIRECTION
{
	DIR_UP = 0,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};


// �׵� �����?������ִ�?�Լ�
// D3DXMatrixIdentity(�׵� �����?�����?���� �����?�ּ�)
// D3DXMatrixIdentity(&m_tInfo.matWorld);

// ũ�� ��ȯ �����?�����?�Լ�
// D3DXMatrixScaling(�������?������ �����?�ּ�, X����, Y����, Z����)
// D3DXMATRIX		matScale;
// D3DXMatrixScaling(&matScale, 1.f, 2.f, 1.f);

// ȸ�� ��ȯ �����?�����?�Լ�
// D3DXMatrixRotationZ(�������?������ �����?�ּ�, ȸ�� ����(����))
// D3DXMATRIX		matRotZ, matRevZ;
// D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(angle));

// ��ġ ��ȯ �����?�����?�Լ�
// D3DXMatrixTranslation(�������?������ �����?�ּ�, x��ġ, y��ġ, z��ġ)
// D3DXMATRIX		matTrans;
// D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

// dx���� �����ϴ� ��İ���?�Լ����� ���� ù��° �۾����� ���?���� ������ �����?�׵� ��ķ�?�����?

// D3DXMATRIX		matScale, matRotZ, matTrans;
// 
// D3DXMatrixScaling(&matScale, 1.f, 2.f, 1.f);
// D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(angle));
// D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
// 
// m_tInfo.matWorld = matScale * matRotZ * matTrans;

// ���Ϳ� �����?������ ��������ִ�?�Լ�
// D3DXVec3TransformCoord(���?���� ������ ������ �ּ�(��ġ), ������ ������ ��ġ ����, ���?;
// D3DXVec3TransformNormal(���?���� ������ ������ �ּ�(����), ������ ������ ���� ����, ���?;
