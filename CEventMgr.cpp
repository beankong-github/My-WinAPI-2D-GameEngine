#include "pch.h"
#include "CEventMgr.h"
#include "CStageMgr.h"
#include "CStage.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::Update()
{
	bool bChangeStage = false;

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].eType)
		{
		case EEVENT_TYPE::CREATE_OBJ:
			// lParam : Object Adress, wParam : Object Type
		{
			CObj* pNewObj = (CObj*)m_vecEvent[i].lParam;
			EOBJ_TYPE eType = (EOBJ_TYPE)m_vecEvent[i].wParam;

			CStage* pCurStage = CStageMgr::GetInst()->GetCurStage();
			pCurStage->AddObject(pNewObj, eType);
		}
			break;

		case EEVENT_TYPE::DELETE_OBJ:

			break;

		case EEVENT_TYPE::STAGE_CHANGE:
			// lParam : Next Stage Enum		
			CStageMgr::GetInst()->ChangeStage((ESTAGE_TYPE)m_vecEvent[i].lParam);		
			bChangeStage = true;
			break;
		}	

		// �̺�Ʈ �߿� Stage ���� �̺�Ʈ�� �־��ٸ�,
		// ������ �̺�Ʈ�� �� �����ϰ� ����
		if (bChangeStage)
		{
			break;
		}
	}

	m_vecEvent.clear();
}