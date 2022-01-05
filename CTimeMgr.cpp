#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"

CTimeMgr::CTimeMgr()
	: m_liFreqency{}
	, m_liPrevCount{}
	, m_liCurCount{}
	, m_iFPS(0)
	, m_fDS(0.f)
	, m_iElapsedTime(0)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Init()
{
	/// <summary>
	/// QueryPerformanceCounter (_Out_ LARGE_INTEGER* lpPerformanceCount) 
	/// - 8����Ʈ ����(longlong)�� ���� ����
	/// - �ʴ� ī��Ʈ�ϴ� ���� ��ȯ (�뷫 �ʴ� õ��)
	/// </summary>
	QueryPerformanceFrequency(&m_liFreqency);
	/// <summary>
	/// QueryPerformanceCounter(_Out_ LARGE_INTEGER* lpPerformanceCount)
	/// - 8����Ʈ ����(longlong)�� ��������
	/// - ������� ī��Ʈ�� �� ��
	/// - Delta Second : ������� ī��Ʈ�� �� �� / �ʴ� ī��Ʈ�� �� ��
	/// </summary>
	QueryPerformanceCounter(&m_liPrevCount);
}

void CTimeMgr::Update()
{
	// ===============================
	//			DS ���ϱ�
	// ===============================
	
	// ���� ī���� Ȯ��
	QueryPerformanceCounter(&m_liCurCount);
	
	// ���� ī���ð� ���� ī������ ���̸� �ʴ� ī�������� ������ 1�������� ����Ǵµ� �ɸ� �ð�(Delta Second)�� ���Ѵ�
	m_fDS = (float)(m_liCurCount.QuadPart - m_liPrevCount.QuadPart) / (float)m_liFreqency.QuadPart;
	
#ifdef _DEBUG
	// ����� ��� ���� ���� 60FPS Ȯ��
	if (m_fDS > (1.f / 60.f))
	{
		m_fDS = 1.f / 60.f;
	}
#endif

	// ���� ī���� ���� �����صд� ( ������ DSüũ�� Ȱ���ϱ� ���ؼ�)
	m_liPrevCount.QuadPart = m_liCurCount.QuadPart;

	// �ð� ���� ( ��� �ð��� ������ ���� �ð��� �����̴� )
	m_fOneSec += m_fDS;


	// ===============================
	//			FPS ���ϱ�
	// ===============================

	m_iFPS++;
	
	// ���� �ð��� 1�ʸ� �Ѵ� ����
	if (m_fOneSec >= 1.f)
	{
		m_fOneSec = m_fOneSec - 1.f;
		m_iElapsedTime++;

		wchar_t szStr[255] = L"";
		wsprintf(szStr, L"FPS: %d || Elapsed time: %d", m_iFPS, m_iElapsedTime);
		SetWindowTextW(CCore::GetInst()->GetMainWndHWND(), szStr);

		m_iFPS = 0;
	}

}