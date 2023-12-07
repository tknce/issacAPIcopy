#include "pch.h"
#include "CScene_Tool.h"



#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CPathMgr.h"

#include "Resource.h"
#include "CTile.h"


#include "CPanelUI.h"
#include "CButton.h"
#include "CTagButton.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCollider.h"
#include "CIsaacTear.h"
#include "CPlayerHead.h"
#include "CItem.h"
#include "CRedmushroom.h"
#include "CDeadIsaac.h"
#include "CProp.h"
#include "CEffect.h"
#include "CEnding.h"


static int ObjectButton = 0;
static int MAPButton = 0;
static int ITEMButton = 0;
static int PlayerButton = 0;
static int MonsterButton = 0;
static int ColliderButton = 0;

static Vec2 ColliderA;
static Vec2 ColliderB;

CScene_Tool::CScene_Tool()
    : m_eMode(TOOL_MODE::NONE)
    , m_ToolObjectType(OBJECT_TYPE::OBJECT)
    , m_ToolItem_Type(ITEM_TYPE::END)
    , m_idx(0)
    
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::enter()
{

  
    CScene::SetResoluration(1600, 900);

	// 윈도우를 메뉴바에 부착
	CEngine::GetInst()->AttachMenu();

    CPlayer* m_Player = new CPlayer;
    m_Player->SetPos(Vec2(500.f, 500.f));
    m_Player->SetScale(Vec2(100.f, 100.f));
    AddObject(m_Player, LAYER_TYPE::PLAYER);

    CPlayerHead* PlayerHead = new CPlayerHead;
    PlayerHead->SetPos(Vec2(500.f, 426.f));
    //PlayerHead->SetScale(Vec2(100.f, 100.f));
    AddObject(PlayerHead, LAYER_TYPE::PLAYER);

    m_Player->SetPlayerHead(PlayerHead);



    /*CItem* Item = new CRedmushroom;
    Item->SetPos(Vec2(500.f, 500.f));
    Item->SetScale(Vec2(100.f, 100.f));
    AddObject(Item, LAYER_TYPE::ITEM);*/

    /*CMonster_HPbar* HPbar = Instantiate<CMonster_HPbar>(Vec2(490, 50), LAYER_TYPE::ETCUI);
    CMonster_HPbar* HPbar1 = Instantiate<CMonster_HPbar>(Vec2(0, 0), LAYER_TYPE::ETCUI);
    HPbar1->SetHeigth();*/

    
    CreateTile1(4, 3, OBJECT_TYPE::MAP);
    
    CCollisionMgr::GetInst()->clear();
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER_PROJECTILE);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLAYER_PROJECTILE);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::MONSTER);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_PROJECTILE, LAYER_TYPE::TILE);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER_PROJECTILE, LAYER_TYPE::TILE);

    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::TILE);

    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::PROP);
    CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::TILE);
    //CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::TILE, LAYER_TYPE::TILE);

    

    CreateUI();

   
    CScene::SetToolMode(true);
    

}



void CScene_Tool::exit()
{

	
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();

    // 메뉴바를 제거
	CEngine::GetInst()->DetachMenu();

    // UIMgr 클리어
    CUIMgr::GetInst()->clear();

    CScene::SetToolMode(false);

}

Vec2 CScene_Tool::CorrectionPos(Vec2 _Correct)
{
    int Mousex = (int)_Correct.x / 1280;
    int Mousey = (int)_Correct.y / 720;



    if (_Correct.x > 1280)
    {
        for (int i = 0; i < Mousex; i++)
        {
            _Correct.x -= 126;
        }
    }
    if (_Correct.y > 720)
    {
        for (int i = 0; i < Mousey; i++)
        {
            _Correct.y -= 96;
        }
    }

    return _Correct;
}


void CScene_Tool::tick()
{
    /*const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::TILE);
    const vector<CObject*>& m_Player = GetObjects(LAYER_TYPE::PLAYER);
    Vec2 PlayerPos = ((CPlayer*)m_Player[0])->GetPos();
    int iMaxCol = ((CPlayer*)m_Player[0])->GetPos().x / 1280;
    int iMaxRow = ((CPlayer*)m_Player[0])->GetPos().y / 717;
    int iCol = iMaxCol * 15;
    int iRow = iMaxRow * 9;

    int iIdx = iRow * GetTileCol() + iCol;
    
    
    if (m_iMiniMapIdx != iIdx && ((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::MAP)
    {
        ((CTile*)vecObj[m_iMiniMapIdx])->SetMiniMaptypeEntered();
    }  

    if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::MAP)
    {
        ((CTile*)vecObj[iIdx])->SetMiniMaptypeEnter();
        m_iMiniMapIdx = iIdx;
    }*/
        

    CScene::MiniMap();

    switch (m_eMode)
    {
    case TOOL_MODE::MAP:
        TileMode();
        break;
    case TOOL_MODE::TILE:
        TileMode();
        break;
    case TOOL_MODE::OBJECT:
        break;
        
    case TOOL_MODE::ANIMATION: 
        
        break;
    case TOOL_MODE::PLAYER:
        PlayerMode();
        break;
    case TOOL_MODE::MONSTER:
        MonsterMode();
        break;
    case TOOL_MODE::ITEM:
        ItemMode();
        break;
    case TOOL_MODE::COLLIDER:
        ColliderMode();
        break;
    case TOOL_MODE::NONE:
        TileMode();
        break;
    default:
        break;
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

    if (IsTap(KEY_TYPE::SPACE))
    {
        SceneChange(SCENE_TYPE::START);
    }
   

    CScene::tick();

}
    
    
void CScene_Tool::ResetButtenType()
{
    const vector<CObject*>& vecObj1 = GetObjects(LAYER_TYPE::UI);

    const vector<CUI*>& Buttonobj = ((CUI*)vecObj1[0])->GetChildUI();

    if(Buttonobj.size() == 7)
    {
        ((CButton*)Buttonobj[0])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[1])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[2])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[3])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[4])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[4])->SetIdx(0);
        ((CButton*)Buttonobj[5])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[6])->SetButtonType(OBJECT_TYPE::DEFAULT);

        ((CButton*)Buttonobj[0])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[1])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[2])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[3])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[4])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[5])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[6])->SetButtonType(ITEM_TYPE::END);
        return;
    }
    if (Buttonobj.size() == 8)
    {
        const vector<CUI*>& Buttonobj = ((CUI*)vecObj1[1])->GetChildUI();

        ((CButton*)Buttonobj[0])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[1])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[2])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[3])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[4])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[4])->SetIdx(0);
        ((CButton*)Buttonobj[5])->SetButtonType(OBJECT_TYPE::DEFAULT);
        ((CButton*)Buttonobj[6])->SetButtonType(OBJECT_TYPE::DEFAULT);

        ((CButton*)Buttonobj[0])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[1])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[2])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[3])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[4])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[5])->SetButtonType(ITEM_TYPE::END);
        ((CButton*)Buttonobj[6])->SetButtonType(ITEM_TYPE::END);
        return;
    }
}



