#include "pch.h"
#include "CAngel.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CAnimator.h"
#include "CCollider.h"
#include "CAI.h"

#include "CIdle.h"
#include "CAngelTrance.h"
#include "CTelePortTrance2.h"

CAngel::CAngel()
	: m_pImage(nullptr)
{
	tMonsterInfo& m_info = CMonster::GetInfo1();
	m_info.fDetectRange = 1000.f;
	m_info.fSpeed = 200.f;
	m_info.fCurHP = 50.f;
	m_info.fMaxHP = 50.f;


	AddComponent(new CAnimator);
	AddComponent(new CCollider);
	AddComponent(new AI);

	GetCollider()->SetScale(Vec2(32.f, 25.f));
	GetCollider()->SetOffset(Vec2(-32.f, 0.f));

	m_pImage = CResMgr::GetInst()->LoadImg(L"AngelMonster", L"image\\isaac\\Monster\\Angel.bmp");
	GetAnimator()->CreateAnimation(L"Angel_nomal", m_pImage, Vec2(0, 0), Vec2(32.f, 32.f), Vec2(79.f, 52.f), Vec2(-55.f, -30.f), 32.f, 4, 0.15);
	GetAnimator()->CreateAnimation(L"Angel_attack", m_pImage, Vec2(11, 32), Vec2(40.f, 32.f), Vec2(87.f, 69.f), Vec2(-55.f, -30.f), 32.f, 1, 0.1);

	GetAnimator()->Play(L"Angel_nomal", true);

	m_pImage = CResMgr::GetInst()->LoadImg(L"boss_Intro", L"image\\isaac\\Map\\IsaacVSIsaac.bmp");
	GetAnimator()->CreateAnimation(L"EMPTY", m_pImage, Vec2(10.f, 10.f), Vec2(10, 10), Vec2(0, 0), Vec2(0.f, 0.f), 0, 1, 0.20f);

	GetAI()->AddState(L"IDLE", new CIdle);
	GetAI()->AddState(L"ATTACK", new CAngelTrance);
	GetAI()->AddState(L"TP", new CTelePortTrance2);
	GetAI()->ChangeState(L"IDLE");
}

CAngel::~CAngel()
{
}

void CAngel::tick()
{
	tMonsterInfo& m_info = CMonster::GetInfo1();

	if (m_info.fCurHP <= 0)
	{
		CSound* pBgm = CResMgr::GetInst()->FindSound(L"Monster_Hurt");
		if (nullptr != pBgm)
			pBgm->Play(false);

		DeleteObject(this);
	}

	CMonster::tick();


}

