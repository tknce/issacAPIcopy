#include "pch.h"
#include "CDeadIsaac.h"

#include "CAnimator.h"
#include "CAnimation.h"
#include "CCollider.h"
#include "CResMgr.h"
#include "CAI.h"
#include "CSound.h"
#include "CKeyMgr.h"

#include "CIdle.h"
#include "CTrace.h"
#include "CDeadTrace.h"
#include "CDeadTrace2.h"
#include "CDeadTrace3.h"
#include "CTeleportTrance.h"
#include "CDeadDEAD.h"
#include "CMonster_HPbar.h"

CDeadIsaac::CDeadIsaac()
	: m_pImage(nullptr)
	, m_Monster_HPbar(nullptr)
	, m_Monster_HP(nullptr)
{
	tMonsterInfo&  m_info = CMonster::GetInfo1();
	m_info.fDetectRange = 600.f;
	m_info.fSpeed = 200.f;
	m_info.fCurHP = 200.f;
	m_info.fMaxHP = 200.f;
	

	AddComponent(new CAnimator);
	AddComponent(new CCollider);
	AddComponent(new AI);

	GetCollider()->SetScale(Vec2(32.f, 47.f));
	GetCollider()->SetOffset(Vec2(0.f,79.f));
	

	m_pImage = CResMgr::GetInst()->LoadImg(L"DeadIsaac", L"image\\isaac\\Monster\\DeadIsaac.bmp");

	GetAnimator()->CreateAnimation(L"DeadIsaac", m_pImage, Vec2(0.f, 235.f), Vec2(64.f, 58.f), Vec2(128.f, 128.f), Vec2(-32.f, 0.f), 64.f, 4, 0.15f);
	GetAnimator()->CreateAnimation(L"DeadIsaac_nomal", m_pImage, Vec2(128.f, 58.f), Vec2(64.f, 58.f), Vec2(128.f, 128.f), Vec2(-32.f, 0.f), 64.f, 1, 0.15f);
	GetAnimator()->CreateAnimation(L"DeadIsaac_stand", m_pImage, Vec2(0.f, 0.f), Vec2(64.f, 58.f), Vec2(100.f, 128.f), Vec2(-16.f, 0.f), 64.f, 4, 0.20f); 

	m_pImage = CResMgr::GetInst()->LoadImg(L"boss_Intro", L"image\\isaac\\Map\\IsaacVSIsaac.bmp");
	GetAnimator()->CreateAnimation(L"boss_Intro", m_pImage, Vec2(0.f, 0.f), Vec2(1280.f, 720.f), Vec2(1280.f, 720.f), Vec2(0.f, 0.f), 1280.f, 1, 0.20f);
	GetAnimator()->CreateAnimation(L"EMPTY", m_pImage, Vec2(10.f, 10.f), Vec2(10, 10), Vec2(0, 0), Vec2(0.f, 0.f), 0, 1, 0.20f);
	m_pImage = CResMgr::GetInst()->LoadImg(L"DeadIsaac_teleport", L"image\\isaac\\Monster\\DeadIsaac_teleport.bmp");
	GetAnimator()->CreateAnimation(L"DeadIsaac_teleport", m_pImage, Vec2(0.f, 0.f), Vec2(80.f, 59.f), Vec2(170.f, 150.f), Vec2(-30.f, 0.f), 80.f, 3, 0.20f);

	GetAnimator()->Play(L"DeadIsaac_nomal", true);

	GetAI()->AddState(L"IDLE", new CIdle);
	GetAI()->AddState(L"TRACE", new CTrace);
	GetAI()->AddState(L"DEADTRACE", new CDeadTrace);
	GetAI()->AddState(L"DEADTRACE2", new CDeadTrace2);
	GetAI()->AddState(L"DEADTRACE3", new CDeadTrace3);
	GetAI()->AddState(L"CTELEPORT", new CTeleportTrance);
	GetAI()->AddState(L"CDeadDEAD", new CDeadDEAD);
	
	GetAI()->ChangeState(L"IDLE");

	

}

CDeadIsaac::~CDeadIsaac()
{
}

void CDeadIsaac::tick()
{
	tMonsterInfo& m_info = CMonster::GetInfo1();

	if (m_info.fCurHP <= 0)
	{
		CSound* pBgm = CResMgr::GetInst()->FindSound(L"PlayerDie");
		if (nullptr != pBgm)
			pBgm->Play(false);

		GetAI()->ChangeState(L"CDeadDEAD");
		DeleteObject(this);
		DeleteObject(m_Monster_HP);
		DeleteObject(m_Monster_HPbar);
	}
	if (IsTap(KEY_TYPE::M))
	{
		GetAI()->ChangeState(L"CDeadDEAD");
		DeleteObject(this);
		DeleteObject(m_Monster_HP);
		DeleteObject(m_Monster_HPbar);
	}

	CMonster::tick();
}

void CDeadIsaac::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
}

void CDeadIsaac::SetHPbar()
{
	m_Monster_HP = Instantiate<CMonster_HPbar>(Vec2(490, 50), LAYER_TYPE::ETCUI);
	m_Monster_HPbar = Instantiate<CMonster_HPbar>(Vec2(0, 0), LAYER_TYPE::ETCUI);
	m_Monster_HPbar->SetHeigth();
}
