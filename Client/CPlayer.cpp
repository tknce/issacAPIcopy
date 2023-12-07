#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CMissile.h"
#include "CIsaacTear.h"
#include "CMonster.h"
#include "CPlayerHead.h"
#include "CTile.h"
#include "CHP.h"
#include "CMiniMap.h"



#include "CImage.h"
#include "CResMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CSound.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"



CPlayer::CPlayer()
	: m_PlayerHead(nullptr)
	, m_CHP(nullptr)
	, m_fSpeed(200.f)
	, m_fAccTime(0.f)
	, m_fScoTime(0.f)
	, m_fPlayerAngleUD(PI / 2.f)
	, m_fPlayerAngleRL(0.f)
	, m_bUnique(true)
	, HP(3)
	, Score(0)
	, m_PlayerInfo()	
	, m_bSet(false)
{	



	AddComponent(new CCollider);
	AddComponent(new CAnimator);
	AddComponent(new CRigidBody);
	
	

	GetCollider()->SetScale(Vec2(32.f, 32.f));
	GetCollider()->SetOffset(Vec2(0.f, 15.f));

	// 플레이어 애니메이션 초기화

	CImage* pPlayerAtlas = CResMgr::GetInst()->LoadImg(L"PlayerAtlas", L"image\\isaac\\Player\\isaacPlayer.bmp");

	GetAnimator()->CreateAnimation(L"next_Map", pPlayerAtlas, Vec2(0.f, 142.f), Vec2(43.f, 37.f), Vec2(72.f, 74.f), Vec2(-20.f, 0.f), 43.f, 1, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Up", pPlayerAtlas, Vec2(0.f, 36.f), Vec2(32.f, 36.f), Vec2(72.f, 74.f), Vec2(-20.f, 0.f), 32.f, 10, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Down", pPlayerAtlas, Vec2(0.f, 36.f), Vec2(32.f, 36.f), Vec2(72.f, 74.f), Vec2(-20.f, 0.f), 32.f, 10, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Left", pPlayerAtlas, Vec2(0.f, 106.f), Vec2(32.f, 36.f), Vec2(72.f, 74.f), Vec2(-20.f,0.f), 32.f, 10, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Right", pPlayerAtlas, Vec2(0.f, 72.f), Vec2(32.f, 36.f), Vec2(72.f, 74.f), Vec2(-21.f, -3.f), 32.f, 10, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_UpStand", pPlayerAtlas, Vec2(0.f, 36.f), Vec2(32.f, 36.f), Vec2(72.f, 74.f), Vec2(-20.f, 0.f), 32.f, 1, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_LeftStand", pPlayerAtlas, Vec2(0.f, 106.f), Vec2(32.f, 36.f), Vec2(72.f, 74.f), Vec2(-20.f, 0.f), 32.f, 1, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_RightStand", pPlayerAtlas, Vec2(0.f, 72.f), Vec2(32.f, 36.f), Vec2(72.f, 74.f), Vec2(-25.f, -3.f), 32.f, 1, 0.1f);
	
	GetAnimator()->CreateAnimation(L"PlayerDead", pPlayerAtlas, Vec2(125.f, 319.f), Vec2(54.f, 37.f), Vec2(92.f, 82.f), Vec2(-25.f, -3.f), 32.f, 1, 1.f);

	 pPlayerAtlas = CResMgr::GetInst()->LoadImg(L"PlayerHit", L"image\\isaac\\Player\\PlayerHit.bmp");
	GetAnimator()->CreateAnimation(L"PlayerHit", pPlayerAtlas, Vec2(0.f, 0.f), Vec2(37.f, 54.f), Vec2(82.f, 84.f), Vec2(-25.f, -3.f), 37.f, 2, 2.f,true,true);

	pPlayerAtlas = CResMgr::GetInst()->LoadImg(L"GetItem", L"image\\isaac\\Player\\GetItem.bmp");
	GetAnimator()->CreateAnimation(L"Getitem", pPlayerAtlas, Vec2(0.f, 0.f), Vec2(37.f, 54.f), Vec2(76.f, 108.f), Vec2(-25.f, -3.f), 37.f, 2, 2.f );

	CImage* pPlayerAtlas2 = CResMgr::GetInst()->LoadImg(L"PlayerAtlas123", L"image\\isaac\\Tears\\TearsDestoryAtlas.bmp");
	GetAnimator()->CreateAnimation(L"PlayerTearDestory", pPlayerAtlas2, Vec2(0.f, 0.f), Vec2(63.f, 63.f), Vec2(100.f, 100.f), Vec2(0.f, 0.f), 63.f, 16, 0.03f);


	pPlayerAtlas = CResMgr::GetInst()->LoadImg(L"TelePort", L"image\\isaac\\Player\\TelePort.bmp");
	GetAnimator()->CreateAnimation(L"TelePort", pPlayerAtlas, Vec2(0.f, 0.f), Vec2(54.f, 128.f), Vec2(100.f, 100.f), Vec2(0.f, 0.f), 54.f, 2, 0.5);

	GetAnimator()->Play(L"Walk_Down", true);

	GetRigidBody()->SetMaxSpeed(500.f);
	//GetRigidBody()->SetMaxGravitySpeed(1000.f);
	GetRigidBody()->SetGravity(false);
	GetRigidBody()->SetMass(3.f);
	/*GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 800.f));*/

	// 기본정보 초기화
	CMiniMap* minimap = Instantiate<CMiniMap>(Vec2(1280  - 170, 0), LAYER_TYPE::ETCUI);
	minimap->SetMiniMaptype();
	minimap = Instantiate<CMiniMap>(Vec2(1280  - 170, 0), LAYER_TYPE::ETCUI);
	minimap->SetMiniMaptype(1);
	
	

	m_CHP = Instantiate<CHP>(Vec2(0, 0), LAYER_TYPE::ETCUI);
	m_CHP->SetMaxHP(m_PlayerInfo.fCurHP);

	m_PlayerInfo.fAttackPower = 10.f;
	m_PlayerInfo.fAttackRance = 11.f;
	m_PlayerInfo.fAttackSpeed = 0.4f;
	m_PlayerInfo.fCurHP = 3.f;
	m_PlayerInfo.fMaxHP = 3.f;
	m_PlayerInfo.fSpeed = 1.f;
	m_PlayerInfo.fMaxSpeed = 2.f;
	m_PlayerInfo.fShotSpeed = 0.8f;
	
	
	

}

CPlayer::~CPlayer()
{
	
}






void CPlayer::tick()
{
	m_CHP->SetHP(m_PlayerInfo.fCurHP);

	if (IsTap(KEY_TYPE::P))
		Healing();

	if (m_PlayerInfo.fCurHP > 0)
	{
		m_fAccTime += DT;
		m_fScoTime += DT;
		// 키입력에 따른 이동
		Vec2 vPos = GetPos();

		// 시간 동기화
		if (IsPressed(KEY_TYPE::W))
		{
			GetRigidBody()->AddForce(Vec2(0.f, -5000.f));
		}

		if (IsPressed(KEY_TYPE::S))
		{
			GetRigidBody()->AddForce(Vec2(0.f, 5000.f));
		}


		if (IsPressed(KEY_TYPE::A))
		{
			GetRigidBody()->AddForce(Vec2(-5000.f, 0.f));
		}



		if (IsPressed(KEY_TYPE::D))
		{
			GetRigidBody()->AddForce(Vec2(5000.f, 0.f));
		}




		if (m_bUnique)
		{
			if (m_bSet)
			{
				GetAnimator()->Play(L"Walk_UpStand", true);
				m_bSet = false;
			}
			

			if (IsTap(KEY_TYPE::W))
				GetAnimator()->Play(L"Walk_Up", true);
			if (IsTap(KEY_TYPE::S))
				GetAnimator()->Play(L"Walk_Down", true);
			if (IsTap(KEY_TYPE::A))
				GetAnimator()->Play(L"Walk_Left", true);
			if (IsTap(KEY_TYPE::D))
				GetAnimator()->Play(L"Walk_Right", true);

			if (GetRigidBody()->GetVelocity() == Vec2(0.f, 0.f))
				GetAnimator()->Play(L"Walk_UpStand", true);

			m_fScoTime = 0.f;
		}
		else
		{
			
			if (m_fScoTime > 1.f)
			{
				m_bUnique = true;				
				m_PlayerHead->SetState(true);
				//GetAnimator()->Play(L"Walk_Down", true);
				m_fScoTime = 0.f;
				m_bSet = true;
			}

		}


		

		if (IsPressed(KEY_TYPE::UP))
		{
			if (m_fAccTime >= m_PlayerInfo.fAttackSpeed)
			{
				CSound* pBgm = CResMgr::GetInst()->FindSound(L"Playertear");
				if (nullptr != pBgm)
					pBgm->Play(false);
				
				CIsaacTear* pMissile = Instantiate<CIsaacTear>(GetPos() + Vec2(-20.f, 0.f), LAYER_TYPE::PLAYER_PROJECTILE);
				
				pMissile->SetPlayerMode(Effect::TEARP);
				pMissile->GetCollider()->SetOffset(Vec2(15.f, 0.f));
				// 키입력에 따른 눈물 각도 조정
				if (IsPressed(KEY_TYPE::D))
				{
					float m_fPlayerAngle1 = PI / 6.f;
					m_fPlayerAngleUD -= m_fPlayerAngle1;
					float m_fplayer = PI / 4.f;

					if (m_fPlayerAngleUD <= m_fplayer)
					{
						m_fPlayerAngleUD = PI / 3.f;
					}

				}

				// 키입력에 따른 눈물 각도 조정
				if (IsPressed(KEY_TYPE::A))
				{
					float m_fPlayerAngle1 = PI / 6.f;
					m_fPlayerAngleUD += m_fPlayerAngle1;
					float m_fplayer = PI / 1.5f;

					if (m_fPlayerAngleUD >= m_fplayer)
					{
						m_fPlayerAngleUD = PI / 1.5f;
					}

				}

				Vec2 a = Vec2((1.f * cosf(m_fPlayerAngleUD)), (-1.f * sinf(m_fPlayerAngleUD)));

				pMissile->SetTearAngle(a);


				m_fAccTime = 0.f;
				m_fPlayerAngleUD = PI / 2.f;

			}
		}

		if (IsPressed(KEY_TYPE::DOWN))
		{
			if (m_fAccTime >= m_PlayerInfo.fAttackSpeed)
			{
				CSound* pBgm = CResMgr::GetInst()->FindSound(L"Playertear");
				if (nullptr != pBgm)
					pBgm->Play(false);

				CIsaacTear* pMissile = Instantiate<CIsaacTear>(GetPos() + Vec2(-20.f, 0.f), LAYER_TYPE::PLAYER_PROJECTILE);
				pMissile->SetPlayerMode(Effect::TEARP);
				pMissile->GetCollider()->SetOffset(Vec2(15.f,-45.f));
				// 키입력에 따른 눈물 각도 조정
				if (IsPressed(KEY_TYPE::D))
				{
					float m_fPlayerAngle1 = PI / 6.f;
					m_fPlayerAngleUD -= m_fPlayerAngle1;
					float m_fplayer = PI / 4.f;

					if (m_fPlayerAngleUD <= m_fplayer)
					{
						m_fPlayerAngleUD = PI / 3.f;
					}

				}

				// 키입력에 따른 눈물 각도 조정
				if (IsPressed(KEY_TYPE::A))
				{
					float m_fPlayerAngle1 = PI / 6.f;
					m_fPlayerAngleUD += m_fPlayerAngle1;
					float m_fplayer = PI / 1.5f;

					if (m_fPlayerAngleUD >= m_fplayer)
					{
						m_fPlayerAngleUD = PI / 1.5f;
					}

				}

				Vec2 a = Vec2((1.f * cosf(m_fPlayerAngleUD)), (1.f * sinf(m_fPlayerAngleUD)));

				pMissile->SetTearAngle(a);


				m_fAccTime = 0.f;
				m_fPlayerAngleUD = PI / 2.f;
			}
		}

		if (IsPressed(KEY_TYPE::LEFT))
		{
			if (m_fAccTime >= m_PlayerInfo.fAttackSpeed)
			{
				CSound* pBgm = CResMgr::GetInst()->FindSound(L"Playertear");
				if (nullptr != pBgm)
					pBgm->Play(false);

				CIsaacTear* pMissile = Instantiate<CIsaacTear>(GetPos() + Vec2(0.f, 0.f), LAYER_TYPE::PLAYER_PROJECTILE);
				pMissile->SetPlayerMode(Effect::TEARP);

				// 키입력에 따른 눈물 각도 조정
				if (IsPressed(KEY_TYPE::W))
				{
					float m_fPlayerAngle1 = PI / 6.f;
					m_fPlayerAngleRL -= m_fPlayerAngle1;
					float m_fplayer = PI / 4.f;

					if (m_fPlayerAngleRL >= m_fplayer)
					{
						m_fPlayerAngleRL = 0;
					}

				}

				// 키입력에 따른 눈물 각도 조정
				if (IsPressed(KEY_TYPE::S))
				{
					float m_fPlayerAngle1 = PI / 6.f;
					m_fPlayerAngleRL += m_fPlayerAngle1;
					float m_fplayer = -PI / 1.5f;

					if (m_fPlayerAngleRL <= m_fplayer)
					{
						m_fPlayerAngleRL = 0;
					}

				}


				Vec2 Angle = Vec2((-1.f * cosf(m_fPlayerAngleRL)), (1.f * sinf(m_fPlayerAngleRL))).Normalize();

				pMissile->SetTearAngle(Angle);




				m_fPlayerAngleRL = 0.f;

				m_fAccTime = 0.f;
			}
		}

		if (IsPressed(KEY_TYPE::RIGHT))
		{
			if (m_fAccTime >= m_PlayerInfo.fAttackSpeed)
			{
				CSound* pBgm = CResMgr::GetInst()->FindSound(L"Playertear");
				if (nullptr != pBgm)
					pBgm->Play(false);

				CIsaacTear* pMissile = Instantiate<CIsaacTear>(GetPos() + Vec2(0.f, 0.f), LAYER_TYPE::PLAYER_PROJECTILE);
				
				pMissile->SetPlayerMode(Effect::TEARP);

				// 키입력에 따른 눈물 각도 조정
				if (IsPressed(KEY_TYPE::W))
				{
					float m_fPlayerAngle1 = PI / 6.f;
					m_fPlayerAngleRL += m_fPlayerAngle1;
					float m_fplayer = PI / 4.f;

					if (m_fPlayerAngleRL >= m_fplayer)
					{
						m_fPlayerAngleRL = 0;
					}

				}


				if (IsPressed(KEY_TYPE::S))
				{
					float m_fPlayerAngle1 = PI / 6.f;
					m_fPlayerAngleRL -= m_fPlayerAngle1;
					float m_fplayer = -PI / 1.5f;

					if (m_fPlayerAngleRL <= m_fplayer)
					{
						m_fPlayerAngleRL = 0;
					}

				}


				Vec2 a = Vec2((1.f * cosf(m_fPlayerAngleRL)), (-1.f * sinf(m_fPlayerAngleRL)));

				pMissile->SetTearAngle(a);


				m_fPlayerAngleRL = 0.f;



				m_fAccTime = 0.f;

			}
		}


		SetPos(vPos);

		CObject::tick();
	}
	else
	{
	
	

		GetAnimator()->Play(L"PlayerDead", false);
	}

	if (m_PlayerInfo.fCurHP == 0)
	{
		CSound* pBgm = CResMgr::GetInst()->FindSound(L"PlayerDie");
		if (nullptr != pBgm)
			pBgm->Play(false);

		m_PlayerInfo.fCurHP -= 0.5;
	}
}

void CPlayer::SetUniquefalse()
{
	m_bUnique = false;  
	m_PlayerHead->SetState(false);
}

void CPlayer::Demage()
{
	if (m_PlayerInfo.fCurHP < 0)
		return;

	if (!m_bUnique)
		return;

	m_bUnique = false;
	m_PlayerHead->SetState(false);
	m_PlayerInfo.fCurHP  -= 0.5;

	if (m_PlayerInfo.fCurHP == 0)
	{
		m_bUnique = false;
		m_PlayerHead->SetState(false);

		return;
	}
	GetAnimator()->Play(L"PlayerHit", true);
	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Hurt");
	if (nullptr != pBgm)
		pBgm->Play(false);
}

void CPlayer::GetItem()
{
	if (!m_bUnique)
		return;

	m_bUnique = false;
	m_PlayerHead->SetState(false);

	GetAnimator()->Play(L"Getitem", true);
}









	void CPlayer::CollisionBeginOverlap(CCollider* _pOtherCollider)
	{
		const vector<CObject*>& vecObj = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::PLAYER);


		m_PlayerHead = (CPlayerHead*)vecObj[1];

	CTile* pTile = dynamic_cast<CTile*>(_pOtherCollider->GetOwner());
	if (pTile == dynamic_cast<CTile*>(_pOtherCollider->GetOwner()))
	{
		if (pTile == nullptr || !IsValid(pTile))
			return;

		GetRigidBody()->SetVelocity(Vec2(0, 0));
		switch (pTile->GetType())
		{
		case OBJECT_TYPE::DEFAULT:
			break;
		case OBJECT_TYPE::MAP:
			break;
		case OBJECT_TYPE::OBJECT:
			break;
		case OBJECT_TYPE::IRON:
			break;
		case OBJECT_TYPE::STONE:
			break;
		case OBJECT_TYPE::FIRE:
			break;
		case OBJECT_TYPE::EMPTYAREA:
			break;
		case OBJECT_TYPE::SHARP:
			Demage();
			
			

			break;
		case OBJECT_TYPE::DOOR:
			break;
		case OBJECT_TYPE::END:
			break;
		default:
			break;
		}
	}
	

	/*CMonster* pMonster = dynamic_cast<CMonster*>(_pOtherCollider->GetOwner());
	if (pMonster == nullptr || !IsValid(pMonster))
		return;
	if (IsValid(pMonster))
		{
			m_bUnique = false;
			m_PlayerInfo.fCurHP = m_PlayerInfo.fCurHP - 0.5;
		}

	if (m_PlayerInfo.fCurHP == 0)
		{
			m_bUnique = false;
		}*/

	}