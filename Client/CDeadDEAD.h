#pragma once
#include "CState.h"
class CDeadDEAD :
    public CState
{

public:
    virtual void enter() override;
    virtual void tick() override;
    virtual void exit() override;

public:
    CLONE(CDeadDEAD);
public:
    CDeadDEAD();
    ~CDeadDEAD();
};

