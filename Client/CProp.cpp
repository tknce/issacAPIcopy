#include "pch.h"
#include "CProp.h"

#include "CResMgr.h"

#include "CImage.h"
#include "CCollider.h"
#include "CTimeMgr.h"
#include "CSound.h"

#include "CPlayer.h"

CProp::CProp()
	: Item(nullptr)
	, m_fAcctime(0)
	, m_bDelete(false)
	, m_pPlayer(nullptr)
{
	AddComponent(new CCollider);

	GetCollider()->SetScale(Vec2(WALLW_SIZE-10, WALLH_SIZE-10));
	GetCollider()->SetOffset(Vec2(WALLW_SIZE / 2, WALLH_SIZE / 2));
}

CProp::~CProp()
{
}

void CProp::tick()
{
	m_fAcctime += DT;

	if (m_bDelete)
	{
		if (m_fAcctime < 1)
		{

			Vec2 PlayerPos = m_pPlayer->GetPos();
			switch (Item->GetItemType())
			{
			case ITEM_TYPE::REDMUSHROOM:

				PlayerPos.x -= 26.f;
				PlayerPos.y -= 50.f;
				Item->SetPos(PlayerPos);
				break;
			case ITEM_TYPE::END:

				break;
			default:
				break;
			}







		}

		if (m_bDelete && m_fAcctime > 0.9)
		{
			Item->SetItemType(ITEM_TYPE::END);
			DeleteObject(Item);
			m_bDelete = false;
		}
			
	}
	CObject::tick();

}

void CProp::render(HDC _dc)
{
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	TransparentBlt(_dc, vRenderPos.x, vRenderPos.y, WALLW_SIZE, WALLH_SIZE, CItem::GetImg()->GetDC(), 0, 0, 104, 83, RGB(255, 0, 255));

	CObject::render(_dc);
}



void CProp::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;

	if (m_bDelete)
		return;

	m_pPlayer = pPlayer->GetPlayer();
	
	CSound* pBgm = CResMgr::GetInst()->FindSound(L"GetItem");

	m_fAcctime = 0;

	if (Item == nullptr || !IsValid(Item))
		return;

	switch (Item->GetItemType())
	{
	case ITEM_TYPE::REDMUSHROOM:
		
		pPlayer->SetPlayerInfo(3,3,0.05,0,0,0);
		pPlayer->GetItem();
		
		if (nullptr != pBgm)
			pBgm->Play(false);
		m_bDelete = true;
		
		
		
		break;
	case ITEM_TYPE::END:

		break;
	default:
		break;
	}
	



}

void CProp::CollisionOverlap(CCollider* _pOtherCollider)
{
	AddForbidden(_pOtherCollider);
}


void CProp::AddForbidden(CCollider* _pOtherCollider)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_pOtherCollider->GetOwner());
	if (nullptr == pPlayer || !IsValid(pPlayer))
		return;
	float fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().y - GetCollider()->GetFinalPos().y);
	float fScale = (pPlayer->GetCollider()->GetScale().y / 2.f + (GetCollider()->GetScale().y / 2.f));

	Vec2 PlayerPos = pPlayer->GetCollider()->GetFinalPos();


	// 타일의 y값을 구하기
	float if1 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2));
	float if2 = (GetCollider()->GetFinalPos().y - (GetCollider()->GetScale().y / 2)) + GetCollider()->GetScale().y;

	// 타일의 y와 플레이어의 y을 비교해 안에 들어가 있으면 y값 코드 진행
	if (PlayerPos.y >= (if1) && PlayerPos.y <= (if2))
	{
		fLen = (float)fabs(pPlayer->GetCollider()->GetFinalPos().x - GetCollider()->GetFinalPos().x);
		fScale = (pPlayer->GetCollider()->GetScale().x / 2.f + (GetCollider()->GetScale().x / 2.f));

		// y축에서 접근한다면 왼쪽인지 오른쪽인지 판단
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

	// x축에서 접근한다면 위쪽인지 아닌지 판단
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
