#include "pch.h"
#include "CDeadTrace2.h"

#include "CTimeMgr.h"
#include "CEffect.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CIsaacTear.h"
#include "CScene.h"
#include "CSceneMgr.h"

#include "CComponent.h"
#include "CCollider.h"
#include "CSound.h"
#include "CResMgr.h"




CDeadTrace2::CDeadTrace2()
	: m_pPlayer(nullptr)
	, m_vLightPos()
	, m_vMonsterLookat()
	, m_fAcctime(0)
	, Angle(PI / 10)
	, iCount(0)
	, TenAngleMode(false)

{
}

CDeadTrace2::~CDeadTrace2()
{
}

void CDeadTrace2::enter()
{

	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);

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


	
}

void CDeadTrace2::tick()
{

	m_fAcctime += DT;
	m_fAcctime2 += DT;
	m_fAcctime3 += DT;
	m_fAcctime4 += DT;

	Angle2 += PI / 5;

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
	else
	{
		if (m_fAcctime > 0.92)
		{
			TearModeOne();

			m_fAcctime = 0;
		}
		if (m_fAcctime2 > 1.92)
		{
			TearModeThree();
			TearModeTened();
			CSound* pBgm = CResMgr::GetInst()->FindSound(L"Boss_Scared");
			if (nullptr != pBgm)
				pBgm->Play(false);

			m_fAcctime2 = 0;
		}
		if (m_fAcctime3 > 3.0)
		{
			CSound* pBgm = CResMgr::GetInst()->FindSound(L"Boss_Scared2");
			if (nullptr != pBgm)
				pBgm->Play(false);

			TenAngleMode = true;

		}
	}

	if (m_fAcctime4 > 5 && m_tMonsterInfo.fCurHP < 100.f)
	{
		GetAI()->ChangeState(L"DEADTRACE3");
		m_fAcctime4 = 0;
	}
	if (m_vLightPos.y > m_vMonsterLookat.y + WALLH_SIZE * 7 && m_vLightPos.x > m_vMonsterLookat.x + WALLW_SIZE * 12)
	{

		//m_vLightPos = m_vMonsterLookat;
		//GetAI()->ChangeState(L"DEADTRACE");
		m_vLightPos = m_vMonsterLookat;
	}
	

}

void CDeadTrace2::exit()
{
	m_vLightPos = m_vMonsterLookat;
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);
	pOwner->GetAnimator()->Play(L"DeadIsaac_teleport", false);

	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Boss_Patten");
	if (nullptr != pBgm)
		pBgm->Play(false);
}



void CDeadTrace2::RightColumn()
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

void CDeadTrace2::CreateRightColumn(int _fwpos, int _fhpos)
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

void CDeadTrace2::TearModeOne()
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

void CDeadTrace2::TearModeThree()
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

void CDeadTrace2::TearModeTen()
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
void CDeadTrace2::TearModeTened()
{
	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());
	assert(pOwner);

	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Boss_Tear");
	if (nullptr != pBgm)
		pBgm->Play(false);

	Vec2 vMonPos = pOwner->GetPos();
	Vec2 vPlayerPos = m_pPlayer->GetPos();
	
	Vec2 vDir = vPlayerPos - vMonPos;
	vDir.Normalize();

	CIsaacTear* pMissile = Instantiate<CIsaacTear>(pOwner->GetPos() + Vec2(-20.f, 60.f), LAYER_TYPE::MONSTER_PROJECTILE);
	pMissile->SetPlayerMode(Effect::TEARM);
	pMissile->SetVecterMode(false);
	pMissile->SetMonsterTear(vDir);
	pMissile->SetAutoTear(true);

	pMissile = Instantiate<CIsaacTear>(pOwner->GetPos() + Vec2(-20.f, 60.f), LAYER_TYPE::MONSTER_PROJECTILE);
	pMissile->SetPlayerMode(Effect::TEARM);
	pMissile->SetVecterMode(false);
	pMissile->SetMonsterTear(vDir);
	pMissile->SetAutoTear(true);
}
