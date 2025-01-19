#pragma once
#include "CObj.h"
#include "CKDHPlayer.h"
#include "Define.h"

class CHexaPad : public CObj
{
public:
	CHexaPad();
	virtual ~CHexaPad();

	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void SetPlayer(CKDHPlayer* _player);
	void SetDirection(kDIRECTION _kDIR);

private:
	float GetDistance(D3DXVECTOR3 _info)
	{
		D3DXVECTOR3 result = GetLocalPositionToWorld() - _info;

		return D3DXVec3Length(&result);
	}

	// 나의 위치를 로컬 좌표에서 월드 좌표로 변환.
	D3DXVECTOR3 GetLocalPositionToWorld()
	{
		D3DXMatrixTranslation(&m_MatrixPosition, m_localPosition.x, m_localPosition.y, m_localPosition.z);
		D3DXMatrixTranslation(&m_MatrixParent, m_Player->GetLocalParentPosition().x, m_Player->GetLocalParentPosition().y, m_Player->GetLocalParentPosition().z);
		D3DXMatrixRotationZ(&m_MatrixRevolution, D3DXToRadian(m_rovAngle));

		m_MatrixWorld = m_MatrixPosition * m_MatrixRevolution * m_MatrixParent;

		return { m_MatrixWorld.m[3][0], m_MatrixWorld.m[3][1], m_MatrixWorld.m[3][2] };
	}

private:
	// 원점.
	D3DXVECTOR3 m_ResetPosition;

	// 플레이어 위치.
	D3DXVECTOR3 m_localPosition;

	// 플레이어 바라보는 곳.
	D3DXVECTOR3 m_localLookAt;

	// 플레이어 방향.
	D3DXVECTOR3 m_localDirection;

	// 플레이어 크기.
	D3DXVECTOR3 m_localScale;

	// 위치 행렬.
	D3DXMATRIX m_MatrixPosition;

	// 회전 행렬.
	D3DXMATRIX m_MatrixRotate;

	// 크기 행렬.
	D3DXMATRIX m_MatrixScale;

	// 공전 행렬.
	D3DXMATRIX m_MatrixRevolution;

	// 부모 행렬.
	D3DXMATRIX m_MatrixParent;

	// 월드 행렬.
	D3DXMATRIX m_MatrixWorld;

	// 버텍스.
	D3DXVECTOR3 vertex[4];

	// 기존 버텍스.
	D3DXVECTOR3 vertexOrigin[4];

	// 내 크기.
	float m_fScale;

	float m_rotAngle;

	float m_rovAngle;

	kDIRECTION m_Direction;

	CKDHPlayer* m_Player;
};

