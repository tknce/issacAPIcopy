#include "pch.h"
#include "CMain.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CKeyMgr.h"
#include "CSound.h"

#include "CAnimator.h"



CMain::CMain()
	: m_CMainImage(nullptr)
	, m_VImage()
	, m_bnext(false)
	, m_bIntro(false)
{
	
	AddComponent(new CAnimator);

	m_CMainImage = CResMgr::GetInst()->LoadImg(L"START", L"image\\isaac\\Map\\Start1.bmp");
	GetAnimator()->CreateAnimation(L"START", m_CMainImage,Vec2(0,0),Vec2(480.f,272.f) ,Vec2(1280,720) ,Vec2(240,136) ,480.f ,2 , 0.3f);
	m_CMainImage = CResMgr::GetInst()->LoadImg(L"Main", L"image\\isaac\\Map\\Main.bmp");
	GetAnimator()->CreateAnimation(L"Main", m_CMainImage, Vec2(0, 0), Vec2(321, 180), Vec2(1280, 720), Vec2(160, 90), 0.f, 1, 0.3f);

	m_CMainImage = CResMgr::GetInst()->LoadImg(L"Start_intro", L"image\\isaac\\Map\\Next_Scene.bmp");
	GetAnimator()->CreateAnimation(L"Start_intro", m_CMainImage, Vec2(0, 0), Vec2(1280, 720), Vec2(1280, 720), Vec2(640, 360), 0.f, 1, 0.3f);

	GetAnimator()->Play(L"START",true);
}

CMain::~CMain()
{
}

void CMain::tick()
{
	if (!m_bnext)
	{
		if (IsTap(KEY_TYPE::ENTER))
		{


			m_bnext = true;
			GetAnimator()->Play(L"Main", false);


		}
	}
	if (IsTap(KEY_TYPE::SPACE))
	{
		m_bIntro = true;
	}
	if (m_bIntro)
	{
		GetAnimator()->Play(L"Start_intro", false);
	}

	CObject::tick();
}

