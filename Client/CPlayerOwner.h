#pragma once
#include "CObject.h"


class CPlayerOwner :
    public CObject
{
    bool    m_bHeadState;




public:
    void SetState(bool _state) { m_bHeadState = _state; }
    bool GetState() {return m_bHeadState;}


    virtual CObject* Clone() = 0;
public:
    CPlayerOwner();
    ~CPlayerOwner();
};

