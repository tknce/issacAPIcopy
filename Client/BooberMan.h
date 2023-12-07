#pragma once
#include "CMonster.h"
class BooberMan :
    public CMonster
{



public:
    virtual void tick() override;
    

public:
    virtual BooberMan* Clone() { return new BooberMan(*this); }

public:
    BooberMan();
    ~BooberMan();
};

