#pragma once
#include "CScene.h"

enum class TOOL_MODE
{
    MAP,
    TILE,
    OBJECT,
    ANIMATION,
    PLAYER,
    MONSTER,
    ITEM,
    DOOR,
    COLLIDER,
    NONE,
};

class CScene_Tool :
    public CScene
{
private:
    TOOL_MODE       m_eMode;

    OBJECT_TYPE     m_ToolObjectType;
    ITEM_TYPE       m_ToolItem_Type;


    

    int             m_idx;


private:

    Vec2 CorrectionPos(Vec2 _Correct);

    void TileMode();
    void ItemMode();
    void PlayerMode();
    void MonsterMode();
    void ColliderMode();
    void CreateUI();
    void NextButton();
    void PrevButton();


    void SetTileButton(OBJECT_TYPE _tpye);
    void SetObjectType(OBJECT_TYPE _tpye) { m_ToolObjectType = _tpye; }
    void ResetButtenType();

    void SetToolMode(TOOL_MODE _Mode) { m_eMode = _Mode; }

    

   


public:
    virtual void tick() override;
    virtual void enter() override;
    virtual void exit() override;

public:
    void TileSave();
    void TileLoad();


    

public:
    CScene_Tool();
    ~CScene_Tool();
};

