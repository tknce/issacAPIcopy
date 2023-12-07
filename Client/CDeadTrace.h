#pragma once
#include "CState.h"
class CDeadTrace :
    public CState
{
private:
    CPlayer*    m_pPlayer;

    Vec2        m_vLightPos;
    Vec2        m_vMonsterLookat;

    tMonsterInfo    m_tMonsterInfo;

    float       m_fAcctime;
    float       m_fAcctime2;
    float       m_fAcctime3;
    float       m_fAcctime4;

public:
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

public:
    void TearModeOne();
    void TearModeThree();
    void TearModeTen();


    CLONE(CDeadTrace);
public:
    CDeadTrace();
    ~CDeadTrace();


};

