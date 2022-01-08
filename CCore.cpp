#include "pch.h"
#include "CCore.h"
#include "CPlayer.h"
#include "CTimeMgr.h"

CPlayer player;

CCore::CCore()
	: m_hwnd(nullptr)
	, m_hDC(nullptr)
	, m_hBackBitMap(nullptr)
	, m_hBackDC(nullptr)
	, m_ptResolution{}
{
}

CCore::~CCore()
{
	// DC ����
	ReleaseDC(m_hwnd, m_hDC);

	// �� ���� ����
	DeleteObject(m_hBackBitMap);
	DeleteDC(m_hBackDC);			// ���� ������ DC�� ReleaseDC�� �ƴ� DeleteDC�� ����Ѵ�.
}

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// ȭ�� ũ�� �ʱ�ȭ ( ������ �ػ󵵿� �´� ũ��� �缳��)
	RECT rt = {0, 0, _ptResolution.x, _ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hwnd, nullptr, -8, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	// Device Context ����
	m_hDC = GetDC(m_hwnd);	// ���� window�� �������� �ϴ� DC
	
	// BackBuffer ����
 	m_hBackBitMap =  CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hBackDC =  CreateCompatibleDC(m_hDC);
 	
	// Backbuffer DC�� ���� ���� bitmap(BackBitMap)�� �׸��� �������� �����Ѵ�.
	HBITMAP hPrevBitMap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitMap);	// m_hBackBitMap�� m_hBackDC ����
	DeleteObject(hPrevBitMap);												// ���� �� �ӽ� ��Ʈ�� ����

	// Manager �ʱ�ȭ
	CTimeMgr::GetInst()->Init();


	// �÷��̾� ��ġ
	player.SetPos(Vec{m_ptResolution.x / 2, m_ptResolution.y / 2 });
	player.SetScale(Vec{100, 100});


	return S_OK;
}

void CCore::Update()
{	// ==================
	//	 Manager Update
	// ==================
	CTimeMgr::GetInst()->Update();


	// ==================
	//	 Object Update
	// ==================

	player.Update();


	// ==================
	//	  Game Render
	// ==================

	// ȭ�� �����
	Rectangle(m_hBackDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
	
	// Player �׸���
	player.Render(m_hBackDC);

	// BackBuffer ������ ������ ��Ʈ������ �ű��(����)
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hBackDC, 0, 0, SRCCOPY);
}
