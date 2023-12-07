#pragma once
#include "CState.h"

class CPlayer;

class CTeleportTrance :
    public CState
{

    CPlayer*    m_pPlayer;

    int         m_iTeleportIdx;

    float       m_fAcctime;

public:

    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

    void TelePort();

public:
    CLONE(CTeleportTrance);

public:
    CTeleportTrance();
    ~CTeleportTrance();


};

