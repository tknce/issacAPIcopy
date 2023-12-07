#pragma once
#include "CMonster.h"


class CAngel :
    public CMonster
{
    CImage* m_pImage;

public:

    virtual void tick() override;

    CLONE(CAngel);

public:
    CAngel();
    ~CAngel();
};

