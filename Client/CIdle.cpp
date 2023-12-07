#include "pch.h"
#include "CIdle.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "CDeadIsaac.h"
#include "CAngel.h"
#include "CSound.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CDeadIsaac.h"
#include "CAnimator.h"


CIdle::CIdle()
{
}

CIdle::~CIdle()
{
}



void CIdle::enter()
{
	// Palyer 를 찾는다
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	m_pPlayer = (CPlayer*)pCurScene->GetObjects(LAYER_TYPE::PLAYER).at(0);
	m_fAcctime = 0;
	m_bSound = true;
}

void CIdle::tick()
{
	// Monster 의 정보를 확인한다.
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);
	float fDetectRange = pOwner->GetInfo().fDetectRange;
	float fDistance = (m_pPlayer->GetPos() - pOwner->GetPos()).Length();

	m_fAcctime += DT;

	// Player 와 IdleState 의 소유 몬스터의 거리 차이가 몬스터의 탐지범위 이내라면
	if (fDistance < fDetectRange)
	{
		// 상태변경
		if (pOwner == (dynamic_cast<CDeadIsaac*>(pOwner)))
		{

			if (m_bSound)
			{
				CSound* pBgm = CResMgr::GetInst()->FindSound(L"Boss_Enter");
				if (nullptr != pBgm)
					pBgm->Play(false);
				pOwner->GetAnimator()->Play(L"boss_Intro", false);
				m_bSound = false;
			}
			

			if(m_fAcctime > 2)
			GetAI()->ChangeState(L"DEADTRACE");

			return;

		}
		if (pOwner == (dynamic_cast<CAngel*>(pOwner)))
			GetAI()->ChangeState(L"ATTACK");
	}

	m_fAcctime = 0;
}

void CIdle::exit()
{
}

