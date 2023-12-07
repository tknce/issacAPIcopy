#include "pch.h"
#include "CEffect.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CImage.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CSound.h"

#include "CPlayer.h"






CEffect::CEffect()
	: m_Image(nullptr)
	, m_fAcctime(0.f)
	, m_Type()
{
	AddComponent(new CAnimator);
	AddComponent(new CCollider);
	GetCollider()->SetScale(Vec2(0, 0));
	m_Image = CResMgr::GetInst()->LoadImg(L"MonsterTDAtlas", L"image\\isaac\\Tears\\MonsterTearsDestoryAtlas.bmp");
	GetAnimator()->CreateAnimation(L"MonsterTDAtlas1", m_Image, Vec2(0.f, 0.f), Vec2(63.f, 63.f), Vec2(100.f, 100.f), Vec2(0.f, -45.f), 63.f, 16, 0.03f);
	m_Image = CResMgr::GetInst()->LoadImg(L"PlayerTDAtlas", L"image\\isaac\\Tears\\TearsDestoryAtlas.bmp");
	GetAnimator()->CreateAnimation(L"PlayerTDAtlas", m_Image, Vec2(0.f, 0.f), Vec2(63.f, 63.f), Vec2(100.f, 100.f), Vec2(0.f, -45.f), 63.f, 16, 0.03f);
	m_Image = CResMgr::GetInst()->LoadImg(L"LightColumn2", L"image\\isaac\\Effect\\LightColumn2.bmp");
	GetAnimator()->CreateAnimation(L"LightColumn", m_Image, Vec2(0.f, 0.f), Vec2(32.f, 360.f), Vec2(100.f, 720.f), Vec2(5.f, -483.f), 64.f, 10, 0.1f, true, 150);
	m_Image = CResMgr::GetInst()->LoadImg(L"Light", L"image\\isaac\\Effect\\Light.bmp");
	GetAnimator()->CreateAnimation(L"Light", m_Image, Vec2(0.f, 0.f), Vec2(96.f, 256.f), Vec2(150.f, 700.f), Vec2(-30.f, -450.f), 63.f, 1, 0.03f,true,false, 125 );
	//GetAnimator()->Play(L"MonsterTDAtlas1", false);
}

CEffect::~CEffect()
{
	
}

void CEffect::tick()
{
	

	if (m_Type == Effect::LIGHT)
	{
		m_fAcctime += DT;
		GetAnimator()->Play(L"Light", false);
		CObject::tick();
		return;
	}
		

	if (m_fAcctime >= 0)
	{
		if (m_fAcctime == 0)
		{
			switch (m_Type)
			{
			case Effect::TEARM:
				GetAnimator()->Play(L"MonsterTDAtlas1", false);
				break;
			case Effect::TEARP:
				GetAnimator()->Play(L"PlayerTDAtlas", false);
				break;
			case Effect::LIGHTCOLUMN:
				GetAnimator()->Play(L"LightColumn", false);
				break;
			case Effect::LIGHT:

				break;
			case Effect::END:
				break;
			default:
				break;
			}
		}


		m_fAcctime += DT;

		if (m_fAcctime > 0.5f)
		{
			DeleteObject(this);
			m_fAcctime = -1;
		}
		CObject::tick();
	}
	
	
}

void CEffect::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;

	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Teleport");

	switch (m_Type)
	{
	case Effect::TEARM:
		
	case Effect::TEARP:
		
	case Effect::LIGHTCOLUMN:
		pPlayer->Demage();
		break;

	case Effect::LIGHT:
		pPlayer->SetUniquefalse();
		pPlayer->GetAnimator()->Play(L"TelePort",false);
		
		if (nullptr != pBgm)
			pBgm->Play(false);
		m_fAcctime = 0;

		
		
		break;
	case Effect::END:
		break;
	default:
		break;
	}
}

void CEffect::CollisionOverlap(CCollider* _pOtherCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;
	Vec2 Playepos = pPlayer->GetPos();
	switch (m_Type)
	{
	case Effect::TEARM:
		break;
	case Effect::TEARP:
		break;
	case Effect::LIGHTCOLUMN:

		break;

	case Effect::LIGHT:
		//pPlayer->SetUniquefalse();	
		Playepos.y -= 150 * DT;
		pPlayer->SetPos(Playepos);
		if (m_fAcctime > 1.0f)
			SceneChange(SCENE_TYPE::STAGE_01);
		break;
	case Effect::END:
		break;
	default:
		break;
	}
}

void CEffect::CollisionEndOverlap(CCollider* _pOhterCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOhterCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;
	Vec2 Playepos = pPlayer->GetPos();
	switch (m_Type)
	{
	case Effect::TEARM:
		break;
	case Effect::TEARP:
		break;
	case Effect::LIGHTCOLUMN:

		break;

	case Effect::LIGHT:
		
		break;
	case Effect::END:
		break;
	default:
		break;
	}
}