void CScene_Tool::TileMode()
{
    const vector<CObject*>& vecObj1 = GetObjects(LAYER_TYPE::UI);

    const vector<CUI*>& Buttonobj = ((CUI*)vecObj1[0])->GetChildUI();


    if (m_eMode == TOOL_MODE::NONE && MAPButton == 0 && Buttonobj.size() == 7)
    {
        MAPButton = 1;

        ResetButtenType();
        ((CButton*)Buttonobj[0])->SetButtonType(OBJECT_TYPE::MAP);
        ((CButton*)Buttonobj[0])->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton), (DWORD_PTR)(OBJECT_TYPE::MAP));
        
        ObjectButton = 0;
    }
    else if (m_eMode == TOOL_MODE::NONE && MAPButton == 0 && Buttonobj.size() == 8)
    {
        MAPButton = 1;

        const vector<CUI*>& Buttonobj = ((CUI*)vecObj1[1])->GetChildUI();

        ResetButtenType();
        ((CButton*)Buttonobj[0])->SetButtonType(OBJECT_TYPE::MAP);
        ((CButton*)Buttonobj[0])->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton), (DWORD_PTR)(OBJECT_TYPE::MAP));
        
        ObjectButton = 0;
    }


    if (m_eMode == TOOL_MODE::TILE && ObjectButton == 0 && Buttonobj.size() == 7)
    {
        ObjectButton = 1;

        ResetButtenType();
        
      
        ((CButton*)Buttonobj[0])->SetButtonType(true);
        ((CButton*)Buttonobj[0])->SetDeletage1(this, ((TAGDELEGATE_FUNC1)&CScene_Tool::SetToolMode), (DWORD_PTR)(TOOL_MODE::COLLIDER));      
        ((CButton*)Buttonobj[1])->SetButtonType(OBJECT_TYPE::STONE);
        ((CButton*)Buttonobj[1])->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton), (DWORD_PTR)(OBJECT_TYPE::STONE));
        ((CButton*)Buttonobj[2])->SetButtonType(OBJECT_TYPE::FIRE);
        ((CButton*)Buttonobj[3])->SetButtonType(OBJECT_TYPE::SHARP);
        ((CButton*)Buttonobj[4])->SetButtonType(OBJECT_TYPE::IRON);
        ((CButton*)Buttonobj[4])->SetIdx(4);
        ((CButton*)Buttonobj[5])->SetButtonType(OBJECT_TYPE::EMPTYAREA);
        ((CButton*)Buttonobj[6])->SetButtonType(OBJECT_TYPE::DOOR);

        MAPButton = 0;

    }

    else if (m_eMode == TOOL_MODE::TILE && ObjectButton == 0 && Buttonobj.size() == 8)
    {
        const vector<CUI*>& Buttonobj = ((CUI*)vecObj1[1])->GetChildUI();

        ObjectButton = 1;
        ResetButtenType();

        ((CButton*)Buttonobj[0])->SetButtonType(true);
        ((CButton*)Buttonobj[0])->SetDeletage1(this, ((TAGDELEGATE_FUNC1)&CScene_Tool::SetToolMode), (DWORD_PTR)(TOOL_MODE::COLLIDER));
        ((CButton*)Buttonobj[1])->SetButtonType(OBJECT_TYPE::STONE);
        ((CButton*)Buttonobj[1])->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton), (DWORD_PTR)(OBJECT_TYPE::STONE));
        ((CButton*)Buttonobj[2])->SetButtonType(OBJECT_TYPE::FIRE);
        ((CButton*)Buttonobj[3])->SetButtonType(OBJECT_TYPE::SHARP);
        ((CButton*)Buttonobj[4])->SetButtonType(OBJECT_TYPE::IRON);
        ((CButton*)Buttonobj[4])->SetIdx(4);
        ((CButton*)Buttonobj[5])->SetButtonType(OBJECT_TYPE::EMPTYAREA);
        ((CButton*)Buttonobj[6])->SetButtonType(OBJECT_TYPE::DOOR);

        MAPButton = 0;
    }

    // 마우스 클릭 시 해당 타일의 이미지 인덱스를 증가시킨다.
    if (IsTap(KEY_TYPE::LBTN))
    {
        ITEMButton = 0;
        PlayerButton = 0;
        MonsterButton = 0;
        
        Vec2 vMousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());

        Vec2 vCameraPos = CCamera::GetInst()->GetLookAt();


        // 1280 720의 해상도가 넘어가면 TILETOOL모드 먹통
        if ((vCameraPos.x + 560.f) < vMousePos.x || (vCameraPos.y + 400.f) < vMousePos.y)
            return;

        vMousePos = CorrectionPos(vMousePos);
        


        int iCol = (int)((vMousePos.x - 63  ) / WALLW_SIZE) ;
        int iRow = (int)((vMousePos.y - 48  ) / WALLH_SIZE) ;
        int iIdx = iRow * GetTileCol() + iCol;

        


        const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::TILE);
       
           

        ((CTile*)vecObj[iIdx])->SetImgIdx(0);
        ((CTile*)vecObj[iIdx])->SetType(m_ToolObjectType);
        for (size_t i = 0; i < m_idx; i++)
        {
            ((CTile*)vecObj[iIdx])->AddImgIdx();

        }
        if (((CTile*)vecObj[iIdx])->GetCollider() != nullptr)
        {
            return;
        }

        // 타일 속에 충돌체 넣기
        if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::MAP)
        {
            ((CTile*)vecObj[iIdx])->SetMiniMap();
            return;
        }
           
        ((CTile*)vecObj[iIdx])->AddComponent(new CCollider);
        if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::SHARP )
        {
            ((CTile*)vecObj[iIdx])->SetColliderScale(Vec2(WALLW_SIZE - 10, WALLH_SIZE - 8));
            ((CTile*)vecObj[iIdx])->SetColliderOffset(Vec2(63 + (WALLW_SIZE / 2), 48 + (WALLH_SIZE / 2)));
            return;
        }
        if (((CTile*)vecObj[iIdx])->GetType() == OBJECT_TYPE::DOOR)
        {
            int m_iImgidx = ((CTile*)vecObj[iIdx])->GetImgIdx();
               if (0 == m_iImgidx || 4 == m_iImgidx || 8 == m_iImgidx || 12 == m_iImgidx || 3 == m_iImgidx || 7 == m_iImgidx || 11 == m_iImgidx || 15 == m_iImgidx)
               {
                   ((CTile*)vecObj[iIdx])->SetColliderScale(Vec2(WALLW_SIZE , WALLH_SIZE/2));
                   ((CTile*)vecObj[iIdx])->SetColliderOffset(Vec2(63 + (WALLW_SIZE / 2), 48 + (WALLH_SIZE / 2)));
                   return;
               }
            ((CTile*)vecObj[iIdx])->SetColliderScale(Vec2(WALLW_SIZE /2, WALLH_SIZE ));
            ((CTile*)vecObj[iIdx])->SetColliderOffset(Vec2(63 + (WALLW_SIZE / 2), 48 + (WALLH_SIZE / 2)));
            return;
        }

        ((CTile*)vecObj[iIdx])->SetColliderScale(Vec2(WALLW_SIZE, WALLH_SIZE));
        ((CTile*)vecObj[iIdx])->SetColliderOffset(Vec2(63 + (WALLW_SIZE / 2), 48 + (WALLH_SIZE / 2)));
       

    }
}

