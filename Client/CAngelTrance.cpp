#include "pch.h"
#include "CAngelTrance.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CTimeMgr.h"
#include "CAnimator.h"
#include "CSound.h"
#include "CResMgr.h"

#include "CPlayer.h"
#include "CIsaacTear.h"

CAngelTrance::CAngelTrance()
	: m_fAcctime(0)
	, m_fAcctime2(0)
	, m_pPlayer(nullptr)
	, m_tMonsterInfo()
{
}

CAngelTrance::~CAngelTrance()
	
{
}


void CAngelTrance::enter()
{
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);

	// Palyer 를 찾는다
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	m_pPlayer = (CPlayer*)pCurScene->GetObjects(LAYER_TYPE::PLAYER).at(0);

	m_tMonsterInfo = pOwner->GetInfo();

	m_fAcctime = 2;
	m_fAcctime2 = 0;
	
	pOwner->GetAnimator()->Play(L"Angel_nomal", true);
	
}

void CAngelTrance::tick()
{
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);

	m_tMonsterInfo = pOwner->GetInfo();

	m_fAcctime += DT;
	m_fAcctime2 += DT;

	if (m_fAcctime > 2.5)
	{
		CSound* pBgm = CResMgr::GetInst()->FindSound(L"Monster_Attack");
		if (nullptr != pBgm)
			pBgm->Play(false);

		pOwner->GetAnimator()->Play(L"Angel_attack", false);
	}

	if (m_fAcctime > 3)
	{
		CSound* pBgm = CResMgr::GetInst()->FindSound(L"Roar");
		if (nullptr != pBgm)
			pBgm->Play(false);

		TearModeThree();
		pOwner->GetAnimator()->Play(L"Angel_nomal", true);
		m_fAcctime = 0;
	}
	if (m_fAcctime2 > 3.5)
	{
		CSound* pBgm = CResMgr::GetInst()->FindSound(L"Teleport");
		if (nullptr != pBgm)
			pBgm->Play(false);
		
		pOwner->GetAnimator()->Play(L"EMPTY", false);
		
	}
	if (m_fAcctime2 > 3.5)
	{
		
		GetAI()->ChangeState(L"TP");
	}
}

void CAngelTrance::exit()
{
	m_fAcctime = 0;
	m_fAcctime2 = 0;
}

void CAngelTrance::TearModeThree()
{
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);



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
		CIsaacTear* pMissile = Instantiate<CIsaacTear>(pOwner->GetPos() + Vec2(-40.f, 0.f), LAYER_TYPE::MONSTER_PROJECTILE);
		pMissile->SetPlayerMode(Effect::TEARM);
		pMissile->SetVecterMode(false);
		pMissile->SetMonsterTear(vDir);
	}
}




