#pragma once
#include "CObject.h"
class CForce :
    public CObject
{
private:
    float   m_fForce;       // 힘의 크기
    float   m_fRadius;      // 힘의 반경
    float   m_fDuration;    // 힘의 유지 시간

    float   m_fAccTime;     // 누적 시간

public:
    void SetForceInfo(float _fForce, float _fRadius, float m_fDuration)
    {
        m_fForce = _fForce;
        m_fRadius = _fRadius;
        m_fDuration = m_fDuration;
    }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

private:
    void AddForceToLayer(LAYER_TYPE _eType);

public:
    CForce* Clone() { return new CForce(*this); }

public:
    CForce();
    virtual ~CForce();



};

