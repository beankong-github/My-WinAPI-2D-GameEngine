#include "pch.h"
#include "CTexture.h"
#include "CCore.h"

CTexture::CTexture()
    :m_hBit(0)
    ,m_hDC(0)
    ,m_info{}
{
}

CTexture::~CTexture()
{
    DeleteObject(m_hBit);
    DeleteDC(m_hDC);
}

int CTexture::Load(const wstring& _strFullPath)
{
    m_hBit = (HBITMAP)LoadImage(nullptr, _strFullPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
    
    if (nullptr == m_hBit)
    {
        return E_FAIL;
    }

    m_hDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

    // 텍스처를 그리기 위한 새 DC가 새로 만든 bitmap(texture)을 그리기 목적지로 선택한다.
    HBITMAP hPrevBitMap = (HBITMAP)SelectObject(m_hDC, m_hBit);	// m_hbit과 m_hDC 연결
    DeleteObject(hPrevBitMap);									// 연결 후 임시 비트맵 삭제

    // 비트맵 정보 알아내기
    GetObject(m_hBit,sizeof(BITMAP), & m_info);

    return S_OK;
}

int CTexture::Create(UINT _iWidth, UINT _iHeight)
{
    m_hBit = CreateCompatibleBitmap(CCore::GetInst()->GetMainDC(), _iWidth, _iHeight);
    m_hDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

    if (nullptr == m_hBit || nullptr == m_hDC)
        return E_FAIL;

    HBITMAP hPrevBitMap = (HBITMAP)SelectObject(m_hDC, m_hBit);
    DeleteObject(hPrevBitMap);

    // 비트맵 정보 알아내기
    GetObject(m_hBit, sizeof(BITMAP), &m_info);

    return S_OK;
}

