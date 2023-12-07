#pragma once
#include "CState.h"

class CPlayer;

class CIdle :
    public CState
{
private:
    CPlayer* m_pPlayer;

    float       m_fAcctime;

    bool        m_bSound;

public:
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

    CLONE(CIdle);
public:
    CIdle();
    ~CIdle();
};