void CScene_Tool::ItemMode()
{

    // 아이템 버튼 클릭시 밑의 UI의 이미지가 바뀐다.
    const vector<CObject*>& vecObj1 = GetObjects(LAYER_TYPE::UI);

    const vector<CUI*>& Buttonobj = ((CUI*)vecObj1[0])->GetChildUI();



    if (m_eMode == TOOL_MODE::ITEM && ITEMButton == 0 && Buttonobj.size() == 7)
    {
        ITEMButton = 1;
        ResetButtenType();
        ((CButton*)Buttonobj[0])->SetButtonType(ITEM_TYPE::REDMUSHROOM);

    }

    else if (m_eMode == TOOL_MODE::ITEM && ITEMButton == 0 && Buttonobj.size() == 8)
    {
        ITEMButton = 1;
        ResetButtenType();
        ((CButton*)Buttonobj[0])->SetButtonType(ITEM_TYPE::REDMUSHROOM);

    }


    if (IsTap(KEY_TYPE::LBTN))
    {
        ObjectButton = 0;
        MAPButton = 0;
        PlayerButton = 0;
        MonsterButton = 0;


        Vec2 vMousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());


        Vec2 vCameraPos = CCamera::GetInst()->GetLookAt();

        // 1280 720의 해상도가 넘어가면 TILETOOL모드 먹통
        if ((vCameraPos.x + 560.f) < vMousePos.x || (vCameraPos.y + 400.f) < vMousePos.y)
            return;
        
        vMousePos = CorrectionPos(vMousePos);


        int iCol = (int)((vMousePos.x - 63) / WALLW_SIZE);
        int iRow = (int)((vMousePos.y - 48) / WALLH_SIZE);
        int iIdx = iRow * GetTileCol() + iCol;

        if (GetTileCol() <= (UINT)iCol || GetTileRow() <= (UINT)iRow
            || vMousePos.x < 0.f || vMousePos.y < 0.f)
        {
            return;
        }


        const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::TILE);
        // Item 생성
        CProp* Prop = Instantiate<CProp>(Vec2(((CTile*)vecObj[iIdx])->GetPos().x + 63, ((CTile*)vecObj[iIdx])->GetPos().y + 48), LAYER_TYPE::PROP);

        CItem* pItem = new CRedmushroom;      
        Vec2 mushroomPos = Prop->GetPos();
        mushroomPos.x += 20;
        mushroomPos.y -= WALLH_SIZE/2;
        pItem->SetPos(mushroomPos);
        AddObject(pItem, LAYER_TYPE::ITEM);
        Prop->SetItem(pItem);
        
    }

}

