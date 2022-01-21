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
		if (nullptr == pLeftCol)
			continue;

		for (size_t j = 0; j < _right.size(); ++j)
		{
			pRightCol = _right[j]->GetCollider();
			// ������Ʈ�� �ݶ��̴��� ���ٸ� �Ǵ� Dead ���¶��
			if (nullptr == pRightCol)
				continue;

			// �� �浹ü�� ������ �浹�߾����� �˻�
			// �� �浹ü�� ���� ���̵� ����
			COLLIDER_ID ID;
			ID.iLeftID = pLeftCol->GetID();
			ID.iRightID = pRightCol->GetID();
			map<LONGLONG, bool> ::iterator iter = m_mapColInfo.find(ID.id);

			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(make_pair(ID.id, false));
				iter = m_mapColInfo.find(ID.id);
			}

			// �� �� �ϳ��� Dead ���� üũ
			bool bDead = pRightCol->GetOwner()->IsDead() || pLeftCol->GetOwner()->IsDead();

			// �浹 �˻�
			if (IsCollision(pLeftCol, pRightCol))
			{
			// �浹 O
				// ���� �����ӿ��� �浹 ���̾���.
				if (iter->second)	
				{
					// �� �� �� ������Ʈ�� Dead �� ���
					if (bDead)
					{
						// �� collider���� �浹 ���� �˸�
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						m_mapColInfo.erase(iter);
					}
					else
					{
						// �� collider���� �浹 �˸�
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol); 
					}
				}

				// ���� �����ӿ��� �浹���� �ʾҴ�.
				else
				{
					// �� collider���� �浹 ���� �˸�
					if (!bDead)
					{
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
					else
					{
						m_mapColInfo.erase(iter);
					}
				}

			}
			
			// �浹 x
			else
			{
				// �浹�� �ƴ� ���
				// ���� �����ӱ����� �浹���̾���
				if (iter->second)
				{
					// �� collider���� �浹 ���� �˸�
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
				if (bDead)
				{
					m_mapColInfo.erase(iter);
				}
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
