#include "pch.h"
#include "CIsaacTear.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CResMgr.h"
#include "CImage.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSound.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CTile.h"


#include "CMonster.h"
#include "CPlayer.h"
#include "CEffect.h"
#include "CMonster_HPbar.h"
#include "CDeadIsaac.h"

CIsaacTear::CIsaacTear()
	: m_PlayerInfo()
	, m_pPlayer(nullptr)
	, m_pTearImage(nullptr)
	, m_pTearTDImage(nullptr)
	, m_fTearColliderOffset(5.f,21.f)
	, m_fAccTime(0)
	, m_fTearAngle()
	, m_VMonsterTear(1.f,1.f)
	, m_fRotateSpeed(0)
	, m_fDetectRange(0)
	, m_fRotateTear(0)
	, m_fTearpos(0)
	, m_bAutoTear(false)
	, m_bTearTD(true)
	, m_bRadian(true)
	, m_PlayerType()
	, m_bPower(false)
{
	AddComponent(new CCollider);
	AddComponent(new CAnimator);



	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecObj = pCurScene->GetObjects(LAYER_TYPE::PLAYER);

	m_PlayerInfo = ((CPlayer*)vecObj[0])->GetPlayerInfo();
	m_pPlayer = ((CPlayer*)vecObj[0]);

	GetCollider()->SetScale(Vec2(20.f, 20.f));
	GetCollider()->SetOffset(m_fTearColliderOffset);

	
	m_pTearImage = CResMgr::GetInst()->FindImg(L"TearAtlas");
	GetAnimator()->CreateAnimation(L"PlayerTearAtlas", m_pTearImage, Vec2(160.f, 0.f), Vec2(36.f, 36.f), Vec2(75.f, 75.f), Vec2(0.f, -35.f), 36.f, 1, 0.03f);
	GetAnimator()->CreateAnimation(L"MonsterTearAtlas", m_pTearImage, Vec2(160.f, 71.f), Vec2(36.f, 36.f), Vec2(75.f, 75.f), Vec2(0.f, -25.f), 36.f, 1, 0.03f);
	

}

CIsaacTear::~CIsaacTear()
{

}



void CIsaacTear::tick()
{	
	
	if (Effect::TEARP == m_PlayerType)
	{
		GetAnimator()->Play(L"PlayerTearAtlas", true);
		
	}
		
	if(Effect::TEARM == m_PlayerType)
	{
		GetAnimator()->Play(L"MonsterTearAtlas", true);
		
	}

	

	m_fAccTime += DT;

	Vec2 vPos = GetPos();

	if (m_bRadian)
	{
		vPos.x += (m_PlayerInfo.fShotSpeed * 500.f) * m_fTearAngle.x  * DT;
		vPos.y += (m_PlayerInfo.fShotSpeed * 500.f) * m_fTearAngle.y  * DT;
	}
	
	else
	{
		vPos.x += (m_PlayerInfo.fShotSpeed * 500.f) * m_VMonsterTear.x * DT;
		vPos.y += (m_PlayerInfo.fShotSpeed * 500.f) * m_VMonsterTear.y * DT;
	}
	


	if (m_bAutoTear)
	{
		//타겟을 향해서 방향을 회전한다.
		Vec2 vMonPos = m_pPlayer->GetPos();
		Vec2 vMissilePos = GetPos();

		Vec2 vDirToMon = vMonPos - vMissilePos;
		Vec2 vMissileDir = GetDir();

		vDirToMon.Normalize();
		vMissileDir.Normalize();

		float fDot = vMissileDir.Dot(vDirToMon);
		float fAngle = acosf(fDot); // 미사일의 진행방향과 몬스터를 향하는 방향 사이의 각도를 구함
		fAngle = (fAngle / PI) * 180.f; // Radian to Degree

		float fRotateAngle = m_fRotateSpeed * DT; // 회전 각도 크기

		if (fAngle < fRotateAngle)
		{
			fRotateAngle = fAngle;
		}

		if (0.f < CrossVector(vDirToMon, vMissileDir))
			fRotateAngle *= -1.f;

		vMissileDir = RotateVector(vMissileDir, fRotateAngle);
		SetDir(vMissileDir);
	}
	if (m_bTearTD)
	{
		if (m_fAccTime >= m_PlayerInfo.fAttackRance / 10 - 0.2f)
		{
			if (m_PlayerInfo.fAttackRance / 10 < m_fAccTime)
			{
			}
			else
			{
				// 떨어지는 눈물 연출 및 충돌체 올리기
				vPos.x += (m_PlayerInfo.fShotSpeed * 0.f) * cosf(CMissile::GetAngle()) * DT;
				vPos.y += (m_PlayerInfo.fShotSpeed * 500.f) * sinf(CMissile::GetAngle()) * DT;
				//vPos.y += 500.f * DT;


				m_fTearColliderOffset.x += (m_PlayerInfo.fShotSpeed * 0.f) * cosf(CMissile::GetAngle()) * DT;
				m_fTearColliderOffset.y += (m_PlayerInfo.fShotSpeed * -500.f) * sinf(CMissile::GetAngle()) * DT;
				GetCollider()->SetOffset(m_fTearColliderOffset);



				float fAngle = CMissile::GetAngle();
				fAngle += PI / 180.f;
				SetPos(vPos);
				CMissile::SetAngle(fAngle);
			}

		}


		if (m_fAccTime >= m_PlayerInfo.fAttackRance / 10)
		{
			if (m_bTearTD)
			{
				m_bTearTD = false;
				m_fTearAngle.x = 0;
				m_fTearAngle.y = 0;
				Effect();
				DeleteObject(this);
				return;
			}
			//DeleteObject(this);
		}
		else
		{
			//GetAnimator()->Play(L"PlayerTearAtlas", true);
			//Effect();
		}

		if (m_fAccTime >= (m_PlayerInfo.fAttackRance / 10) + 0.1)
		{
			m_bTearTD = false;
			Effect();
			DeleteObject(this);
			m_fAccTime = 0;
			return;
		}
		//GetAnimator()->Play(L"PlayerTearDestory", true);
		/*if (IsTap(KEY_TYPE::RIGHT) )
		{
			GetAnimator()->Play(L"PlayerTearDestory", true);
		}*/

		SetPos(vPos);

		if (m_fAccTime >= (m_PlayerInfo.fAttackRance / 10))
		{
			m_bTearTD = false;
			Effect();
			DeleteObject(this);
			m_fAccTime = 0;
			return;
		}
	}
	CMissile::tick();



}




