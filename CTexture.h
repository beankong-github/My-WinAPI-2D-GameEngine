#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    // �ؽ�ó�� ���� ���� �ػ�(�ȼ� ����)
    UINT m_iWidth;
    UINT m_iHeight;

    HBITMAP m_hBit;
    HDC     m_hDC;

public:
    HDC GetDC() { return m_hDC; }

private:
    int Load(const wstring& _strFullPath) override;
    
public:
    CTexture();
    ~CTexture();

};

