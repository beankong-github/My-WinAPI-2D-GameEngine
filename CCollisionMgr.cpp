#include "pch.h"
#include "CCollisionMgr.h"

#include "CStageMgr.h"
#include "Cstage.h"

#include "CObj.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	:m_arrCheck{}
{}

CCollisionMgr::~CCollisionMgr()
{}

void CCollisionMgr::Update()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		for (UINT j = i; j < MAX_LAYER; j++)
		{
			// i Ÿ�� ������Ʈ�� j Ÿ�� ������Ʈ �浹!
			if (m_arrCheck[i] & (1 << j))
			{
				// �浹�� i Ÿ�� ������Ʈ�� j Ÿ�� ������Ʈ �迭�� ������ �浹 �˻�
				CStage* pCurStage = CStageMgr::GetInst()->GetCurStage();
				CollisionGroup(pCurStage->GetObjects((EOBJ_TYPE)i), pCurStage->GetObjects((EOBJ_TYPE)j));
			}
		}
	}
}

void CCollisionMgr::CollisionGroup(const vector<CObj*>& _left, const vector<CObj*>& _right)
{
	CCollider* pLeftCol = nullptr;
	CCollider* pRightCol = nullptr;

	for (size_t i = 0; i < _left.size(); ++i)
	{
		pLeftCol = _left[i]->GetCollider();
		// ������Ʈ�� �ݶ��̴��� ���ٸ� �Ǵ� Dead ���¶��
		if (nullptr == pLeftCol || pLeftCol->GetOwner()->IsDead())
			continue;

		for (size_t j = 0; j < _right.size(); ++j)
		{
			pRightCol = _right[j]->GetCollider();
			// ������Ʈ�� �ݶ��̴��� ���ٸ� �Ǵ� Dead ���¶��
			if (nullptr == pRightCol || pRightCol->GetOwner()->IsDead())
				continue;

			// ������Ʈ 1 �� 1 �浹 �˻�
			if (IsCollision(pLeftCol, pRightCol))
			{
				// �浹���� ���
				// �� collider���� �浹 �˸�
				pLeftCol->OnCollision(pRightCol);
				pRightCol->OnCollision(pLeftCol);
			}
			else
			{
				// �浹�� �ƴ� ���
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _left, CCollider* _right)
{
	Vec vLColPos =  _left->GetFinalPos();
	Vec vLColScale = _left->GetScale();

	Vec vRColPos = _right->GetFinalPos();
	Vec vRColScale = _right->GetScale();

	float fDist = 0.f;

	// x�� �浹 �׽�Ʈ
	fDist = abs(vLColPos.x - vRColPos.x);
	if (fDist > abs(vLColScale.x / 2 + vRColScale.x / 2))
	{
		//�Ȱ�ģ��
		return false;
	}

	// y�� �浹 �׽�Ʈ
	fDist = abs(vLColPos.y - vRColPos.y);
	if (fDist > abs(vLColScale.y / 2 + vRColScale.y / 2))
	{
		//�Ȱ�ģ��
		return false;
	}

	return true;
}

void CCollisionMgr::CollisionOn(EOBJ_TYPE _left, EOBJ_TYPE _right)
{
	UINT iCol = 0, iRow = 0;

	// Left�� Right �� �� ū ���� ���� Ȱ���Ѵ�
	if ((UINT)_left > (UINT)_right)
	{
		iCol = (UINT)_left;
		iRow = (UINT)_right;
	}
	else
	{
		iCol = (UINT)_right;
		iRow = (UINT)_left;
	}

	m_arrCheck[iRow] |= (1 << iCol);
}

void CCollisionMgr::CollisionOff(EOBJ_TYPE _left, EOBJ_TYPE _right)
{
	UINT iCol = 0, iRow = 0;

	// Left�� Right �� �� ū ���� ���� Ȱ���Ѵ�
	if ((UINT)_left > (UINT)_right)
	{
		iCol = (UINT)_left;
		iRow = (UINT)_right;
	}
	else
	{
		iCol = (UINT)_right;
		iRow = (UINT)_left;
	}

	m_arrCheck[iRow] &= ~(1 << iCol);
}
