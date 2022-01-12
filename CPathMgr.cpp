#include "pch.h"
#include "CPathMgr.h"

CPathMgr::CPathMgr()
	:m_strContentPath{ '\0',}
{
}

CPathMgr::~CPathMgr()
{
}

void CPathMgr::Init()
{
	//Content ���� ��θ� ã�Ƴ���
	GetCurrentDirectory(255, m_strContentPath);
	
	// �θ� ���� ��θ� �˾Ƴ��� (OutputFile ����)
	int iLen = (int)wcslen(m_strContentPath);
	
	for(int i = iLen - 1; 0 <= i; --i)
	{
		if (L'\\' == m_strContentPath[i])
		{
			m_strContentPath[i] = L'\0';
			break;
		}
	}

	// bin\\content ���� ��θ� ���δ�
	wcscat_s(m_strContentPath, L"\\bin\\content\\");
}
