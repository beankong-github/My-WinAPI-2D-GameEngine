#include "pch.h"
#include "CKeyMgr.h"

// KEY enum ������ �����ϴ� Ű�� ���� �ƽ�Ű�ڵ�
int g_iVK[(UINT)KEY::KEY_END] = 
{
	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','H','J','K','L',
	'Z','X','C','V','B','N','M',
	
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_NUMPAD0,
	VK_NUMPAD1,
	VK_NUMPAD2,
	VK_NUMPAD3,
	VK_NUMPAD4,
	VK_NUMPAD5,
	VK_NUMPAD6,
	VK_NUMPAD7,
	VK_NUMPAD8,
	VK_NUMPAD9,

	VK_LSHIFT,
	VK_LMENU,
	VK_LCONTROL,
	VK_SPACE,
	VK_RETURN,
	VK_BACK,
	VK_ESCAPE,
	VK_TAB,
};

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}


void CKeyMgr::Init()
{
	// Ű ���� �ʱ�ȭ�ؼ� ����(�����迭)�� ����
	for (UINT i = 0; i < (UINT)KEY::KEY_END; i++)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update()
{
	// ��� Ű�� ���� üũ
	for (UINT i = 0; i < (UINT)KEY::KEY_END; i++)
	{
		// Ű�� �����ִ�.
		if (GetAsyncKeyState(g_iVK[i]) & 0x8000)
		{
			// ������ ������ �ʾҴ�.
			if (false == m_vecKey[i].bprevCheck)
			{
				m_vecKey[i].eState = KEY_STATE::TAP;
			}

			// ������ ���� �־���.
			else
			{
				m_vecKey[i].eState = KEY_STATE::PRESSED;
			}
			
			// ���� �Է»��¸� ����
			m_vecKey[i].bprevCheck = true;
		}

		// Ű�� �������� �ʴ�.
		else
		{
			// ������ �����־���.
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::PRESSED == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			// ������ �������� �ʾҴ�
			else
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}

			// ���� �Է»��¸� ����
			m_vecKey[i].bprevCheck = false;
		}
	}
}
