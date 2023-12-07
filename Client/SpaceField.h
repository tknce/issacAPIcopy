#pragma once
#include "CObject.h"

class CImage;

class SpaceField :
    public CObject
{
private:
    CImage* m_pImage;
    Vec2    vPos;
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    SpaceField* Clone() { return new SpaceField; }
    virtual void CollisionEndOverlap(CCollider* _pOhterCollider) override;

public:
    SpaceField();
    ~SpaceField();
};

