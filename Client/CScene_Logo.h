#pragma once
#include "CScene.h"
class CScene_Logo :
    public CScene
{
    float m_fAcctime;

    bool    m_bNext;

    


public:
    virtual void enter() override;
    virtual void exit() override;
    virtual void tick() override;

public:
    CScene_Logo();
    ~CScene_Logo();
    
};

