#pragma once
#include "CPlayerOwner.h"

class CImage;

class CPlayerHead :
    public CPlayerOwner
{
    CImage* m_PlayerHead;

    float   m_fAcctime;
    
    bool    m_bBool;
    bool    m_bHIt;



public:
    virtual void tick() override;
    
    
   


public:
    virtual CPlayerHead* Clone() { return new CPlayerHead(*this); }

public:
    CPlayerHead();
    ~CPlayerHead();
};

