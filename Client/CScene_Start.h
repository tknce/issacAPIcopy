#pragma once
#include "CScene.h"
class CScene_Start :
    public CScene
{

public:
    virtual void enter() override;
    virtual void exit() override;
    virtual void tick() override;

public:
    void TileLoad();
public:
    CScene_Start();
    ~CScene_Start();
};

