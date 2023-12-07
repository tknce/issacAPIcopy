#pragma once
#include "CObject.h"



class CMonster_HPbar :
    public CObject
{
    CImage* m_CMonster_HPbar;

    float   m_fMonster_rate;

    int     m_iHeigth;

public:

    virtual void tick() override;
    virtual void render(HDC _dc) override;

    float SetRate(float _rate) { return m_fMonster_rate -= _rate; }
    void SetHeigth() { m_iHeigth = 0; }

public:
    CLONE(CMonster_HPbar);
public:
    CMonster_HPbar();
    ~CMonster_HPbar();
};