void CScene_Tool::PlayerMode()
{
    //const vector<CObject*>& vecobj = GetObjects(LAYER_TYPE::PLAYER);
    const vector<CObject*>& vecObj1 = GetObjects(LAYER_TYPE::UI);

    const vector<CUI*>& Buttonobj = ((CUI*)vecObj1[0])->GetChildUI();



    if (m_eMode == TOOL_MODE::PLAYER && PlayerButton == 0 && Buttonobj.size() == 7)
    {
        PlayerButton = 1;
        ResetButtenType();
    }

    else if (m_eMode == TOOL_MODE::PLAYER && PlayerButton == 0 && Buttonobj.size() == 8)
    {
        PlayerButton = 1;
        ResetButtenType();
    }




    
        if (IsTap(KEY_TYPE::LBTN))
        {
            ObjectButton = 0;
            MAPButton = 0;
            ITEMButton = 0;
            MonsterButton = 0;


            Vec2 vMousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());


            Vec2 vCameraPos = CCamera::GetInst()->GetLookAt();

            // 1280 720의 해상도가 넘어가면 TILETOOL모드 먹통
            if ((vCameraPos.x + 560.f) < vMousePos.x || (vCameraPos.y + 400.f) < vMousePos.y)
                return;

            vMousePos = CorrectionPos(vMousePos);


            int iCol = (int)((vMousePos.x - 63) / WALLW_SIZE);
            int iRow = (int)((vMousePos.y - 48) / WALLH_SIZE);
            int iIdx = iRow * GetTileCol() + iCol;

            if (GetTileCol() <= (UINT)iCol || GetTileRow() <= (UINT)iRow
                || vMousePos.x < 0.f || vMousePos.y < 0.f)
            {
                return;
            }


            const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::TILE);
            // 멤버 플레이어를 옮긴다
            const vector<CObject*>& m_Player = GetObjects(LAYER_TYPE::PLAYER);
            ((CPlayer*)m_Player[0])->SetPos(Vec2(((CTile*)vecObj[iIdx])->GetPos().x+101, ((CTile*)vecObj[iIdx])->GetPos().y+48));

            

            
        }
    
}

void CScene_Tool::MonsterMode()
{
    const vector<CObject*>& vecObj1 = GetObjects(LAYER_TYPE::UI);

    const vector<CUI*>& Buttonobj = ((CUI*)vecObj1[0])->GetChildUI();



    if (m_eMode == TOOL_MODE::MONSTER && MonsterButton == 0 && Buttonobj.size() == 7)
    {
        MonsterButton = 1;
        ResetButtenType();
    }

    else if (m_eMode == TOOL_MODE::MONSTER && MonsterButton == 0 && Buttonobj.size() == 8)
    {
        MonsterButton = 1;
        ResetButtenType();
    }



    if (IsTap(KEY_TYPE::LBTN))
    {
        ObjectButton = 0;
        MAPButton = 0;
        ITEMButton = 0;
        PlayerButton = 0;

        Vec2 vMousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());


        Vec2 vCameraPos = CCamera::GetInst()->GetLookAt();

        // 1280 720의 해상도가 넘어가면 TILETOOL모드 먹통
        if ((vCameraPos.x + 560.f) < vMousePos.x || (vCameraPos.y + 400.f) < vMousePos.y)
            return;

        vMousePos = CorrectionPos(vMousePos);


        int iCol = (int)((vMousePos.x - 63) / WALLW_SIZE);
        int iRow = (int)((vMousePos.y - 48) / WALLH_SIZE);
        int iIdx = iRow * GetTileCol() + iCol;

        if (GetTileCol() <= (UINT)iCol || GetTileRow() <= (UINT)iRow
            || vMousePos.x < 0.f || vMousePos.y < 0.f)
        {
            return;
        }


        const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::TILE);
        // Monster 생성
        CObject* pMonster = new CDeadIsaac;
        pMonster->SetPos(Vec2(((CTile*)vecObj[iIdx])->GetPos().x + 101, ((CTile*)vecObj[iIdx])->GetPos().y + 48));
        AddObject(pMonster, LAYER_TYPE::MONSTER);

        
        


    }

}

