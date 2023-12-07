#pragma once
#include "CState.h"
class CDeadTrace3 :
    public CState
{
    CPlayer* m_pPlayer;

    Vec2        m_vLightPos;
    Vec2        m_vMonsterLookat;

    tMonsterInfo    m_tMonsterInfo;


    float       m_fAcctime;
    
    int         m_iCount;


public:
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

public:



    void RightColumn();

    void CreateRightColumn(int _fwpos, int _fhpos);


public:
    CLONE(CDeadTrace3);
public:
    CDeadTrace3();
    ~CDeadTrace3();
};

