#pragma once
#include "CObject.h"
class CEnding :
    public CObject
{
    CImage* m_pImage;

    int     m_iImageIdx;

    float   m_fAcctime;

    bool    m_bSetPlay;

public:
    virtual void tick() override;

    void SetBox() { m_iImageIdx = 7; }
    void SetBackground() { m_iImageIdx = 8; }


    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;

public:
    CLONE(CEnding);
public:
    CEnding();
    ~CEnding();
};

