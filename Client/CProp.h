#pragma once
#include "CItem.h"

class CPlayer;
class CProp :
    public CItem
{

    CItem* Item;
    CPlayer* m_pPlayer;

    float   m_fAcctime;

    bool       m_bDelete;

public:

    virtual void tick() override;
    virtual void render(HDC _dc) override;

    void SetItem(CItem* _Item) { Item = _Item; }
    void AddForbidden(CCollider* _pOtherCollider);

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;
    virtual void CollisionOverlap(CCollider* _pOtherCollider) override;
public:
    CLONE(CProp);

public:

    CProp();
    ~CProp();
};

