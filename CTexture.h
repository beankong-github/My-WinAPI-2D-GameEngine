#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    // �ؽ�ó�� ���� ���� �ػ�(�ȼ� ����)
    BITMAP  m_info;
    HBITMAP m_hBit;
    HDC     m_hDC;

public:
    HDC GetDC() { return m_hDC; }
    UINT Width() { return m_info.bmWidth; }
    UINT Height() { return m_info.bmHeight; }

private:
    int Load(const wstring& _strFullPath) override;

public:
    CTexture();
    ~CTexture();

};

