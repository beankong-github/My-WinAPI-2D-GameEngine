#include "pch.h"
#include "CStage.h"
#include "CCore.h"
#include "CObj.h"
#include "CPlayer.h"
#include "CBullet.h"

CStage::CStage()
{
}

CStage::~CStage()
{
	Clear();
}


void CStage::Update()
{
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		for (size_t i = 0; i < m_vecObj[j].size(); i++)
		{
			if (m_vecObj[j][i]->IsDead())
				continue;

			m_vecObj[j][i]->Update();
		}
	}
}

void CStage::LateUpdate()
{
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		for (size_t i = 0; i < m_vecObj[j].size(); i++)
		{
			if (m_vecObj[j][i]->IsDead())
				continue;

			m_vecObj[j][i]->LateUpdate();
		}
	}
}

void CStage::Render(HDC _dc)
{
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		vector<CObj*>::iterator iter = m_vecObj[j].begin();

		for (; iter != m_vecObj[j].end();)
		{
			// ������Ʈ�� Dead ���¸� ������Ʈ �迭���� �����Ѵ�
			if ((*iter)->IsDead())
				iter = m_vecObj[j].erase(iter);

			else
			{
				(*iter)->Render(_dc);
				++iter;
			}
		}
	}
}

void CStage::Clear()
{
	// ���� �ʱ�ȭ
	for (int j = 0; j < (UINT)EOBJ_TYPE::END; j++)
	{
		for (size_t i = 0; i < m_vecObj[j].size(); i++)
		{
			assert(m_vecObj[j][i]);
			delete m_vecObj[j][i];
		}
		m_vecObj[j].clear();
	}
	// �þ ���� ���� ���̱�
	// vector<CObj*> tempVec;
	// m_vecObj.swap(tempVec);
}