void CScene_Tool::ColliderMode()
{

    if (IsTap(KEY_TYPE::LBTN))
    {
        static int ObjectButton = 0;
        static int MAPButton = 0;
        static int ITEMButton = 0;
        static int PlayerButton = 0;
        static int MonsterButton = 0;



        Vec2 vMousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());


        Vec2 vCameraPos = CCamera::GetInst()->GetLookAt();

        // 1280 720의 해상도가 넘어가면 TILETOOL모드 먹통
        if ((vCameraPos.x + 480.f) < vMousePos.x || (vCameraPos.y + 320.f) < vMousePos.y)
            return;
        
        vMousePos = CorrectionPos(vMousePos);



        int iCol = (int)((vMousePos.x - 63) / WALLW_SIZE);
        int iRow = (int)((vMousePos.y - 48) / WALLH_SIZE);
        int iIdx = iRow * GetTileCol() + iCol;

        if (GetTileCol() <= (UINT)iCol || GetTileRow() <= (UINT)iRow
            || vMousePos.x < 0.f || vMousePos.y < 0.f)
        {
            return;
        }

        const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::TILE);

        if (ColliderA.x == 0 && ColliderA.y == 0)
        {
            // 충돌체가 없다면 리턴한다.
            if (((CTile*)vecObj[iIdx])->GetCollider() == nullptr)
                return;

            // 처음 클릭시 충돌체의 크기를 없애고 리턴한다.
            ColliderA = ((CTile*)vecObj[iIdx])->GetPos();
            ((CTile*)vecObj[iIdx])->SetColliderScale(Vec2(0, 0));
            return;
        }
            

        ColliderB = ((CTile*)vecObj[iIdx])->GetPos();

        Vec2 ColliderA2 = ColliderA;
        Vec2 ColliderB2 = ColliderB;
        
        ColliderA = CorrectionPos(ColliderA);
        ColliderB = CorrectionPos(ColliderB);

        

        // 두 충돌체의 행렬을 구한다.
        int iColA = (int)ColliderA.x / WALLW_SIZE;
        int iRowA = (int)ColliderA.y / WALLH_SIZE;

        int iColB = (int)ColliderB.x / WALLW_SIZE;
        int iRowB = (int)ColliderB.y / WALLH_SIZE;


        // 처음과 2번째 클릭한 곳 까지 충돌체를 늘린다.
        if (((CTile*)vecObj[iIdx])->GetCollider() == nullptr)
            return;
        

           
                if (ColliderA.x <= ColliderB.x)
                {
                    Vec2 ColliderScale;                  

                    ColliderScale .x = ColliderB2.x - ColliderA2.x + WALLW_SIZE;

                    // 처음 클릭한 위치의 y가 두번째 클릭한 위치보다 작을 경우, A위치 기준 4분면       
                    if (ColliderA2.y <= ColliderB2.y)
                    {
                        ColliderScale.y = ColliderB2.y - ColliderA2.y + WALLH_SIZE;


                    }

                    // 처음 클릭한 위치가 y가 두번째 클릭한 위치보다 클 경우  A위치 기준  2분면
                    else
                    {
                                           
                        
                        // 둘 사이에 있는 모든 오브젝트 충돌체 없애기
                        for (; iRowB <= iRowA; ++iRowB)
                        {
                            for (; iColA <= iColB; ++iColA)
                            {
                                int iIdx1 = iRowB * GetTileCol() + iColA;
                                if (((CTile*)vecObj[iIdx1]) == nullptr  )
                                    return;
                                                                   
                                if(((CTile*)vecObj[iIdx])->GetCollider() != nullptr)
                                    ((CTile*)vecObj[iIdx1])->SetColliderScale(Vec2(0.f, 0.f));
                                
                                
                            }
                            iColA = (int)ColliderA.x / WALLW_SIZE;
                        }
                        ColliderScale.y = ColliderA2.y - ColliderB2.y + WALLH_SIZE;
                        ((CTile*)vecObj[iIdx])->SetColliderScale(ColliderScale);

                        ((CTile*)vecObj[iIdx])->SetColliderOffset((Vec2(-ColliderScale.x / 2.f + 63.f + (WALLW_SIZE), (ColliderScale.y / 2.f + 48.f))));



                        Vec2 collider;
                        ColliderA = collider;
                        ColliderB = collider;
        
                        return;
                    }

                   
                    // 둘 사이에 있는 모든 오브젝트 충돌체 없애기
                    for (; iRowA <= iRowB; ++iRowA)
                    {
                        for (; iColA <= iColB; ++iColA)
                        {

                            int iIdx1 = iRowA * GetTileCol() + iColA;
                            if (((CTile*)vecObj[iIdx1]) == nullptr)
                                return;

                            if (((CTile*)vecObj[iIdx])->GetCollider() != nullptr)
                                ((CTile*)vecObj[iIdx1])->SetColliderScale(Vec2(0.f, 0.f));

                        }
                        iColA = (int)ColliderA.x / WALLW_SIZE;
                    }

                    ((CTile*)vecObj[iIdx])->SetColliderScale(ColliderScale);
                    //((CTile*)vecObj[iIdx])->GetCollider()->SetOffset(Vec2(0, ( - ColliderScale.y / 2)));
                    ((CTile*)vecObj[iIdx])->SetColliderOffset(Vec2(-ColliderScale.x / 2.f + 63.f + (WALLW_SIZE), (-ColliderScale.y / 2.f + 48.f + (WALLH_SIZE))));



                    Vec2 collider;
                    ColliderA = collider;
                    ColliderB = collider;
                } 
                // 처음 클릭한 위치의 x가 두번째 클릭한 위치보다 클 경우
                else
                {
                    Vec2 ColliderScale;

                    ColliderScale.x = ColliderA2.x - ColliderB2.x + WALLW_SIZE;

                    // 처음 클릭한 위치의 y가 두번째 클릭한 위치보다 클 경우  A위치 기준 3분면
                    if (ColliderA2.y <= ColliderB2.y)
                    {
                        ColliderScale.y = ColliderB2.y - ColliderA2.y + WALLH_SIZE;
                    }

                    //  A위치 기준 1분면
                    else
                    {
                        for (; iRowB <= iRowA; ++iRowB)
                        {
                            for (; iColB <= iColA; ++iColB)
                            {

                                int iIdx1 = iRowB * GetTileCol() + iColB;
                                if (((CTile*)vecObj[iIdx1]) == nullptr)
                                    return;

                                if (((CTile*)vecObj[iIdx])->GetCollider() != nullptr)
                                    ((CTile*)vecObj[iIdx1])->SetColliderScale(Vec2(0.f, 0.f));

                            }
                            iColB = (int)ColliderB.x / WALLW_SIZE;
                        }

                        ColliderScale.y = ColliderA2.y - ColliderB2.y + WALLH_SIZE;

                        ((CTile*)vecObj[iIdx])->SetColliderScale(ColliderScale);
                        //((CTile*)vecObj[iIdx])->GetCollider()->SetOffset(Vec2(0, ( - ColliderScale.y / 2)));
                        ((CTile*)vecObj[iIdx])->SetColliderOffset(Vec2(ColliderScale.x / 2.f + 63.f, (ColliderScale.y / 2.f + 48.f )));


                        Vec2 collider;
                        ColliderA = collider;
                        ColliderB = collider;

                        return;

                    }

                    for (; iRowA <= iRowB; ++iRowA)
                    {
                        for (; iColB <= iColA; ++iColB)
                        {

                            int iIdx1 = iRowA * GetTileCol() + iColB;
                            if (((CTile*)vecObj[iIdx1]) == nullptr)
                                return;

                            if (((CTile*)vecObj[iIdx])->GetCollider() != nullptr)
                                ((CTile*)vecObj[iIdx1])->SetColliderScale(Vec2(0.f, 0.f));

                        }
                        iColB = (int)ColliderB.x / WALLW_SIZE;
                    }

                    ((CTile*)vecObj[iIdx])->SetColliderScale(ColliderScale);
                    ((CTile*)vecObj[iIdx])->SetColliderOffset(Vec2(ColliderScale.x / 2.f + 63.f , (-ColliderScale.y / 2.f + 48.f + WALLH_SIZE)));

                    Vec2 collider;
                    ColliderA = collider;
                    ColliderB = collider;
                }                               
     }               
    }
       




