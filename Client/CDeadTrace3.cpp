#include "pch.h"
#include "CDeadTrace3.h"

#include "CCollider.h"
#include "CCamera.h"
#include "CAnimator.h"
#include "CTimeMgr.h"
#include "CSound.h"
#include "CResMgr.h"

#include "CEffect.h"



CDeadTrace3::CDeadTrace3()
{
}

CDeadTrace3::~CDeadTrace3()
{
}


void CDeadTrace3::enter()
{
	Vec2 vCameraPos = CCamera::GetInst()->GetLookAt();
	Vec2 vResolution = CCamera::GetInst()->GetResolution();
	vCameraPos.x = vCameraPos.x - (vResolution.x / 2) + (WALLW_SIZE / 2) + WALLW_SIZE;
	vCameraPos.y = vCameraPos.y - (vResolution.y / 2) + 15 + WALLH_SIZE;

	m_vLightPos = vCameraPos;
	m_vMonsterLookat = vCameraPos;

	m_fAcctime = 0;
	m_iCount = 0;
	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Teleport");
	if (nullptr != pBgm)
		pBgm->Play(false);
	
}

void CDeadTrace3::tick()
{
	m_fAcctime += DT;

	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);
	Vec2 Pos = pOwner->GetPos();
	Pos.y -= 1000 * DT;
	pOwner->SetPos(Pos);

	if (m_fAcctime > 0.4)
	{
		if (m_iCount < 10)
		{
			CSound* pBgm = CResMgr::GetInst()->FindSound(L"Light");
			if (nullptr != pBgm)
				pBgm->Play(false);
			pBgm->SetVolume(20);
			m_iCount += 1;
		}


		pOwner->GetAnimator()->Play(L"EMPTY", false);
		
		RightColumn();
		m_fAcctime = 0;
	}
	else
	{
		CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
		assert(pOwner);
		Vec2 Pos = pOwner->GetPos();
		Pos.y -= 1000 * DT;
		pOwner->SetPos(Pos);

		

	}
	
	if (m_vLightPos.y > m_vMonsterLookat.y + WALLH_SIZE * 7 && m_vLightPos.x > m_vMonsterLookat.x + WALLW_SIZE * 12)
	{
		
		//m_vLightPos = m_vMonsterLookat;
		//GetAI()->ChangeState(L"DEADTRACE");
		m_vLightPos = m_vMonsterLookat;
		GetAI()->ChangeState(L"CTELEPORT");
		m_iCount = 0;
	}
	
}

void CDeadTrace3::exit()
{

	m_vLightPos = m_vMonsterLookat;
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);
	pOwner->GetAnimator()->Play(L"DeadIsaac", true);
}

void CDeadTrace3::RightColumn()
{

	CreateRightColumn(0, 0);

	if (m_vLightPos.x >= m_vMonsterLookat.x + WALLW_SIZE * 2)
	{
		CreateRightColumn(1, -1);
		CreateRightColumn(-1, 1);
		if (m_vLightPos.x >= m_vMonsterLookat.x + WALLW_SIZE * 3)
		{
			CreateRightColumn(-2, 2);
			CreateRightColumn(2, -2);
			if (m_vLightPos.x >= m_vMonsterLookat.x + WALLW_SIZE * 4)
			{
				CreateRightColumn(2, -2);
				CreateRightColumn(3, -3);
				CreateRightColumn(-3, 3);
			}
			if (m_vLightPos.x >= m_vMonsterLookat.x + WALLW_SIZE * 5)
			{
				CreateRightColumn(3, -3);
				CreateRightColumn(4, -4);
			}
			if (m_vLightPos.x >= m_vMonsterLookat.x + WALLW_SIZE * 6)
			{
				CreateRightColumn(5, -5);
			}

		}
	}
	m_vLightPos.x += WALLW_SIZE;
	m_vLightPos.y += WALLH_SIZE;


}

void CDeadTrace3::CreateRightColumn(int _fwpos, int _fhpos)
{
	Vec2 create;
	create.x = m_vLightPos.x / WALLW_SIZE;
	create.y = m_vLightPos.y / WALLH_SIZE;

	if (m_vLightPos.x + (_fwpos * WALLW_SIZE) < m_vMonsterLookat.x + WALLW_SIZE * 13 && m_vLightPos.y + (_fhpos * WALLW_SIZE) < m_vMonsterLookat.y + WALLH_SIZE * 7 + 20)
	{
		CEffect* LightColumn = Instantiate<CEffect>(Vec2(m_vLightPos.x + (_fwpos * WALLW_SIZE), m_vLightPos.y + (_fhpos * WALLH_SIZE)), LAYER_TYPE::MONSTER_PROJECTILE);
		LightColumn->SetTypeBool(Effect::LIGHTCOLUMN);
		LightColumn->GetCollider()->SetScale(Vec2(WALLW_SIZE, WALLH_SIZE));
		LightColumn->GetCollider()->SetOffset(Vec2(WALLW_SIZE / 2, WALLH_SIZE / 2));
	}
}




