#pragma once
#include "CItem.h"
class CRedmushroom :
    public CItem
{



public:
    virtual void tick() override;

    


    
public:




public:
    virtual CRedmushroom* Clone() { return new CRedmushroom(*this); }

public:
    CRedmushroom();
    ~CRedmushroom();
};

