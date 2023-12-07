#pragma once
#include "CState.h"

class CDeadTrace2 :
    public CState
{
    CPlayer*    m_pPlayer;

    Vec2        m_vLightPos;
    Vec2        m_vMonsterLookat;

    tMonsterInfo    m_tMonsterInfo;

    int         iCount;

    float       m_fAcctime;
    float       m_fAcctime2;
    float       m_fAcctime3;
    float       m_fAcctime4;
    float       Angle ;
    float       Angle2;

    bool        TenAngleMode;

public:
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

public:

    void TearModeOne();
    void TearModeThree();
    void TearModeTen();
    void TearModeTened();


    void RightColumn();

    void CreateRightColumn(int _fwpos, int _fhpos);


public:
    CLONE(CDeadTrace2);
public:
    CDeadTrace2();
    ~CDeadTrace2();
};

