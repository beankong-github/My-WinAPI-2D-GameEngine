#include "pch.h"
#include "CMonster.h"

#include "CBullet.h"
#include "CCore.h"
#include "CCollider.h"

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

void CMonster::OnCollisionEnter(CObj* _pOther)
{	
}

void CMonster::OnCollision(CObj* _pOther)
{
	// �÷��̾� �Ѿ˰� �浹 �� 
 	CBullet* pbullet = dynamic_cast<CBullet*>(_pOther);
	if (nullptr != pbullet)
	{
		// HitCount ��ŭ Buller�� �浹 �� ����
		m_iHitCount -= 1;
		if(m_iHitCount <= 0 )
			DeleteObject(this);
	}

}

void CMonster::OnCollisionExit(CObj* _pOther)
{	
}

