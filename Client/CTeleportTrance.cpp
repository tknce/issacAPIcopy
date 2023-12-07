#include "pch.h"
#include "CTeleportTrance.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CSound.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CPlayer.h"


CTeleportTrance::CTeleportTrance()
	: m_pPlayer(nullptr)
	, m_iTeleportIdx(0)
{
}

CTeleportTrance::~CTeleportTrance()
{
}


void CTeleportTrance::enter()
{
	m_fAcctime = 0;


}

void CTeleportTrance::tick()
{
	m_fAcctime += DT;

	if (m_fAcctime > 1)
	{
		

		TelePort();
		m_fAcctime = 0;
	}
}

void CTeleportTrance::exit()
{
	
}

void CTeleportTrance::TelePort()
{
	

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	m_pPlayer = (CPlayer*)pCurScene->GetObjects(LAYER_TYPE::PLAYER).at(0);
	int iMaxCol = m_pPlayer->GetPos().x / 1280;
	int iMaxRow = m_pPlayer->GetPos().y / 720;


	CMonster* pOwner = dynamic_cast<CMonster*>(GetOwner());

	Vec2 SetPos;
	

	switch (m_iTeleportIdx)
	{
	case 0:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 178);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 96);
		break;
	case 1:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 558);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 140);
		break;
	case 2:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 488);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 380);
		break;
	case 3:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 668);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 255);
		break;
	case 4:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 168);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 90);
		break;
	case 5:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 558);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 380);
		break;
	case 6:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 258);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 250);
		break;

	case 7:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 484);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 250);
		break;
	case 8:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 674);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 21);
		break;
	case 9:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 450);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 63);
		break;
	case 10:
		SetPos.x = (float)((iMaxCol * 1280) + 66 + 48);
		SetPos.y = (float)((iMaxRow * 720) + 66 + 285);
		m_iTeleportIdx = 0;
		break;

	default:
		break;
	}
	m_iTeleportIdx += 1;

	CSound* pBgm = CResMgr::GetInst()->FindSound(L"Teleport");
	if (nullptr != pBgm)
		pBgm->Play(false);

	pOwner->SetPos(Vec2(SetPos));
	GetAI()->ChangeState(L"DEADTRACE2");
}



