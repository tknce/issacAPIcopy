#pragma once
#include "CObject.h"



class CImge;
class Collider;
class CMiniMap;


class CTile :
    public CObject
{

private:
    CImage*     m_pTileAtlas;   // Ÿ�� �̹��� ����
    int         m_iImgidx;      // Ư�� Ÿ��
    OBJECT_TYPE  m_Objecttype;   // Ÿ�� Ư�� �ٲٱ�
	CMiniMap*	 m_pMiniMap;		// �ʰ� �̴ϸ��� ����

    Vec2        m_VColliderScale;   //�浹ü ũ�� ����
    Vec2        m_VColliderOffset;  //�浹ü ������

	bool		m_bForbiden;		//�浹�� ���°�

public:
    void SetImgIdx(int _iIdx) { m_iImgidx = _iIdx; }
    void SetType(OBJECT_TYPE _objType) { m_Objecttype = _objType; }
    void SetImage(CImage* _image) { m_pTileAtlas = _image; }
    void SetColliderScale(Vec2 _scale);
    void SetColliderOffset(Vec2 _offset);
    void SetScale(Vec2 _scale) { m_VColliderScale = _scale; }
	void SetMiniMap();
	void SetMiniMaptypeEnter();
	void SetMiniMaptypeEntered();
public:
    int GetImgIdx() { return m_iImgidx; }
    OBJECT_TYPE GetType() { return m_Objecttype; }
    Vec2 GetColliderSacle() { return m_VColliderScale; }
    Vec2 GetColliderOffset() { return m_VColliderOffset; }
	 


    
   

public:
    void AddImgIdx();    
    void Typerender(HDC _dc);
    void AddForbidden(CCollider* _pCollider);
	void AddForbidden1(CCollider* _pCollider);


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

public:
    virtual void CollisionBeginOverlap(CCollider* _pCollider) override;
    virtual void CollisionOverlap(CCollider* _pCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pCollider) override;


    virtual CTile* Clone() { return new CTile(*this); }

public:
    CTile();
    ~CTile();



  //  template<typename T>
  //  void AddForbidden1(CCollider* _pCollider)
  //  {
		//T* pPlayer = dynamic_cast<T*>(_pCollider->GetOwner());
		//if (nullptr == pPlayer || !IsValid(pPlayer))
		//	return;
		//float fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().y - GetCollider()->GetFinalPos().y);
		//float fScale = (pPlayer->GetCollider()->GetScale().y / 2.f + (GetCollider()->GetScale().y / 2.f));

		//Vec2 PlayerPos = pPlayer->GetCollider()->GetFinalPos();


		//// Ÿ���� y���� ���ϱ�
		//float if1 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2));
		//float if2 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2)) + GetCollider()->GetScale().y;

		//// Ÿ���� y�� �÷��̾��� y�� ���� �ȿ� �� ������ y�� �ڵ� ����
		//if (PlayerPos.y >= (if1) && PlayerPos.y <= (if2))
		//{
		//	fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().x - GetCollider()->GetFinalPos().x);
		//	fScale = (pPlayer->GetCollider()->GetScale().x / 2.f + (GetCollider()->GetScale().x / 2.f));

		//	// y�࿡�� �����Ѵٸ� �������� ���������� �Ǵ�
		//	if ((pPlayer->GetCollider()->GetFinalPos().x < GetCollider()->GetFinalPos().x))
		//	{
		//		if (fLen < fScale)
		//		{
		//			Vec2 vPlayerPos = pPlayer->GetPos();
		//			vPlayerPos.x -= (fScale - fLen) + 1.f;

		//			pPlayer->SetPos(vPlayerPos);
		//			return;
		//		}
		//	}
		//	else
		//	{
		//		if (fLen < fScale)
		//		{
		//			Vec2 vPlayerPos = pPlayer->GetPos();
		//			vPlayerPos.x += (fScale - fLen) + 1.f;
		//			pPlayer->SetPos(vPlayerPos);
		//			return;
		//		}
		//	}
		//}

		//// x�࿡�� �����Ѵٸ� �������� �ƴ��� �Ǵ�
		//if ((pPlayer->GetCollider()->GetFinalPos().y < GetCollider()->GetFinalPos().y))
		//{
		//	if (fLen < fScale)
		//	{
		//		Vec2 vPlayerPos = pPlayer->GetPos();
		//		vPlayerPos.y -= (fScale - fLen) + 1.f;
		//		pPlayer->SetPos(vPlayerPos);
		//		return;
		//	}
		//}
		//else
		//{
		//	if (fLen < fScale)
		//	{
		//		Vec2 vPlayerPos = pPlayer->GetPos();
		//		vPlayerPos.y += (fScale - fLen) + 1.f;
		//		pPlayer->SetPos(vPlayerPos);
		//		return;
		//	}
		//}
  //  }
};

