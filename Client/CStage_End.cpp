#include "pch.h"
#include "CStage_End.h"

#include "CKeyMgr.h"
#include "CEnding.h"
#include "CPlayer.h"
#include "CCamera.h"

CStage_End::CStage_End()
{
}

CStage_End::~CStage_End()
{
}

void CStage_End::enter()
{
    CScene::SetResoluration(1280, 720);

    CEnding* Ending = Instantiate<CEnding>(Vec2(160.f, 90.f), LAYER_TYPE::ENDING);
    Ending->SetBackground();
    Ending = Instantiate<CEnding>(Vec2(460.f, 160.f), LAYER_TYPE::ENDING);

    CCamera::GetInst()->SetLookAt(Vec2(640, 360));
}

void CStage_End::exit()
{
    DeleteAllObject();
}

void CStage_End::tick()
{
    CScene::SceneMove();
    CScene::tick();
}