void CScene_Tool::NextButton()
{
    const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::UI);

    const vector<CUI*>& Buttonobj = ((CUI*)vecObj[1])->GetChildUI();


    // 버튼의 인덱스를 더하고 인덱스 값을 타일 인덱스에 보낸다
    for (size_t i = 0; i < Buttonobj.size(); ++i)
    {
        ((CButton*)Buttonobj[0])->AddImgIdx();
        m_idx = ((CButton*)Buttonobj[0])->GetIdx();
        return;
    }
}

void CScene_Tool::PrevButton()
{
    const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::UI);

    const vector<CUI*>& Buttonobj = ((CUI*)vecObj[1])->GetChildUI();


    // 버튼의 인덱스를 빼고 인덱스 값을 타일 인덱스에 보낸다
    for (size_t i = 0; i < Buttonobj.size(); ++i)
    {
        ((CButton*)Buttonobj[0])->minusImgIdx();
        m_idx = ((CButton*)Buttonobj[0])->GetIdx();
        return;
    }
}

void CScene_Tool::SetTileButton(OBJECT_TYPE _tpye)
{
    const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::UI);

    const vector<CUI*>& Buttonobj = ((CUI*)vecObj[0])->GetChildUI();


    // 버튼의 타입을 바꾸고 인덱스를 초기화 한다.
   
    ((CButton*)Buttonobj[0])->SetButtonType(_tpye);
    
    SetObjectType(_tpye);
    m_idx = 0;
    ((CButton*)Buttonobj[0])->SetIdx(0);
       
}














void TileSaveFunc();
void TileLoadFunc();

