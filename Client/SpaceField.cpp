#include "pch.h"
#include "SpaceField.h"
#include "CResMgr.h"


#include "CImage.h"


#include "CCollider.h"
#include "CAnimation.h"
#include "CAnimator.h"


void SpaceField::CollisionEndOverlap(CCollider* _pOhterCollider)
{
}

SpaceField::SpaceField()
	:m_pImage(nullptr)
	, vPos{}

{
	AddComponent(new CCollider);
	AddComponent(new CAnimator);

	m_pImage = CResMgr::GetInst()->LoadImg(L"Test", L"image\\Test.bmp");
	

	GetCollider()->SetOffset(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(2560.f, 1440.f));
	

	/*AddComponent(new CCollider);

	GetCollider()->SetOffset(Vec2(-1280.f, 0.f));
	GetCollider()->SetScale(Vec2(3, 1440.f));

	AddComponent(new CCollider);

	GetCollider()->SetOffset(Vec2(0.f, 1220.f));
	GetCollider()->SetScale(Vec2(2560.f, 2.f));

	AddComponent(new CCollider);

	GetCollider()->SetOffset(Vec2(0.f, -1220.f));
	GetCollider()->SetScale(Vec2(2560.f, -2.f));*/
	

}
//SpaceField::SpaceField(int _i)
//	:m_pImage(nullptr)
//	, vPos{}
//{
//	AddComponent(new CCollider);
//
//	GetCollider()->SetOffset(Vec2(-1280.f, 0.f));
//	GetCollider()->SetScale(Vec2(3, 1440.f));
//}
//SpaceField::SpaceField(float _f)
//	:m_pImage(nullptr)
//	, vPos{}
//{
//	AddComponent(new CCollider);
//
//	GetCollider()->SetOffset(Vec2(0.f, 1220.f));
//	GetCollider()->SetScale(Vec2(2560.f, 2.f));
//}
//SpaceField::SpaceField(char _c)
//	:m_pImage(nullptr)
//	, vPos{}
//{
//	AddComponent(new CCollider);
//
//	GetCollider()->SetOffset(Vec2(0.f, -1220.f));
//	GetCollider()->SetScale(Vec2(2560.f, -2.f));
//}

SpaceField::~SpaceField()
{
}


void SpaceField::tick()
{
	CObject::tick();

}

void SpaceField::render(HDC _dc)
{
	
	

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc, (int)vPos.x - m_pImage->GetWidth() / 2
		, (int)vPos.y - m_pImage->GetHeight() / 2
		, m_pImage->GetWidth(), m_pImage->GetHeight()
		, m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), RGB(255, 0, 255));
	CObject::render(_dc);

}


