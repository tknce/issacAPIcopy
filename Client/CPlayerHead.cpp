#include "pch.h"
#include "CPlayerHead.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CImage.h"
#include "CPlayer.h"




CPlayerHead::CPlayerHead()
	: m_PlayerHead(nullptr)
	, m_fAcctime(0.f)
	, m_bBool(true)
	, m_bHIt(false)
{
	
	AddComponent(new CAnimator);


	m_PlayerHead = CResMgr::GetInst()->LoadImg(L"isaacHead", L"image\\isaac\\Player\\isaacPlayer.bmp");

	GetAnimator()->CreateAnimation(L"Head_Down", m_PlayerHead, Vec2(0.f, 0.f), Vec2(40.f, 36.f), Vec2(72.f, 74.f), Vec2(-18.f, 45.f), 32.f, 1, 0.5f);
	GetAnimator()->CreateAnimation(L"Head_Right", m_PlayerHead, Vec2(80.f, 0.f), Vec2(40.f, 36.f), Vec2(72.f, 74.f), Vec2(-20.f, 43.f), 32.f, 1, 0.5f);
	GetAnimator()->CreateAnimation(L"Head_Up", m_PlayerHead, Vec2(160.f, 0.f), Vec2(40.f, 36.f), Vec2(72.f, 74.f), Vec2(-22.f, 44.f), 32.f, 1, 0.5f);
	GetAnimator()->CreateAnimation(L"Head_Left", m_PlayerHead, Vec2(240.f, 0.f), Vec2(40.f, 36.f), Vec2(72.f, 74.f), Vec2(-22.f, 43.f), 32.f, 1, 0.5f);

	m_PlayerHead = CResMgr::GetInst()->LoadImg(L"isaacHeadTear", L"image\\isaac\\Player\\isaacPlayer1.bmp");
	GetAnimator()->CreateAnimation(L"HeadTear_Down", m_PlayerHead, Vec2(0.f, 0.f), Vec2(40.f, 36.f), Vec2(72.f, 74.f), Vec2(-17.f, 43.f), 40.f, 2, 0.2f);
	GetAnimator()->CreateAnimation(L"HeadTear_Right", m_PlayerHead, Vec2(80.f, 0.f), Vec2(40.f, 36.f), Vec2(72.f, 74.f), Vec2(-20.f, 42.f), 40.f, 2, 0.2f);
	GetAnimator()->CreateAnimation(L"HeadTear_Up", m_PlayerHead, Vec2(160.f, 0.f), Vec2(40.f, 36.f), Vec2(72.f, 74.f), Vec2(-20.f, 42.f), 40.f, 2, 0.2f);
	GetAnimator()->CreateAnimation(L"HeadTear_Left", m_PlayerHead, Vec2(240.f, 0.f), Vec2(40.f, 36.f), Vec2(72.f, 74.f), Vec2(-20.f, 43.f), 40.f, 2, 0.2f);

	GetAnimator()->CreateAnimation(L"Empty", m_PlayerHead, Vec2(240.f, 230.f), Vec2(40.f, 36.f), Vec2(72.f, 74.f), Vec2(-20.f, 43.f), 40.f, 1, 0.2f);

	GetAnimator()->Play(L"Head_Down", true);	
}

CPlayerHead::~CPlayerHead()
{
}


void CPlayerHead::tick()
{


	const vector<CObject*>& vecObj = CSceneMgr::GetInst()->GetCurScene()->GetObjects(LAYER_TYPE::PLAYER);

	

	Vec2 vPos = ((CPlayer*)vecObj[0])->GetPos();
	vPos.y = vPos.y - 72.f;
	m_fAcctime += DT;


	bool Hit = GetState();
	


	if (Hit)
	{
		if (m_bHIt)
		{
			GetAnimator()->Play(L"Head_Down", true);
			m_bHIt = false;
		}

		if (m_bBool)
		{
			

			if (IsTap(KEY_TYPE::W))
				GetAnimator()->Play(L"Head_Up", true);
			if (IsTap(KEY_TYPE::S))
				GetAnimator()->Play(L"Head_Down", true);
			if (IsTap(KEY_TYPE::A))
				GetAnimator()->Play(L"Head_Left", true);
			if (IsTap(KEY_TYPE::D))
				GetAnimator()->Play(L"Head_Right", true);

			if (IsPressed(KEY_TYPE::UP))
			{
				m_bBool = false;
				GetAnimator()->Play(L"HeadTear_Up", false);

			}
			if (IsPressed(KEY_TYPE::DOWN))
			{
				m_bBool = false;
				GetAnimator()->Play(L"HeadTear_Down", false);

			}
			if (IsPressed(KEY_TYPE::RIGHT))
			{
				m_bBool = false;
				GetAnimator()->Play(L"HeadTear_Right", false);

			}
			if (IsPressed(KEY_TYPE::LEFT))
			{
				m_bBool = false;
				GetAnimator()->Play(L"HeadTear_Left", false);
			}
		}
		else
		{
			if (m_fAcctime > 0.4)
			{
				m_bBool = true;
				m_fAcctime = 0.f;
				
			}
		}
	}
	else
	{
		GetAnimator()->Play(L"Empty", false);
		m_bBool = false;
		m_fAcctime = 0.f;
		m_bHIt = true;
		
	}
	SetPos(vPos);
	CObject::tick();
}


