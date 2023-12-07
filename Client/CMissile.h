#pragma once
#include "CObject.h"

class CImage;
class CMonster;

class CMissile :
    public CObject
{
private:
    CImage* m_pImage;
    Vec2    m_vDir;


    float   m_Angle;
    


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    void SetDir(Vec2 _vDir)    { m_vDir = _vDir;  m_vDir.Normalize();}
    Vec2 GetDir() { return m_vDir; }

    void SetAngle(float _Angle) { m_Angle = _Angle; }
    float GetAngle() { return m_Angle; }

public:
   



public:
    CMissile();
    
    ~CMissile();
};

