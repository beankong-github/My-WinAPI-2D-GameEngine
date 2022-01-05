#include "pch.h"
#include "CCore.h"
#include "CPlayer.h"
#include "CTimeMgr.h"

CPlayer player;

CCore::CCore()
	: m_hwnd(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
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

	// ȭ�� ũ�� �ʱ�ȭ ( ������ �ػ󵵿� �´� ũ��� �缳��)
	RECT rt = {0, 0, _ptResolution.x, _ptResolution.y};
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hwnd, nullptr, -8, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
	
	// Device Context ����
	m_hDC = GetDC(m_hwnd);
	
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
	//Rectangle(m_hDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	player.Render(m_hDC);
}
