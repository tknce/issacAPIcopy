#pragma once
#include "CComponent.h"

union COLLIDER_ID
{
    struct
    {
        UINT LEFT_ID;
        UINT RIGHT_ID;
    };
    LONGLONG ID;
};


class CCollider :
    public CComponent
{
private:
    Vec2        m_vOffsetPos;   // Object �� ���� ������� �Ÿ�
    Vec2        m_vScale;
    Vec2        m_vFinalPos;    // �浹ü�� ���� ��ġ

    int         m_iCollisionCount; // �浹 Ƚ��

public:
    void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
    void SetOffset(Vec2 _vOffset) { m_vOffsetPos = _vOffset; }
    void SetCount(int _iCount) { m_iCollisionCount -= _iCount; }
    void SetFinalPos(Vec2 FinalPos) { m_vFinalPos = FinalPos; }


    Vec2 GetFinalPos() const { return m_vFinalPos;}
    Vec2 GetScale() const { return m_vScale; }

  



public:    
    // �浹�� ó�� �߻��ϴ� ����
    void CollisionBeginOverlap(CCollider* _pOtherCollider);   

    // �浹 ���̴�.
    void CollisionOverlap(CCollider* _pOtherCollider);

    // �浹�� ������� ����
    void CollisionEndOverlap(CCollider* _pOtherCollider);
  
public:
    CLONE(CCollider);

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CCollider();
    CCollider(const CCollider& _collider);
    ~CCollider();
};

