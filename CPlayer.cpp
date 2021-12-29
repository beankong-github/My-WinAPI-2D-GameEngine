#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
	:m_vPos{},
	m_vScale{}
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // VK_LEFT�� ������ ���� ���� ���� ȣ�� �������� �����ִ� ���¶��
	{
		m_vPos.x -= 0.01f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // VK_LEFT�� ������ ���� ���� ���� ȣ�� �������� �����ִ� ���¶��
	{
		m_vPos.x += 0.01f;
	}
}

void CPlayer::Render(HDC _dc)
{
	Rectangle(_dc,  (int)(m_vPos.x - (m_vScale.x / 2.f)),
				 	(int)(m_vPos.y - (m_vScale.y / 2.f)),
				 	(int)(m_vPos.x + (m_vScale.x / 2.f)),
					(int)(m_vPos.y + (m_vScale.y / 2.f)));
}
