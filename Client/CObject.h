#pragma once

#include "CEntity.h"
#include "CCamera.h"

class CComponent;
class CCollider;
class CRigidBody;
class CAnimator;
class AI;

class CObject :
    public CEntity
{
private:
    CComponent* m_arrComponent[(UINT)COMPONENT_TYPE::END];

    Vec2        m_vPos;
    Vec2        m_vScale;
    

    bool        m_bDead;


public:
    void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

    Vec2 GetPos() const { return m_vPos; }
    Vec2 GetScale() const { return m_vScale; }

    bool IsDead() const { return m_bDead; }

    AI* GetAI() const { return (AI*)m_arrComponent[(UINT)COMPONENT_TYPE::AI]; }
    CCollider* GetCollider() const { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER]; }
    CAnimator* GetAnimator() const { return (CAnimator*)m_arrComponent[(UINT)COMPONENT_TYPE::ANIMATOR]; }
    CRigidBody* GetRigidBody() const { return (CRigidBody*)m_arrComponent[(UINT)COMPONENT_TYPE::RIGIDBODY]; }

    void AddComponent(CComponent* _pComponent);

 
      

public:
    virtual void tick();
    virtual void render(HDC _dc);

    // 충돌 이벤트
    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) {};
    virtual void CollisionOverlap(CCollider* _pOhterCollider) {};
    virtual void CollisionEndOverlap(CCollider* _pOhterCollider) {};



private:
    void SetDead() { m_bDead = true; }



public:
    virtual CObject* Clone() = 0;

public:
    CObject();    
    CObject(const CObject& _obj);
    virtual ~CObject();

    friend class CEventMgr;
};

