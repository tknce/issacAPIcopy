#pragma once
#include "CObject.h"



class CImge;
class Collider;
class CMiniMap;


class CTile :
    public CObject
{

private:
    CImage*     m_pTileAtlas;   // 타일 이미지 모음
    int         m_iImgidx;      // 특정 타일
    OBJECT_TYPE  m_Objecttype;   // 타일 특성 바꾸기
	CMiniMap*	 m_pMiniMap;		// 맵과 미니맵을 연동

    Vec2        m_VColliderScale;   //충돌체 크기 설정
    Vec2        m_VColliderOffset;  //충돌체 오프셋

	bool		m_bForbiden;		//충돌시 상태값

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


		//// 타일의 y값을 구하기
		//float if1 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2));
		//float if2 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2)) + GetCollider()->GetScale().y;

		//// 타일의 y와 플레이어의 y을 비교해 안에 들어가 있으면 y값 코드 진행
		//if (PlayerPos.y >= (if1) && PlayerPos.y <= (if2))
		//{
		//	fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().x - GetCollider()->GetFinalPos().x);
		//	fScale = (pPlayer->GetCollider()->GetScale().x / 2.f + (GetCollider()->GetScale().x / 2.f));

		//	// y축에서 접근한다면 왼쪽인지 오른쪽인지 판단
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

		//// x축에서 접근한다면 위쪽인지 아닌지 판단
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

