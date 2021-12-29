#include "pch.h"
#include "CCore.h"
#include "CPlayer.h"

CPlayer player;

CCore::CCore()
	: m_hwnd(nullptr),
	m_hDC(nullptr),
	m_ptResolution{}
{
}

CCore::~CCore()
{
	// DC ����
	ReleaseDC(m_hwnd, m_hDC);
}

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// ȭ�� ũ�� �ʱ�ȭ
	RECT rt = {0, 0, _ptResolution.x, _ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hwnd, nullptr, -8, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	// Device Context ����
	m_hDC = GetDC(m_hwnd);
	
	// �÷��̾� ��ġ
	player.SetPos(POINT{m_ptResolution.x/2, m_ptResolution.y/2});
	player.SetScale(POINT{100, 100});


	return S_OK;
}

void CCore::Update()
{ 
	static int i = 0;
	i++;	// �ʴ� �Լ� ���� Ƚ�� ī��Ʈ

	static ULONGLONG iPrevCount = GetTickCount64();		// ���� 1ȸ�� ����
	ULONGLONG iCurCount = GetTickCount64();				// �Ź� ����
	
	// 1�ʿ� �ѹ��� ���ǿ� �ɸ�
	if (iCurCount - iPrevCount > 1000)
	{
		wchar_t szOut[255] = {};
		wsprintf(szOut, L"�ʴ� CCore::Update �Լ� ȣ�� Ƚ��: %d", i);
		SetWindowText(m_hwnd, szOut);

		i = 0;
		iPrevCount = iCurCount;
	}

	player.Update();

	
	// ȭ�� �����
	Rectangle(m_hDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	player.Render(m_hDC);
}
