#pragma once
#include "CMissile.h"
class CMonsterTear :
    public CMissile
{
    tMonsterInfo     m_MonsterInfo;
    CObject* m_pMonster;
    CImage* m_pTearTDImage;
    CImage* m_pTearImage;

    Vec2            m_fTearAngle;
    Vec2            m_fTearColliderOffset;

    float           m_fAccTime;
    float           m_fRotateSpeed; //회전속도
    float           m_fDetectRange;
    float           m_fTearpos;
    float           m_fRotateTear;

    bool            m_bAutoTear;
    bool            m_bTearTD;

public:
    virtual void tick() override;
    //virtual void render(HDC _dc) override;


public:

    void FindTarget();

    void SetTearAngle(Vec2 _tearspeed) { m_fTearAngle = _tearspeed; }
    void SetAutoTear(bool _autotear) { m_bAutoTear = _autotear; }
    void SetAccTime(float _facctime) { m_fAccTime = _facctime; }
    void SetRotateTear(float _rotatetear) { m_fRotateTear = _rotatetear; }


public:
    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) override;

    CLONE(CMonsterTear);

public:
    CMonsterTear();
    ~CMonsterTear();
};

