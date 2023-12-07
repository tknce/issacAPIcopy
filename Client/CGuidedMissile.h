#pragma once
#include "CMissile.h"

class CGuidedMissile :
    public CMissile
{
private:
    CObject*        m_pTarget;      //Ÿ��
    float           m_fRotateSpeed; //ȸ���ӵ�

    float           m_fDetectRange;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

private:
    void FindTarget();

public:
    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) override;


public:
    CGuidedMissile();
    ~CGuidedMissile();
};

