#pragma once
#include "CObject.h"

class CImage;

class CMain :
    public CObject
{
    CImage* m_CMainImage;

    Vec2        m_VImage;

    bool        m_bnext;

    bool    m_bIntro;

public:
    virtual void tick() override;


public:
    bool GetNext() {       return m_bnext           ;    }
    void Setinter() { m_bIntro = true; }
public:
    CLONE(CMain);
public:

    CMain();
    ~CMain();
};

