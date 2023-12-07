#include "pch.h"
#include "CDeadTrace.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CImage.h"


#include "CPlayer.h"
#include "CIsaacTear.h"
#include "CEffect.h"
#include "CSound.h"
#include "CDeadIsaac.h"

static int iCount = 0;

static float Angle = PI / 10;;

static bool TenAngleMode = false;

CDeadTrace::CDeadTrace()	
	: m_pPlayer(nullptr)
	, m_vLightPos()
	, m_vMonsterLookat()
	, m_fAcctime(0)
	, m_fAcctime2(0)
	, m_fAcctime3(0)
	, m_fAcctime4(0)
	, m_tMonsterInfo()
{
}

CDeadTrace::~CDeadTrace()
{
}

void CDeadTrace::enter()
{
	CDeadIsaac* pOwner = dynamic_cast<CDeadIsaac*>(GetOwner());
	assert(pOwner);
	pOwner->SetHPbar();
	// Palyer 를 찾는다
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	m_pPlayer = (CPlayer*)pCurScene->GetObjects(LAYER_TYPE::PLAYER).at(0);
	m_fAcctime = 0;
	m_fAcctime2 = 0;

	Vec2 vCameraPos = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CCamera::GetInst()->GetResolution();
	vCameraPos.x = vCameraPos.x - (vResolution.x / 2) + (WALLW_SIZE / 2) + WALLW_SIZE;
	vCameraPos.y = vCameraPos.y - (vResolution.y / 2) + 15 + WALLH_SIZE;

	m_vLightPos = vCameraPos;
	m_vMonsterLookat = vCameraPos;

	m_tMonsterInfo = pOwner->GetInfo();
	pOwner->GetAnimator()->Play(L"DeadIsaac_nomal", true);
	


	/*CImage* m_pImage = CResMgr::GetInst()->LoadImg(L"DeadIsaac", L"image\\isaac\\Monster\\DeadIsaac.bmp");

	pOwner->GetAnimator()->CreateAnimation(L"DeadIsaac_stand", m_pImage, Vec2(0.f, 0.f), Vec2(64.f, 58.f), Vec2(100.f, 128.f), Vec2(-32.f, 0.f), 64.f, 4, 0.15f);*/
	//pOwner->GetAnimator()->Play(L"DeadIsaac_nomal", true);
}

void CDeadTrace::tick()
{
	m_fAcctime += DT;
	m_fAcctime2 += DT;
	m_fAcctime3 += DT;
	m_fAcctime4 += DT;

	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);

	m_tMonsterInfo = pOwner->GetInfo();

	if (TenAngleMode)
	{
		if (m_fAcctime3 > 0.075f)
		{
			TearModeTen();
			m_fAcctime3 = 0;
			iCount += 1;

		}
		if (iCount > 3)
		{
			TenAngleMode = false;
			m_fAcctime3 = 0;
			iCount = 0;
			Angle += PI / 6;

		}

	}


	if (m_fAcctime > 0.92)
	{
		TearModeOne();

		m_fAcctime = 0;
	}
	if (m_fAcctime2 > 1.92)
	{
		TearModeThree();
		CSound* pBgm = CResMgr::GetInst()->FindSound(L"Boss_Scared");
		if (nullptr != pBgm)
			pBgm->Play(false);

		m_fAcctime2 = 0;
	}
	if (m_fAcctime3 > 3.0)
	{
		TenAngleMode = true;

	}
	if (m_tMonsterInfo.fCurHP < 150.f)
	{
		GetAI()->ChangeState(L"DEADTRACE2");
		m_fAcctime4 = 0;
	}
}

	

void CDeadTrace::exit()
{
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);
	pOwner->GetAnimator()->Play(L"DeadIsaac_stand", true);

	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Boss_Patten");
	if (nullptr != pBgm)
		pBgm->Play(false);
}

void CDeadTrace::TearModeOne()
{
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);

	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Boss_Tear");
	if (nullptr != pBgm)
		pBgm->Play(false);

	Vec2 vMonPos = pOwner->GetPos();
	Vec2 vPlayerPos = m_pPlayer->GetPos();
	vPlayerPos.x = vPlayerPos.x - 50;
	vPlayerPos.y = vPlayerPos.y - 50;
	Vec2 vDir = vPlayerPos - vMonPos;
	vDir.Normalize();

	CIsaacTear* pMissile = Instantiate<CIsaacTear>(pOwner->GetPos() + Vec2(-20.f, 60.f), LAYER_TYPE::MONSTER_PROJECTILE);
	pMissile->SetPlayerMode(Effect::TEARM);
	pMissile->SetVecterMode(false);
	pMissile->SetMonsterTear(vDir);
	
}

void CDeadTrace::TearModeThree()
{
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);

	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Boss_Tear");
	if (nullptr != pBgm)
		pBgm->Play(false);
	
	for (size_t i = 0; i < 3; i++)
	{
		Vec2 vMonPos = pOwner->GetPos();
		Vec2 vPlayerPos = m_pPlayer->GetPos();

		vPlayerPos.x = vPlayerPos.x - 150;
		vPlayerPos.y = vPlayerPos.y - 150;

		vPlayerPos.x = vPlayerPos.x + i * 100;
		vPlayerPos.y = vPlayerPos.y + i * 100;
		

		Vec2 vDir = vPlayerPos - vMonPos;
		vDir.Normalize();
		CIsaacTear* pMissile = Instantiate<CIsaacTear>(pOwner->GetPos() + Vec2(-20.f, 60.f), LAYER_TYPE::MONSTER_PROJECTILE);
		pMissile->SetPlayerMode(Effect::TEARM);
		pMissile->SetVecterMode(false);
		pMissile->SetMonsterTear(vDir);
	}
	
	
}

void CDeadTrace::TearModeTen()
{
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);

	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Boss_Tear");
	if (nullptr != pBgm)
		pBgm->Play(false);

	for (size_t i = 0; i < 10; i++)
	{

		CIsaacTear* pMissile = Instantiate<CIsaacTear>(pOwner->GetPos() + Vec2(-20.f, 60.f), LAYER_TYPE::MONSTER_PROJECTILE);
		pMissile->SetPlayerMode(Effect::TEARM);
		pMissile->SetTearAngle(Vec2(1 * cosf(Angle), 1.f * sinf(Angle)));
		
		Angle += PI / 5;
	}
	
}




