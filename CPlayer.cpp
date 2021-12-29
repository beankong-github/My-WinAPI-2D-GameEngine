#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
	:m_ptPos{},
	m_ptScale{}
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // VK_LEFT�� ������ ���� ���� ���� ȣ�� �������� �����ִ� ���¶��
	{
		m_ptPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // VK_LEFT�� ������ ���� ���� ���� ȣ�� �������� �����ִ� ���¶��
	{
		m_ptPos.x += 1;
	}
}

void CPlayer::Render(HDC _dc)
{
	Rectangle(_dc, m_ptPos.x - (m_ptScale.x / 2),
		m_ptPos.y - (m_ptScale.y / 2),
		m_ptPos.x + (m_ptScale.x / 2),
		m_ptPos.y + (m_ptScale.y / 2));
}