void CScene_Tool::CreateUI()
{
    Vec2 vResolution = CEngine::GetInst()->GetResolution();

    //PanelUI
    CPanelUI* pPanel = new CPanelUI;
    pPanel->SetScale(Vec2(320.f, 900.f));
    pPanel->SetPos(Vec2(vResolution.x - pPanel->GetScale().x, 0.f));



    // ButtonUi
    // 보여지는 그림
    CButton* pButton = new CButton;
    pButton->SetScale(Vec2(220.f, 150.f));
    pButton->SetPos(Vec2(50.f, 50.f));
    pButton->SetButtonType(OBJECT_TYPE::MAP);
    // pButton->SetCallBack(&TileSaveFunc);
    
    pPanel->AddChildUi(pButton);

   
    
    // 이전 버트
   CTagButton* pNextPrebutton = new CTagButton;
   pNextPrebutton->SetScale(Vec2(100.f, 50.f));
   pNextPrebutton->SetPos(Vec2(30.f, 220.f));
   pNextPrebutton->SetbuttonIdx(1);
   // pButton->SetCallBack(&TileSaveFunc);
   pNextPrebutton->SetDeletage(this, (TAGDELEGATE_FUNC)&CScene_Tool::PrevButton);
   pPanel->AddChildUi(pNextPrebutton);

   // 다음 버튼
   pNextPrebutton = new CTagButton;
   pNextPrebutton->SetScale(Vec2(100.f, 50.f));
   pNextPrebutton->SetPos(Vec2(pPanel->GetScale().x - 30.f - pNextPrebutton->GetScale().x, 220.f));
   // pButton->SetCallBack(&TileSaveFunc);
   pNextPrebutton->SetDeletage(this, (TAGDELEGATE_FUNC)&CScene_Tool::NextButton);
   pPanel->AddChildUi(pNextPrebutton);

   // MAP 버튼
   pNextPrebutton = new CTagButton;
   pNextPrebutton->SetScale(Vec2(220.f, 100.f));
   pNextPrebutton->SetPos(Vec2(50.f, 290.f));
   pNextPrebutton->SetbuttonIdx(2);
   //// pButton->SetCallBack(&TileSaveFunc);
   pNextPrebutton->SetDeletage1(this, ((TAGDELEGATE_FUNC1)&CScene_Tool::SetToolMode),(DWORD_PTR)(TOOL_MODE::NONE));
   pPanel->AddChildUi(pNextPrebutton);

   // OBJECT 버튼
   pNextPrebutton = new CTagButton;
   pNextPrebutton->SetScale(Vec2(220.f, 100.f));
   pNextPrebutton->SetPos(Vec2(50.f, 410.f));
   pNextPrebutton->SetbuttonIdx(3);
   //// pButton->SetCallBack(&TileSaveFunc);
   pNextPrebutton->SetDeletage1(this, ((TAGDELEGATE_FUNC1)&CScene_Tool::SetToolMode), (DWORD_PTR)(TOOL_MODE::TILE));
   pPanel->AddChildUi(pNextPrebutton);

   // ITEM 버튼
   pNextPrebutton = new CTagButton;
   pNextPrebutton->SetScale(Vec2(220.f, 100.f));
   pNextPrebutton->SetPos(Vec2(50.f, 530.f));
   pNextPrebutton->SetbuttonIdx(4);
   //// pButton->SetCallBack(&TileSaveFunc);
   pNextPrebutton->SetDeletage1(this, ((TAGDELEGATE_FUNC1)&CScene_Tool::SetToolMode), (DWORD_PTR)(TOOL_MODE::ITEM));
   pPanel->AddChildUi(pNextPrebutton);

   // PLAYER 버튼
   pNextPrebutton = new CTagButton;
   pNextPrebutton->SetScale(Vec2(220.f, 100.f));
   pNextPrebutton->SetPos(Vec2(50.f, 650.f));
   pNextPrebutton->SetbuttonIdx(5);
   //// pButton->SetCallBack(&TileSaveFunc);
   pNextPrebutton->SetDeletage1(this, ((TAGDELEGATE_FUNC1)&CScene_Tool::SetToolMode), (DWORD_PTR)(TOOL_MODE::PLAYER));
   pPanel->AddChildUi(pNextPrebutton);

   // MONSTER 버튼
   pNextPrebutton = new CTagButton;
   pNextPrebutton->SetScale(Vec2(220.f, 100.f));
   pNextPrebutton->SetPos(Vec2(50.f, 770.f));
   pNextPrebutton->SetbuttonIdx(6);
   //// pButton->SetCallBack(&TileSaveFunc);
   pNextPrebutton->SetDeletage1(this, ((TAGDELEGATE_FUNC1)&CScene_Tool::SetToolMode), (DWORD_PTR)(TOOL_MODE::MONSTER));
   pPanel->AddChildUi(pNextPrebutton);
    AddObject(pPanel, LAYER_TYPE::UI);
    

    float scale = 4;
    float posx = 100;
   // PanelUI 
    CPanelUI* pPanel1 = new CPanelUI;
   pPanel1->SetScale(Vec2(1280.f, 180.f));
   pPanel1->SetPos(Vec2(0.f, vResolution.y - pPanel1->GetScale().y));

   // 오브젝트 종류 별 이미지 출력
   // 맵
   pButton = new CButton;
   pButton->SetScale(Vec2(TILE_SIZE* scale, TILE_SIZE* scale));
   pButton->SetPos(Vec2(posx, 50.f));
   pButton->SetButtonType(OBJECT_TYPE::DEFAULT);
   // pButton->SetCallBack(&TileSaveFunc);
   pButton->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton),(DWORD_PTR)(OBJECT_TYPE::MAP));
   pPanel1->AddChildUi(pButton);

   posx += 150;

   // 돌
   pButton = new CButton;
   pButton->SetScale(Vec2(TILE_SIZE * scale, TILE_SIZE * scale));
   pButton->SetPos(Vec2(posx, 50.f));
   pButton->SetButtonType(OBJECT_TYPE::DEFAULT);
   // pButton->SetCallBack(&TileSaveFunc);
   pButton->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton),(DWORD_PTR)(OBJECT_TYPE::STONE));
   pPanel1->AddChildUi(pButton);

   posx += 150;
   
   // 불
   pButton = new CButton;
   pButton->SetScale(Vec2(TILE_SIZE * scale, TILE_SIZE * scale));
   pButton->SetPos(Vec2(posx, 50.f));
   pButton->SetButtonType(OBJECT_TYPE::DEFAULT);
   // pButton->SetCallBack(&TileSaveFunc);
   pButton->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton), (DWORD_PTR)(OBJECT_TYPE::FIRE));
   pPanel1->AddChildUi(pButton);

   posx += 150;

   // 가시
   pButton = new CButton;
   pButton->SetScale(Vec2(TILE_SIZE * scale, TILE_SIZE * scale));
   pButton->SetPos(Vec2(posx, 50.f));
   pButton->SetButtonType(OBJECT_TYPE::DEFAULT);
   // pButton->SetCallBack(&TileSaveFunc);
   pButton->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton), (DWORD_PTR)(OBJECT_TYPE::SHARP));
   pPanel1->AddChildUi(pButton);

   posx += 150;

   // 철 돌이랑 이미지 똑같음
   pButton = new CButton;
   pButton->SetScale(Vec2(TILE_SIZE * scale, TILE_SIZE * scale));
   pButton->SetPos(Vec2(posx, 50.f));
   pButton->SetButtonType(OBJECT_TYPE::DEFAULT);
   //pButton->SetIdx(4);
   // pButton->SetCallBack(&TileSaveFunc);
   pButton->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton), (DWORD_PTR)(OBJECT_TYPE::IRON));
   pPanel1->AddChildUi(pButton);

   posx += 150;

   // 떨어지는 공간
   pButton = new CButton;
   pButton->SetScale(Vec2(TILE_SIZE* scale, TILE_SIZE* scale));
   pButton->SetPos(Vec2(posx, 50.f));
   pButton->SetButtonType(OBJECT_TYPE::DEFAULT);
   // pButton->SetCallBack(&TileSaveFunc);
   pButton->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton), (DWORD_PTR)(OBJECT_TYPE::EMPTYAREA));
   pPanel1->AddChildUi(pButton);

   posx += 150;

   // 문
   pButton = new CButton;
   pButton->SetScale(Vec2(TILE_SIZE* scale, TILE_SIZE* scale));
   pButton->SetPos(Vec2(posx, 50.f));
   pButton->SetButtonType(OBJECT_TYPE::DEFAULT);
   // pButton->SetCallBack(&TileSaveFunc);
   pButton->SetDeletage1(this, ((DELEGATE_FUNC1)&CScene_Tool::SetTileButton), (DWORD_PTR)(OBJECT_TYPE::DOOR));
   pPanel1->AddChildUi(pButton);


   AddObject(pPanel1, LAYER_TYPE::UI);

}









