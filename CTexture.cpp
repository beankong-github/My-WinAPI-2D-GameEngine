#include "pch.h"
#include "CTexture.h"
#include "CCore.h"

int CTexture::Load(const wstring& _strFullPath)
{
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFullPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
    
    if (nullptr == m_hBit)
    {
        return E_FAIL;
    }

    m_hDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

    // �ؽ�ó�� �׸��� ���� �� DC�� ���� ���� bitmap(texture)�� �׸��� �������� �����Ѵ�.
    HBITMAP hPrevBitMap = (HBITMAP)SelectObject(m_hDC, m_hBit);	// m_hbit�� m_hDC ����
    DeleteObject(hPrevBitMap);									// ���� �� �ӽ� ��Ʈ�� ����

    return S_OK;
}

CTexture::CTexture()
    :m_iHeight()
    ,m_iWidth()
    ,m_hBit(0)
    ,m_hDC(0)
{
}

CTexture::~CTexture()
{
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);
}
