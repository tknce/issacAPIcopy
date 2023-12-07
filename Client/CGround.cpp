#include "pch.h"
#include "CGround.h"

#include "CCollider.h"
#include "CRigidBody.h"

#include "CPlayer.h"


CGround::CGround()
{
	AddComponent(new CCollider);
	GetCollider()->SetScale(Vec2(600.f, 50.f));

}

CGround::~CGround()
{
}



void CGround::tick()
{
	CObject::tick();
}

void CGround::CollisionBeginOverlap(CCollider* _pCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;

	//pPlayer->GetRigidBody()->SetGround(true);

	float fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().y - GetCollider()->GetFinalPos().y);
	float fScale = (pPlayer->GetCollider()->GetScale().y / 2.f + (GetCollider()->GetScale().y / 2.f));
	
	Vec2 PlayerPos = pPlayer->GetCollider()->GetFinalPos();

	float if1 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2)) ;
	float if2 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2)) + GetCollider()->GetScale().y;




	if (PlayerPos.y > if1  && PlayerPos.y < if2)
	{
		fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().x - GetCollider()->GetFinalPos().x);
		fScale = (pPlayer->GetCollider()->GetScale().x / 2.f + (GetCollider()->GetScale().x / 2.f));
		if ((pPlayer->GetCollider()->GetFinalPos().x < GetCollider()->GetFinalPos().x))
		{
			if (fLen < fScale)
			{
				Vec2 vPlayerPos = pPlayer->GetPos();
				vPlayerPos.x -= (fScale - fLen) + 1.f;
				pPlayer->SetPos(vPlayerPos);
				return;
			}
		}
		else
		{
			if (fLen < fScale)
			{
				Vec2 vPlayerPos = pPlayer->GetPos();
				vPlayerPos.x += (fScale - fLen) + 1.f;
				pPlayer->SetPos(vPlayerPos);
				return;
			}
		}
	}
	if ((pPlayer->GetCollider()->GetFinalPos().y < GetCollider()->GetFinalPos().y)) 
	{
		if (fLen < fScale)
		{
			Vec2 vPlayerPos = pPlayer->GetPos();
				vPlayerPos.y -= (fScale - fLen) + 1.f;
				pPlayer->SetPos(vPlayerPos);
				return;
		}
	}
	else
	{
		if (fLen < fScale)
		{
			Vec2 vPlayerPos = pPlayer->GetPos();
			vPlayerPos.y += (fScale - fLen) + 1.f;
			pPlayer->SetPos(vPlayerPos);
			return;
		}
	}

	
	
}

void CGround::CollisionOverlap(CCollider* _pCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;
}

void CGround::CollisionEndOverlap(CCollider* _pCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;

	
}

