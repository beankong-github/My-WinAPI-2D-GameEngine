#pragma once

class CTexture;

enum class ECAM_EFFECT
{
	NONE,
	FADEIN,
	FADEOUT,
	VIBRATE,


	END
};

class CCamera
{
	SINGLE(CCamera)

private:
	Vec			m_vLookAt;
	Vec			m_vDiff;		// �ػ� �߾� ������ ī�޶� �����ִ� ���� ����
	CTexture*	m_pVeilTex;

	// EFFECT
	ECAM_EFFECT m_eEffect;
	float		m_fEffectTime;
	float		m_fAddTime;		// �����ð�

	// EFFECT :: FADE
	float		m_fAlpha;		// 0 ~ 1

	// EFFECT :: VIBRATE
	float		m_fRange;
	float		m_fSpeed;
	EDIRECTION	m_eVibDir;
	Vec			m_vOriginLookAt;


public:
	void Init();
	void Update();
	void Render(HDC _dc);

public:
	Vec GetRenderPos(Vec _vPos) { return _vPos - m_vDiff; }

public:
	void FadeIn(float _fTime)
	{
		m_eEffect = ECAM_EFFECT::FADEIN;
		m_fEffectTime = _fTime;
		m_fAlpha = 1.f;
		m_fAddTime = 0.f;
	}

	// ���� ��ο����� ȿ��
	void FadeOut(float _fTime)
	{
		m_eEffect = ECAM_EFFECT::FADEOUT;
		m_fEffectTime = _fTime;
		m_fAlpha = 0.f;
		m_fAddTime = 0.f;
	}

	// ���� ȿ��
	void Vibration(float _fRange/*����*/, float _fTime/*���������ð�*/, float _fSpeed/*�����ӵ�*/, EDIRECTION _dir /*��������*/)
	{
		m_eEffect = ECAM_EFFECT::VIBRATE;
		m_fRange = _fRange;
		m_fEffectTime = _fTime;
		m_fSpeed = _fSpeed;
		m_eVibDir = _dir;
		m_vOriginLookAt = m_vLookAt;
		m_fAddTime = 0.f;
	}
};

