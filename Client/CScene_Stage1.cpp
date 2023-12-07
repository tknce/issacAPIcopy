#include "pch.h"
#include "CScene_Stage1.h"


#include "CCollisionMgr.h"
#include "CCamera.h"
#include "CCollider.h"
#include "CKeyMgr.h"
#include "CPlayer.h"
#include "CPlayerHead.h"
#include "CDeadIsaac.h"
#include "CProp.h"
#include "CRedmushroom.h"
#include "CAngel.h"


#include "CTile.h"

CScene_Stage1::CScene_Stage1()
{
}

CScene_Stage1::~CScene_Stage1()
{
}

void CScene_Stage1::enter()
{
    CScene::SetResoluration(1280, 720);

    CPlayer* m_Player = new CPlayer;
    m_Player->SetPos(Vec2(640.f, 360.f));
    m_Player->SetScale(Vec2(100.f, 100.f));
    AddObject(m_Player, LAYER_TYPE::PLAYER);

    CPlayerHead* PlayerHead = new CPlayerHead;
    AddObject(PlayerHead, LAYER_TYPE::PLAYER);

    m_Player->SetPlayerHead(PlayerHead);

    CCamera::GetInst()->SetTargetObject(m_Player);
    
    CObject* pMonster = new CDeadIsaac;
    pMonster->SetPos(Vec2(1280 + 640, 360));
    AddObject(pMonster, LAYER_TYPE::MONSTER);

    CCollisionMgr::GetInst()->clear();
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_PROJECTILE);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLAYER_PROJECTILE);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_PROJECTILE, LAYER_TYPE::TILE);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER_PROJECTILE, LAYER_TYPE::TILE);

    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENDING);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PROP);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::TILE);

    TileLoad();
    CCamera::GetInst()->SetCameraEffect(CAM_EFFECT::FADE_IN, 2);

    
}

void CScene_Stage1::exit()
{
    DeleteAllObject();

    CCollisionMgr::GetInst()->clear();
}

void CScene_Stage1::tick()
{
    CScene::tick();
    CScene::MiniMap();
    CScene::Door();
    CCamera::GetInst()->RemoveTargetObject();
    if (IsTap(KEY_TYPE::J))
    {
        GetSwich();
        if (!GetSwich())
            SetSwich(true);
        else
            SetSwich(false);
    }
    if (IsTap(KEY_TYPE::K))
    {
        GetTileSwich();
        if (!GetTileSwich())
            SetTileSwich(true);
        else
            SetTileSwich(false);
    }


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
}

void CScene_Stage1::TileLoad()
{
    // 열려는 파일 이름
    OPENFILENAME ofn = {};

    wchar_t szFilePath[256] = {};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFilePath;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 256;
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // 파일 입출력
    FILE* pFile = nullptr;




    // 실행경로 가져오기
    GetCurrentDirectory(256, szFilePath);

    // 상위폴더로 변경
    size_t iLen = wcsnlen_s(szFilePath, 256);
    for (size_t i = iLen; i > 0; --i)
    {
        if (L'\\' == szFilePath[i])
        {
            szFilePath[i + 1] = L'\0';
            break;
        }

        continue;
    }

    // + L"bin\\content"
    wcscat_s(szFilePath, L"bin\\content\\Save\\2");





    // 쓰기 모드로 열기
    _wfopen_s(&pFile, szFilePath, L"rb");
    //_wfopen_s(&pFile, L"C:\\Users\\ace\\Desktop\\125", L"rb");

    if (nullptr == pFile)
        return;

    // 타일 가로 세로 개수
    UINT iCol = 0;
    UINT iRow = 0;

    UINT iMapCol = 0;
    UINT iMapRow = 0;


    fread(&iCol, sizeof(UINT), 1, pFile);
    fread(&iRow, sizeof(UINT), 1, pFile);
    fread(&iMapCol, sizeof(UINT), 1, pFile);
    fread(&iMapRow, sizeof(UINT), 1, pFile);


    CreateTile1(iMapCol, iMapRow, OBJECT_TYPE::MAP);



    const vector<CObject*>& vecTileMap = GetObjects(LAYER_TYPE::MAP);
    for (size_t i = 0; i < vecTileMap.size(); ++i)
    {
        CTile* pTile = (CTile*)vecTileMap[i];
        pTile->Load(pFile);

    }

    const vector<CObject*>& vecTile = GetObjects(LAYER_TYPE::TILE);
    for (size_t i = 0; i < vecTile.size(); ++i)
    {
        CTile* pTile = (CTile*)vecTile[i];
        pTile->Load(pFile);
        if (OBJECT_TYPE::DEFAULT != pTile->GetType())
        {
            pTile->AddComponent(new CCollider);
            Vec2 a = pTile->GetPos();
            pTile->GetCollider()->SetScale(pTile->GetColliderSacle());
            pTile->GetCollider()->SetOffset(pTile->GetColliderOffset());
            //pTile->GetCollider()->SetFinalPos(a);

            if (OBJECT_TYPE::MAP == pTile->GetType())
                pTile->SetMiniMap();
        }
    }

    fclose(pFile);
}


