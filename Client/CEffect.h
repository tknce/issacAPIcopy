#pragma once
#include "CObject.h"





//class CImage;

class CEffect :
    public CObject
{
    CImage*     m_Image;
    
    Effect      m_Type;

    float       m_fAcctime;


public:

    virtual void tick() override;

    void SetTypeBool(Effect _typebool) { m_Type = _typebool; } 

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pOhterCollider) override;

public:

    CLONE(CEffect);

public:
    CEffect();
    ~CEffect();
};

