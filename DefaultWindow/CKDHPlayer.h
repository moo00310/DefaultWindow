#pragma once
#include "CPlayer.h"
class CKDHPlayer : public CPlayer
{
public:
	CKDHPlayer();
	virtual ~CKDHPlayer();

	// CPlayer��(��) ���� ��ӵ�
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

	// ���� ��ġ�� ���� ��ǥ���� ���� ��ǥ�� ��ȯ.
	D3DXVECTOR3 GetLocalPositionToWorld()
	{
		D3DXMatrixTranslation(&m_MatrixPosition, m_localPosition.x, m_localPosition.y, m_localPosition.z);
		D3DXMatrixTranslation(&m_MatrixParent, m_localParentPosition.x, m_localParentPosition.y, m_localParentPosition.z);
		D3DXMatrixRotationZ(&m_MatrixRevolution, D3DXToRadian(m_revolAngle));

		m_MatrixWorld = m_MatrixPosition * m_MatrixRevolution * m_MatrixParent;

		return { m_MatrixWorld.m[3][0], m_MatrixWorld.m[3][1], m_MatrixWorld.m[3][2] };
	}

private:
	// ����.
	D3DXVECTOR3 m_ResetPosition;

	// �÷��̾� ��ġ.
	D3DXVECTOR3 m_localPosition;

	// �θ� ��ġ.
	D3DXVECTOR3 m_localParentPosition;

	// �÷��̾� �ٶ󺸴� ��.
	D3DXVECTOR3 m_localLookAt;

	// �÷��̾� ����.
	D3DXVECTOR3 m_localDirection;

	// �÷��̾� ũ��.
	D3DXVECTOR3 m_localScale;

	// ��ġ ���.
	D3DXMATRIX m_MatrixPosition;

	// ȸ�� ���.
	D3DXMATRIX m_MatrixRotate;

	// ũ�� ���.
	D3DXMATRIX m_MatrixScale;

	// ���� ���.
	D3DXMATRIX m_MatrixRevolution;

	// �θ� ���.
	D3DXMATRIX m_MatrixParent;

	// ���� ���.
	D3DXMATRIX m_MatrixWorld;

	// ���ؽ�.
	D3DXVECTOR3 vertex[3];

	// ���� ���ؽ�.
	D3DXVECTOR3 vertexOrigin[3];

	// �θ� ũ��.
	float m_fParentScale;

	// �� ũ��.
	float m_fScale;

	// ���� ����.
	float m_revolAngle;

	// ���� ����.
	float m_rotAngle;

	// ������ ������.
	float m_moreScale;

	// ���� �ӵ�.
	float m_revolSpeed;

	// ���� �ӵ�.
	float m_rotSpeed;
};

