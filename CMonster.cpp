#include "pch.h"
#include "CMonster.h"

#include "CBullet.h"

CMonster::CMonster()
	:m_iHitCount(5)
{
	// collider �߰�
	CCollider* pCollider = new CCollider;
	AddComponent(pCollider);
}

CMonster::~CMonster()
{
}

void CMonster::Update()
{
}

void CMonster::Render(HDC _dc)
{
	CObj::Render(_dc);

#ifdef _DEBUG
	Render_Component(_dc);
#endif // DEBUG

}

void CMonster::OnCollision(CObj* _pOtherObj)
{
	// �÷��̾� �Ѿ˰� �浹 �� 
	dynamic_cast<CBullet*>(_pOtherObj);
	if (nullptr != _pOtherObj)
	{
		// HitCount ��ŭ Buller�� �浹 �� ����
		m_iHitCount -= 1;
		if(m_iHitCount <= 0 )
			DeleteObject(this);
	}

}

