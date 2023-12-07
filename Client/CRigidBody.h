#pragma once
#include "CComponent.h"
class CRigidBody :
    public CComponent
{
private:
    Vec2    m_vForce;
    Vec2    m_vAccel;
    Vec2    m_vVelocity;

    float   m_fMass;
    float   m_fFriction;
    float   m_fMaxSpeed;            // �߷��� �ƴ� �ִ� �ӷ� ����
    float   m_fMaxGravitySpeed;     // �߷¿� ���� �߻��ϴ� �ִ� �ӷ� ����

    Vec2    m_vGravityAccel;        // �߷� ���ӵ�
    bool    m_bUseGravity;          // �߷� ����
    bool    m_bGround;              // ���� ���ִ��� Ȯ��


public:
    virtual void tick() override;


public:
    void AddForce(Vec2 _vF) { m_vForce += _vF; }
    void AddVelocity(Vec2 _vVelocity) {m_vVelocity += _vVelocity;}
    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
    Vec2 GetVelocity() { return m_vVelocity; }

    void SetMass(float _fMass) { m_fMass = _fMass; }
    void SetMaxSpeed(float _fMax) { m_fMaxSpeed = _fMax; }
    void SetMaxGravitySpeed(float _fMax) { m_fMaxGravitySpeed = _fMax; }
    void SetGravity(bool _bSet) { m_bUseGravity = _bSet; }
    void SetGravityAccel(Vec2 _vAccel) { m_vGravityAccel = _vAccel; }
    void SetGround(bool _bGround) { m_bGround = _bGround; }

    bool isGround() { return m_bGround; }

public:
    CLONE(CRigidBody);


public:
    CRigidBody();
    ~CRigidBody();
};

