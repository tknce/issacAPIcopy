#pragma once
#include "CMonster.h"
class CMiniMonster :
    public CMonster
{


    


    

    virtual void tick() override;
    virtual void render(HDC _dc) override;

    CMiniMonster();
    ~CMiniMonster();
};

