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
	for (size_t i = 0; i < m_vecObj.size(); i++)
	{
		m_vecObj[i]->Update();
	}
}

void CStage::Render(HDC _dc)
{
	for (size_t i = 0; i < m_vecObj.size(); i++)
	{
		m_vecObj[i]->Render(_dc);
	}
}

void CStage::Clear()
{
	// ���� �ʱ�ȭ
	for (size_t i = 0; i < m_vecObj.size(); i++)
	{
		assert(m_vecObj[i]);
		delete m_vecObj[i];
	}
	m_vecObj.clear();

	// �þ ���� ���� ���̱�
	// vector<CObj*> tempVec;
	// m_vecObj.swap(tempVec);
}