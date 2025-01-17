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

extern HWND		g_hWnd;

enum SCENEID { SC_START, SC_MENU, SC_MOO, SC_SSH, SC_END };
enum OBJID { OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_MOUSE, OBJ_SHIELD, OBJ_BUTTON, OBJ_END };
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
	D3DXVECTOR3		vNormal;	// 법선 벡터(방향 벡터)

	D3DXVECTOR3		vPos;

	D3DXMATRIX		matWorld;

}INFO;


// 행렬 관련 함수

// 항등 행렬을 만들어주는 함수
// D3DXMatrixIdentity(항등 행렬을 만들기 위한 행렬의 주소)
// D3DXMatrixIdentity(&m_tInfo.matWorld);

// 크기 변환 행렬을 만드는 함수
// D3DXMatrixScaling(결과값을 저장할 행렬의 주소, X배율, Y배율, Z배율)
// D3DXMATRIX		matScale;
// D3DXMatrixScaling(&matScale, 1.f, 2.f, 1.f);

// 회전 변환 행렬을 만드는 함수
// D3DXMatrixRotationZ(결과값을 저장할 행렬의 주소, 회전 각도(라디안))
// D3DXMATRIX		matRotZ, matRevZ;
// D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(angle));

// 위치 변환 행렬을 만드는 함수
// D3DXMatrixTranslation(결과값을 저장할 행렬의 주소, x위치, y위치, z위치)
// D3DXMATRIX		matTrans;
// D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

// dx에서 제공하는 행렬관련 함수들은 가장 첫번째 작업으로 결과 값을 저장할 행렬을 항등 행렬로 만든다.

// D3DXMATRIX		matScale, matRotZ, matTrans;
// 
// D3DXMatrixScaling(&matScale, 1.f, 2.f, 1.f);
// D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(angle));
// D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
// 
// m_tInfo.matWorld = matScale * matRotZ * matTrans;

// 벡터와 행렬의 곱셈을 수행시켜주는 함수
// D3DXVec3TransformCoord(결과 값을 저장할 벡터의 주소(위치), 곱셈을 수행할 위치 벡터, 행렬);
// D3DXVec3TransformNormal(결과 값을 저장할 벡터의 주소(방향), 곱셈을 수행할 방향 벡터, 행렬);
