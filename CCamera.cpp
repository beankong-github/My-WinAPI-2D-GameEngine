#include "pch.h"
#include "CCamera.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{}

void CCamera::Init()
{
	Vec vResolution = CCore::GetInst()->GetResolution();
	
	m_vLookAt = vResolution / 2.f;
}

void CCamera::Update()
{
	// Ű �Է¿� ���� ī�޶� �̵�
	if (IS_KEY_PRESSED(KEY::UP))
	{
		m_vLookAt.y += DS * 200.f;
	}

	if (IS_KEY_PRESSED(KEY::DOWN))
	{
		m_vLookAt.y += DS * 200.0f;
	}

	if (IS_KEY_PRESSED(KEY::LEFT))
	{
		m_vLookAt.x -= DS * 200.f;
	}
	if (IS_KEY_PRESSED(KEY::RIGHT))
	{
		m_vLookAt.x += DS * 200.f;
	}

	// �ػ� �߾Ӱ� ���ϱ�
	Vec vCenter = CCore::GetInst()->GetResolution();
	vCenter /= 2.f;
	m_vDiff = m_vLookAt - vCenter;

	
}