void CScene_Tool::TileSave()
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
    ofn.lpstrFilter = L"Tile\0*.tile\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (false == GetSaveFileName(&ofn))
        return;

    // 파일 입출력
    FILE* pFile = nullptr;

    // 쓰기 모드로 열기
    _wfopen_s(&pFile, szFilePath, L"wb");

    if (nullptr == pFile)
        return;

    // 타일 가로 세로 개수
    UINT iCol = GetTileCol();
    UINT iRow = GetTileRow();

    UINT iMapCol = GetTileMapCol();
    UINT iMapRow = GetTileMapRow();



    fwrite(&iCol, sizeof(UINT), 1, pFile);
    fwrite(&iRow, sizeof(UINT), 1, pFile);
    fwrite(&iMapCol, sizeof(UINT), 1, pFile);
    fwrite(&iMapRow, sizeof(UINT), 1, pFile);

    


    const vector<CObject*>& vecTileMap = GetObjects(LAYER_TYPE::MAP);
    for (size_t i = 0; i < vecTileMap.size(); ++i)
    {
        CTile* pTile = (CTile*)vecTileMap[i];
        pTile->Save(pFile);

    }

    const vector<CObject*>& vecTile = GetObjects(LAYER_TYPE::TILE);
    for (size_t i = 0; i < vecTile.size(); ++i)
    {
        CTile* pTile = (CTile*)vecTile[i];
        pTile->Save(pFile);

    }

    fclose(pFile);
}

void CScene_Tool::TileLoad()
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

    if (false == GetOpenFileName(&ofn))
        return;

 

    // 파일 입출력
    FILE* pFile = nullptr;




    //// 실행경로 가져오기
    //GetCurrentDirectory(256, szFilePath);

    //// 상위폴더로 변경
    //size_t iLen = wcsnlen_s(szFilePath, 256);
    //for (size_t i = iLen; i > 0; --i)
    //{
    //    if (L'\\' == szFilePath[i])
    //    {
    //        szFilePath[i + 1] = L'\0';
    //        break;
    //    }

    //    continue;
    //}

    //// + L"bin\\content"
    //wcscat_s(szFilePath, L"bin\\content\\Save\\125");





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
            pTile->GetCollider()->SetScale(pTile->GetColliderSacle());
            pTile->GetCollider()->SetOffset(pTile->GetColliderOffset());

            if (OBJECT_TYPE::MAP == pTile->GetType())
            pTile->SetMiniMap();
        }
    }

    fclose(pFile);
}


















//======================
//Tile Count Dialog Proc
//======================

INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
    {
        switch (wParam)
        {
        case IDOK:
            if (LOWORD(wParam)== IDOK)
            {
                // Edit Control 에 입력한 수치를 알아낸다.
                UINT iCol = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
                UINT iRol = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

                CScene* pScene = CSceneMgr::GetInst()->GetCurScene();
                if (nullptr == dynamic_cast<CScene_Tool*>(pScene))
                {
                    MessageBox(nullptr, L"에러", L"에러", MB_OK);
                }

                pScene->CreateTile1(iCol, iRol, OBJECT_TYPE::MAP);
            }
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
       
        }
    }
    break;
    }
    return (INT_PTR)FALSE;
}
void TileSaveFunc()
{
    // TileSave
    CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(CSceneMgr::GetInst()->GetCurScene());
    if (nullptr != pToolScene)
        pToolScene->TileSave();
}


void TileLoadFunc()
{
    CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(CSceneMgr::GetInst()->GetCurScene());
    if (nullptr != pToolScene)
        pToolScene->TileLoad();
}