void CIsaacTear::FindTarget()
{
	if (IsValid(m_pPlayer))
		return;

	Vec2 vMissilePos = GetPos();

	// 현재 Scene을 찾는다
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Monster Layer을 가져온다.
	const vector<CObject*>& vecMon = pCurScene->GetObjects(LAYER_TYPE::MONSTER);

	float fDistance = m_fDetectRange;
	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		float fDist = vMissilePos.Distance(vecMon[i]->GetPos());

		if (fDist < fDistance)
		{
			fDistance = fDist;
			m_pPlayer = vecMon[i];
		}

	}

}

void CIsaacTear::Effect()
{

	// 눈물 없애는 임팩트
	CEffect* PlayerTearDestory = Instantiate<CEffect>(GetPos(), LAYER_TYPE::PLAYER_PROJECTILE);	
	PlayerTearDestory->SetTypeBool(m_PlayerType);
}

void CIsaacTear::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	

	switch (m_PlayerType)
	{
	case Effect::TEARM:
		
		if (dynamic_cast<CPlayer*>(_pOhterCollider->GetOwner()))
		{
			m_bTearTD = false;
			m_fTearAngle.x = 0;
			m_fTearAngle.y = 0;
			Effect();
			CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOhterCollider->GetOwner());
			pPlayer->Demage();
			
			DeleteObject(this);
			//GetAnimator()->Play(L"PlayerTearDestory", false);
			
			return;
		}
		break;
	case Effect::TEARP:
		if (dynamic_cast<CMonster*>(_pOhterCollider->GetOwner()))
		{
			m_bTearTD = false;
			m_fTearAngle.x = 0;
			m_fTearAngle.y = 0;
			CMonster* pMonster = dynamic_cast<CMonster*>(_pOhterCollider->GetOwner());
			pMonster->MonsterDemage(m_PlayerInfo.fAttackPower);
			if (pMonster == dynamic_cast<CDeadIsaac*>(_pOhterCollider->GetOwner()))
			{
				CDeadIsaac* pMonster = dynamic_cast<CDeadIsaac*>(_pOhterCollider->GetOwner());
				CMonster_HPbar* HP = pMonster->GetHPbar();
				float Ratio = m_PlayerInfo.fAttackPower / pMonster->GetInfo().fMaxHP;
				HP->SetRate(Ratio);
			}
			
			Effect();
			DeleteObject(this);
			//GetAnimator()->Play(L"PlayerTearDestory", false);
			
			return;
		}
		break;
	case Effect::LIGHTCOLUMN:
		break;
	case Effect::END:
		break;
	default:
		break;
	}
		
	if (dynamic_cast<CTile*>(_pOhterCollider->GetOwner()))
	{
		CTile* Tile = dynamic_cast<CTile*>(_pOhterCollider->GetOwner());

		OBJECT_TYPE Tiletype = Tile->GetType();
		
		switch (Tiletype)
		{
		case OBJECT_TYPE::DEFAULT:
			break;
		case OBJECT_TYPE::MAP:
			break;
		case OBJECT_TYPE::OBJECT:

			break;
		case OBJECT_TYPE::IRON:
			m_bTearTD = false;
			m_fTearAngle.x = 0;
			m_fTearAngle.y = 0;
			Effect();
			DeleteObject(this);
			//GetAnimator()->Play(L"PlayerTearDestory", false);
			return;
			break;
		case OBJECT_TYPE::STONE:
			m_bTearTD = false;
			m_fTearAngle.x = 0;
			m_fTearAngle.y = 0;
			Effect();
			DeleteObject(this);
			//GetAnimator()->Play(L"PlayerTearDestory", false);
			return;
			break;
		case OBJECT_TYPE::FIRE:
			m_bTearTD = false;
			m_fTearAngle.x = 0;
			m_fTearAngle.y = 0;
			Effect();
			DeleteObject(this);
			//GetAnimator()->Play(L"PlayerTearDestory", false);
			return;
			break;
		case OBJECT_TYPE::EMPTYAREA:
			break;
		case OBJECT_TYPE::SHARP:
			
			break;
		case OBJECT_TYPE::DOOR:
			m_bTearTD = false;
			m_fTearAngle.x = 0;
			m_fTearAngle.y = 0;
			Effect();
			DeleteObject(this);
			//GetAnimator()->Play(L"PlayerTearDestory", false);
			return;
			break;
		case OBJECT_TYPE::END:
			break;
		default:
			break;
		}
	}

}