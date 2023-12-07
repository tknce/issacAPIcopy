#pragma once
#include "CState.h"
class CAngelTrance :
    public CState
{
    CPlayer*        m_pPlayer;

    tMonsterInfo    m_tMonsterInfo;

    float           m_fAcctime;
    float           m_fAcctime2;


public:
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

public:

    void TearModeThree();



    CLONE(CAngelTrance);

    CAngelTrance();
    ~CAngelTrance();

};

