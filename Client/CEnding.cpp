#include "pch.h"
#include "CEnding.h"

#include "CAnimator.h"
#include "CResMgr.h"
#include "CTimeMgr.h"



CEnding::CEnding()
	: m_pImage(nullptr)
	, m_iImageIdx(1)
	, m_fAcctime()
	, m_bSetPlay(true)
{
	AddComponent(new CAnimator);

	m_pImage = CResMgr::GetInst()->LoadImg(L"Ending_1", L"image\\isaac\\Ending\\Ending_1.bmp");
	GetAnimator()->CreateAnimation(L"Ending_1", m_pImage, Vec2(0.f, 0.f), Vec2(128.f, 144.f), Vec2(500.f, 500.f), Vec2(0, 0), 128.f, 2, 0.1);
	m_pImage = CResMgr::GetInst()->LoadImg(L"Ending_2", L"image\\isaac\\Ending\\Ending_2.bmp");
	GetAnimator()->CreateAnimation(L"Ending_2", m_pImage, Vec2(0.f, 0.f), Vec2(128.f, 144.f), Vec2(500.f, 500.f), Vec2(0, 0), 128.f, 2, 0.1);
	m_pImage = CResMgr::GetInst()->LoadImg(L"Ending_3", L"image\\isaac\\Ending\\Ending_3.bmp");
	GetAnimator()->CreateAnimation(L"Ending_3", m_pImage, Vec2(0.f, 0.f), Vec2(128.f, 144.f), Vec2(500.f, 500.f), Vec2(0, 0), 128.f, 2, 0.1);
	m_pImage = CResMgr::GetInst()->LoadImg(L"Ending_4", L"image\\isaac\\Ending\\Ending_4.bmp");
	GetAnimator()->CreateAnimation(L"Ending_4", m_pImage, Vec2(0.f, 0.f), Vec2(128.f, 144.f), Vec2(500.f, 500.f), Vec2(0, 0), 128.f, 2, 0.1);
	m_pImage = CResMgr::GetInst()->LoadImg(L"Ending_5", L"image\\isaac\\Ending\\Ending_5.bmp");
	GetAnimator()->CreateAnimation(L"Ending_5", m_pImage, Vec2(0.f, 0.f), Vec2(128.f, 144.f), Vec2(500.f, 500.f), Vec2(0, 0), 128.f, 2, 0.1);
	m_pImage = CResMgr::GetInst()->LoadImg(L"Ending_6", L"image\\isaac\\Ending\\Ending_6.bmp");
	GetAnimator()->CreateAnimation(L"Ending_6", m_pImage, Vec2(0.f, 0.f), Vec2(128.f, 144.f), Vec2(500.f, 500.f), Vec2(30, 0), 128.f, 2, 0.1);
	m_pImage = CResMgr::GetInst()->LoadImg(L"Ending_Box", L"image\\isaac\\Ending\\Ending_Box.bmp");
	GetAnimator()->CreateAnimation(L"Ending_Box", m_pImage, Vec2(0.f, 0.f), Vec2(88.f, 84.f), Vec2(256.f, 288.f), Vec2(0, 0), 88.f, 4, 0.20);
	m_pImage = CResMgr::GetInst()->LoadImg(L"Ending_background", L"image\\isaac\\Ending\\Ending_background.bmp");
	GetAnimator()->CreateAnimation(L"Ending_background", m_pImage, Vec2(0.f, 0.f), Vec2(321.f, 180.f), Vec2(1280.f, 720.f), Vec2(0, 0), 321.f, 1, 0.1);


}

CEnding::~CEnding()
{
}



void CEnding::tick()
{
	m_fAcctime += DT;
	if (m_bSetPlay) 
	{
		m_bSetPlay = false;
		switch (m_iImageIdx)
		{
		case 1:
			GetAnimator()->Play(L"Ending_1", true);
			
			break;
		case 2:
			GetAnimator()->Play(L"Ending_2", true);
			break;
		case 3:
			GetAnimator()->Play(L"Ending_3", true);
			break;
		case 4:
			GetAnimator()->Play(L"Ending_4", true);
			break;
		case 5:
			GetAnimator()->Play(L"Ending_5", true);
			break;
		case 6:
			GetAnimator()->Play(L"Ending_6", true);
			break;
		case 7:
			GetAnimator()->Play(L"Ending_Box", false);
			break;
		case 8:
			GetAnimator()->Play(L"Ending_background", false);
			break;
		default:
			break;
		}
	}
	
	if (m_fAcctime > 3)
	{
		m_fAcctime = 0;
		if(m_iImageIdx < 6)
		m_iImageIdx += 1;

		if(m_iImageIdx == 7)
			m_iImageIdx = 10;

		if (m_iImageIdx == 8)
			m_iImageIdx = 255;
		m_bSetPlay = true;
	}
		
	CObject::tick();
}

void CEnding::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	if(m_iImageIdx == 10)
		SceneChange(SCENE_TYPE::ENDING);
}

