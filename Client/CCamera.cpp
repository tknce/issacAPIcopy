#include "pch.h"
#include "CCamera.h"
#include "CEngine.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CObject.h"
#include "CImage.h"


CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_pVeil(nullptr)
	, m_fAlpha(0.f)	
	, m_Score(0)
{	
	POINT ptResol = CEngine::GetInst()->GetResolution();
	m_pVeil = CResMgr::GetInst()->CreateImg(L"Veil", ptResol.x, ptResol.y);
}

CCamera::~CCamera()
{
}

void CCamera::init()
{
	m_vResolution = CEngine::GetInst()->GetResolution();
	m_vLook = (m_vResolution / 2.f);
}

void CCamera::tick()
{	
	
	
	if (IsPressed(KEY_TYPE::NUM_8))
	{
		m_vLook.y -= DT * 500.f;
	}
	if (IsPressed(KEY_TYPE::NUM_5))
	{
		m_vLook.y += DT * 500.f;
	}
	if (IsPressed(KEY_TYPE::NUM_4))
	{
		m_vLook.x -= DT * 500.f;
	}
	if (IsPressed(KEY_TYPE::NUM_6))
	{
		m_vLook.x += DT * 500.f;
	}

	if (m_pTargetObj != nullptr)
	{
		m_vLook = m_pTargetObj->GetPos();
	}

	
	// 처리할 카메라 효과가 있으면
	if (!m_CamEffectInfo.empty())
	{
		tCamEffectInfo& info = m_CamEffectInfo.front();

		info.fAccTime += DT;
		float fRatio = (info.fAccTime / info.fDuration);	// 제한 시간 대비 진행시간의 비율을 0 ~ 1 사이로 환산

		if (1.f <= fRatio)
		{
			fRatio = 1.f;
			m_CamEffectInfo.pop_front();
		}

		else
		{
			if (CAM_EFFECT::FADE_IN == info.eEffect)
				m_fAlpha = 1.f - fRatio;
			else if (CAM_EFFECT::FADE_OUT == info.eEffect)
				m_fAlpha = fRatio;
			else
				m_fAlpha = 0.f;
		}


	}
	//Vec2 a;
	//CamaradurationWiggle(a, 1.f, 1000.f);

	m_vDiff = m_vLook - (m_vResolution / 2.f);


}

void CCamera::render(HDC _dc)
{
	if (0.f == m_fAlpha)
		return;

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = 0;
	tFunc.SourceConstantAlpha = (BYTE)(255.f * m_fAlpha);

	AlphaBlend(_dc, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, m_pVeil->GetDC()
		, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, tFunc);

	//스코어 창


	/*wchar_t szFloat[50] = {};


	swprintf_s(szFloat, 50, L"Score : %d", m_Score);
	int iLen = (int)wcsnlen_s(szFloat, 50);
	TextOut(_dc, 10, 10, szFloat, iLen);*/

}


void CCamera::CamaradurationWiggle(Vec2 _WigglePos, float Duration, float WigglePower)
{
	_WigglePos = m_vLook;

	if (Wiggletime <= Duration)
	{
		Wiggletime += DT;
		CamaraWiggle(WigglePower);
	}

	else
	{
		m_vLook = _WigglePos;
	}


}

void CCamera::CamaraWiggle(float WigglePower)
{


	if (m_shake < 0.1)
	{
		m_shake += DT;
		m_vLook.y -= DT * WigglePower;
	}
	else if (m_shake < 0.2)
	{
		m_shake += DT;
		m_vLook.y -= DT * -WigglePower;
	}
	else
	{
		m_shake = 0;
	}

}
