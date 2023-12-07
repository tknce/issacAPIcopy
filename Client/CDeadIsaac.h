#pragma once
#include "CMonster.h"
class CMonster_HPbar;

class CDeadIsaac :
    public CMonster
{
    CImage*             m_pImage;
    CMonster_HPbar*     m_Monster_HP;
    CMonster_HPbar*     m_Monster_HPbar;

public:

    virtual void tick() override;

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;

public:
    CMonster_HPbar* GetHPbar() { return m_Monster_HPbar; }

    void SetHPbar();
       
    
public:

    CLONE(CDeadIsaac);

public:
    CDeadIsaac();
    ~CDeadIsaac();
};

