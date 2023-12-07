#include "pch.h"
#include "CScene_Logo.h"


#include "CMain.h"

#include "CEngine.h"
#include "CCollisionMgr.h"
#include "CTimeMgr.h"
#include "CSound.h"
#include "CResMgr.h"

#include "CEventMgr.h"
#include "CKeyMgr.h"


CScene_Logo::CScene_Logo()
	:m_fAcctime()
	, m_bNext(false)
{
}

CScene_Logo::~CScene_Logo()
{
}

void CScene_Logo::enter()
{

	CScene::SetResoluration(1280,720);

	CMain* Main = Instantiate<CMain>(Vec2(0, 0), LAYER_TYPE::MAP);
	// 충돌 체크
	CCollisionMgr::GetInst()->clear();

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLAYER_PROJECTILE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::TILE, LAYER_TYPE::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::TILE, LAYER_TYPE::PLAYER_PROJECTILE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::DEFAULT);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);

	
}

void CScene_Logo::exit()
{
	DeleteAllObject();
	//CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_OUT, 2);
	CCollisionMgr::GetInst()->clear();


}

void CScene_Logo::tick()
{
	CScene::tick();
	
	m_fAcctime += DT;

	if (IsTap(KEY_TYPE::N_1))
	{
		SceneChange(SCENE_TYPE::TOOL);
	}
	if (IsTap(KEY_TYPE::N_2))
	{
		SceneChange(SCENE_TYPE::LOGO);
	}
	if (IsTap(KEY_TYPE::N_3))
	{
		SceneChange(SCENE_TYPE::START);
	}
	if (IsTap(KEY_TYPE::N_4))
	{
		SceneChange(SCENE_TYPE::STAGE_01);
	}
	if (IsTap(KEY_TYPE::N_5))
	{
		SceneChange(SCENE_TYPE::ENDING);
	}


	if(IsTap(KEY_TYPE::ENTER))
	m_bNext = true;

	if (IsTap(KEY_TYPE::SPACE))
	{
		CSound* pBgm = CResMgr::GetInst()->FindSound(L"intro");
		if (nullptr != pBgm)
			pBgm->Play(false);
		
		m_fAcctime = 2;
		
	}
	if (m_fAcctime > 6)
	{
		if (m_bNext)
			SceneChange(SCENE_TYPE::START);
	}
	
}


