#pragma once
#include "CPlayer.h"
class CKDHPlayer : public CPlayer
{
public:
	CKDHPlayer();
	virtual ~CKDHPlayer();

	// CPlayer을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Key_Input() override;

	D3DXVECTOR3 GetLocalParentPosition()
	{
		return m_localParentPosition;
	}

private:
	// 원점.
	D3DXVECTOR3 m_ResetPosition;

	// 플레이어 위치.
	D3DXVECTOR3 m_localPosition;

	// 부모 위치.
	D3DXVECTOR3 m_localParentPosition;

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
	D3DXVECTOR3 vertex[3];

	// 기존 버텍스.
	D3DXVECTOR3 vertexOrigin[3];

	// 부모 크기.
	float m_fParentScale;

	// 내 크기.
	float m_fScale;

	// 공전 각도.
	float m_revolAngle;

	// 자전 각도.
	float m_rotAngle;

	// 스케일 증가값.
	float m_moreScale;

	// 공전 속도.
	float m_revolSpeed;

	// 자전 속도.
	float m_rotSpeed;
};

