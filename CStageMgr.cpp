#include "pch.h"
#include "CStageMgr.h"
#include "CStage.h"
#include "CStage_Start.h"
//#include "CStage_Play01.h"
//#include "CStage_Play02.h"
//#include "CStage_Exit.h"

CStageMgr::CStageMgr()
	:m_arrStage{}
	,m_pCurStage(nullptr)
{}

CStageMgr::~CStageMgr()
{
	// ���������� Heap �޸� ������ �����Ҵ� �� ���̹Ƿ� 
	// ���������� ����� �� �Ҵ� �����ؾ� �Ѵ�.
	for (size_t i = 0; i < (int)ESTAGE_TYPE::STAGE_END; i++)
	{
		if (nullptr != m_arrStage[i])
		{
			delete m_arrStage[i];
		}
	}

}

void CStageMgr::Init()
{
	// ��� �������� ����
	m_arrStage[(UINT)ESTAGE_TYPE::START] = new CStage_Start;
	//m_arrStage[(UINT)ESTAGE_TYPE::PLAY_01] = new CStage_Play01;
	//m_arrStage[(UINT)ESTAGE_TYPE::PLAY_02] = new CStage_Play02;
	//m_arrStage[(UINT)ESTAGE_TYPE::EXIT] = new CStage_Exit;
	
	// ���� �������� ����
	m_pCurStage = m_arrStage[(UINT)ESTAGE_TYPE::START];
	m_pCurStage->Init();
}

void CStageMgr::Update()
{
	m_pCurStage->Update();
}

void CStageMgr::Render(HDC _dc)
{
	m_pCurStage->Render(_dc);
}
