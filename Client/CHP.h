#pragma once
#include "CObject.h"
class CHP :
    public CObject
{
    CImage* m_CHP;



    float         m_IHP;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    void SetHP(float _HP) { m_IHP = _HP; }
    void SetMaxHP(float _HP) { m_IHP = _HP; }


public:
    CLONE(CHP);
public:
    CHP();
    ~CHP();
};

