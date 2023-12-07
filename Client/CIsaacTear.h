#pragma once
#include "CMissile.h"




class CObject;
class CImage;
class CPlayer;

class CIsaacTear :
    public CMissile
{
    tPlayerInfo     m_PlayerInfo;
    CObject*        m_pPlayer;
    CImage*         m_pTearTDImage;
    CImage*         m_pTearImage;
    
    Vec2            m_fTearAngle;
    Vec2            m_fTearColliderOffset;
    Vec2            m_VMonsterTear;

    Effect          m_PlayerType;

    float           m_fAccTime;    
    float           m_fRotateSpeed; //회전속도
    float           m_fDetectRange;
    float           m_fTearpos;
    float           m_fRotateTear;

    bool            m_bAutoTear;
    bool            m_bTearTD;
    bool            m_bRadian;
    bool            m_bPower;
    

public:
    virtual void tick() override;
    //virtual void render(HDC _dc) override;


public:
   
    void FindTarget();

    void SetTearAngle(Vec2 _tearspeed) { m_fTearAngle = _tearspeed; }
    void SetAutoTear(bool _autotear) { m_bAutoTear = _autotear; }
    void SetAccTime(float _facctime) { m_fAccTime = _facctime; }
    void SetRotateTear(float _rotatetear) { m_fRotateTear = _rotatetear; }
    void SetMonsterTear(Vec2 _MonsterTearAngle) { m_VMonsterTear = _MonsterTearAngle; }
    void SetVecterMode(bool _bool) { m_bRadian = _bool; }
    void SetPlayerMode(Effect _effect) { m_PlayerType = _effect; }


    void Effect();


public:
    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) override;

    CIsaacTear* Clone() { return new CIsaacTear(*this); }

public:
    CIsaacTear();
    ~CIsaacTear();


};

