#pragma once
#include "CScene.h"
class CStage_End :
    public CScene
{
public:
    virtual void enter() override;
    virtual void exit() override;
    virtual void tick() override;

public:
    CStage_End();
    ~CStage_End();

};

