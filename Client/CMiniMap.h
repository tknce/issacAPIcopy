#pragma once
#include "CObject.h"

//class CImage;

class CMiniMap :
    public CObject
{
    CImage* m_CImage;
    int     m_iMinimaptype;
    int     m_iAlpha;
    int     m_iImagetype;

public:

    

    virtual void tick() override;
    virtual void render(HDC _dc) override;


public:
    void SetMiniMaptype() { m_iMinimaptype = 2; m_iAlpha = 125; }
    void SetMiniMaptype(int _type) { m_iMinimaptype = _type; }
    void SetMiniMapEnter() { m_iImagetype = 52; }
    void SetMiniMapEntered() { m_iImagetype = 26; }

public:
    CLONE(CMiniMap);

public:

    CMiniMap();
    ~CMiniMap();
};

