#pragma once
#include "CScene.h"
class CScene_Stage1 :
    public CScene
{

public:
    virtual void enter() override;
    virtual void exit() override;
    virtual void tick() override;

public:
    void TileLoad();
public:
    CScene_Stage1();
    ~CScene_Stage1();
};

