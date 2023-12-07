#include "pch.h"
#include "CMonsterTear.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CResMgr.h"
#include "CImage.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"


#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CTile.h"

#include "CMonster.h"
#include "CPlayer.h"


CMonsterTear::CMonsterTear()
	: m_MonsterInfo()
	, m_pMonster(nullptr)
	, m_pTearImage(nullptr)
	, m_pTearTDImage(nullptr)
	, m_fTearColliderOffset(5.f, 21.f)
	, m_fAccTime(0)
	, m_fTearAngle()
	, m_fRotateSpeed(0)
	, m_fDetectRange(0)
	, m_fRotateTear(0)
	, m_fTearpos(0)
	, m_bAutoTear(false)
	, m_bTearTD(true)
{
	AddComponent(new CCollider);
	AddComponent(new CAnimator);


	GetCollider()->SetScale(Vec2(20.f, 20.f));
	GetCollider()->SetOffset(m_fTearColliderOffset);

	CMonster* a;
	m_MonsterInfo = a->GetInfo();

	m_pTearImage = CResMgr::GetInst()->FindImg(L"PlayerTDAtlas");
	GetAnimator()->CreateAnimation(L"PlayerTearDestory", m_pTearImage, Vec2(0.f, 0.f), Vec2(63.f, 63.f), Vec2(100.f, 100.f), Vec2(0.f, -45.f), 63.f, 16, 0.03f);
	m_pTearImage = CResMgr::GetInst()->FindImg(L"TearAtlas");
	GetAnimator()->CreateAnimation(L"PlayerTearAtlas", m_pTearImage, Vec2(160.f, 71.f), Vec2(36.f, 36.f), Vec2(63.f, 63.f), Vec2(0.f, -25.f), 36.f, 1, 0.03f);



}

CMonsterTear::~CMonsterTear()
{

}



void CMonsterTear::tick()
{


	m_fAccTime += DT;

	Vec2 vPos = GetPos();

	vPos.x += (m_MonsterInfo.fShotSpeed * 500.f) * m_fTearAngle.x * DT;
	vPos.y += (m_MonsterInfo.fShotSpeed * 500.f) * m_fTearAngle.y * DT;






	if (m_bAutoTear)
	{
		//타겟을 향해서 방향을 회전한다.
		Vec2 vMonPos = m_pMonster->GetPos();
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
				GetAnimator()->Play(L"PlayerTearDestory", false);

			}
			//DeleteObject(this);
		}
		else
		{
			GetAnimator()->Play(L"PlayerTearAtlas", true);
		}

		if (m_fAccTime >= (m_PlayerInfo.fAttackRance / 10) + 0.1)
		{
			DeleteObject(this);
		}
		//GetAnimator()->Play(L"PlayerTearDestory", true);
		/*if (IsTap(KEY_TYPE::RIGHT) )
		{
			GetAnimator()->Play(L"PlayerTearDestory", true);
		}*/

		SetPos(vPos);
	}
	if (m_fAccTime >= (m_PlayerInfo.fAttackRance / 10) + 0.05)
	{
		DeleteObject(this);
	}

	CMissile::tick();



}




void CMonsterTear::FindTarget()
{
	if (IsValid(m_pMonster))
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
			m_pMonster = vecMon[i];
		}

	}

}

void CMonsterTear::CollisionBeginOverlap(CCollider* _pOhterCollider)
{

	int a = 0;

	if (dynamic_cast<CPlayer*>(_pOhterCollider->GetOwner()))
	{
		m_bTearTD = false;
		m_fTearAngle.x = 0;
		m_fTearAngle.y = 0;
		GetAnimator()->Play(L"PlayerTearDestory", false);
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
			GetAnimator()->Play(L"PlayerTearDestory", false);
			break;
		case OBJECT_TYPE::STONE:
			m_bTearTD = false;
			m_fTearAngle.x = 0;
			m_fTearAngle.y = 0;
			GetAnimator()->Play(L"PlayerTearDestory", false);
			break;
		case OBJECT_TYPE::FIRE:
			m_bTearTD = false;
			m_fTearAngle.x = 0;
			m_fTearAngle.y = 0;
			GetAnimator()->Play(L"PlayerTearDestory", false);
			break;
		case OBJECT_TYPE::EMPTYAREA:
			break;
		case OBJECT_TYPE::SHARP:

			break;
		case OBJECT_TYPE::DOOR:
			m_bTearTD = false;
			m_fTearAngle.x = 0;
			m_fTearAngle.y = 0;
			GetAnimator()->Play(L"PlayerTearDestory", false);
			break;
		case OBJECT_TYPE::END:
			break;
		default:
			break;
		}



		//DeleteObject(this);
	}

	if (m_fAccTime >= 0.048)
	{
		//DeleteObject(this);

	}






}
