#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::tick()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	for (UINT iRow = 0; iRow < MAX_LAYER; ++iRow)
	{
		for (UINT iCol = iRow; iCol < MAX_LAYER; ++iCol)
		{
			if (m_matrix[iRow] & (1 << iCol))
			{
				CollisionBtwLayer(pCurScene, (LAYER_TYPE)iRow, (LAYER_TYPE)iCol);
			}
		}
	}
}


void CCollisionMgr::CollisionBtwLayer(CScene* _pCurScene, LAYER_TYPE _eLeft, LAYER_TYPE _eRight)
{
	const vector<CObject*>& vecLeft = _pCurScene->GetObjects(_eLeft);
	const vector<CObject*>& vecRight = _pCurScene->GetObjects(_eRight);
		
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		size_t j = 0;
		if (_eLeft == _eRight)
		{
			j = i + 1;
		}
		

		for (; j < vecRight.size(); ++j)
		{
			if (nullptr == vecRight[j]->GetCollider())
			{
				continue;
			}

			CollisionBtwCollider(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider());
		}
	}
}

void CCollisionMgr::CollisionBtwCollider(CCollider* _pLeft, CCollider* _pRight)
{
	// �� �浹ü�� ID �� Ȯ��
	COLLIDER_ID id;
	id.LEFT_ID = _pLeft->GetID();
	id.RIGHT_ID = _pRight->GetID();

	// ���� �浹 ������ �˻��Ѵ�.
	map<LONGLONG, bool>::iterator iter = m_mapColInfo.find(id.ID);

	// �浹������ �ƿ� ������ ������ش�.
	if (iter == m_mapColInfo.end())
	{
		m_mapColInfo.insert(make_pair(id.ID, false));
		iter = m_mapColInfo.find(id.ID);
	}

	// �� �浹ü�� �ϳ� �̻��� Dead �������� �˻�
	bool isDead = _pLeft->GetOwner()->IsDead() || _pRight->GetOwner()->IsDead();

	// ���� �浹������ �˻� �Ѵ�.			
	if (IsCollision(_pLeft, _pRight))
	{
		// �浹 ���̴�.
		if (false == iter->second)
		{
			// ���� �����ӿ��� �浹���� �ʾҴ�.
			// ��--> �̹� �����ӿ� �浹 ����
			_pLeft->CollisionBeginOverlap(_pRight);
			_pRight->CollisionBeginOverlap(_pLeft);
			iter->second = true;
		}
		else
		{
			
			//���� ������ ���, �浹�� ����
			if (isDead)
			{
				_pLeft->CollisionOverlap(_pRight);
				_pRight->CollisionOverlap(_pLeft);
				
				if(isDead != _pLeft->GetOwner()->IsDead())
				_pLeft->SetCount(1);
				if(isDead != _pRight->GetOwner()->IsDead())
				_pRight->SetCount(1);

				iter->second = false;
			}
			
			
			else
			{
				// �������� �浹, ���ݵ� �浹
				_pLeft->CollisionOverlap(_pRight);
				_pRight->CollisionOverlap(_pLeft);
			}
		
		}
	}

	else
	{
		// �浹 X
		if (iter->second)
		{
			// �������� �浹�ϰ� �־���
			// ��--> �浹�� �� ��� ����
			_pLeft->CollisionEndOverlap(_pRight);
			_pRight->CollisionEndOverlap(_pLeft);
			iter->second = false;
		}
	}
}


bool CCollisionMgr::IsCollision(CCollider* _pLeft, CCollider* _pRight)
{
	Vec2 vLeftPos = _pLeft->GetFinalPos();
	Vec2 vLeftScale = _pLeft->GetScale();

	Vec2 vRightPos = _pRight->GetFinalPos();
	Vec2 vRightScale = _pRight->GetScale();


	// �� �浹ü�� �������� �Ÿ���, �� ������ ���ݳ����� ���� ���ؼ� 
	// �� ��(x, y) ���� ��ġ�� �κ��� ���ÿ� �����ϴ��� üũ�Ѵ�.
	if (fabs(vLeftPos.x - vRightPos.x) < (vLeftScale.x / 2.f + vRightScale.x / 2.f) 
		&& fabs(vLeftPos.y - vRightPos.y) < (vLeftScale.y / 2.f + vRightScale.y / 2.f))
	{
		return true;
	}

	return false;
}






void CCollisionMgr::CollisionLayerCheck(LAYER_TYPE _eLeft, LAYER_TYPE _eRight)
{
	// �� ���� ���ڸ� ��(�迭�� �ε���) ����, �� ū ���ڸ� ��(��Ʈ ��ġ) ��
	UINT iRow = 0, iCol = 0;

	if ((UINT)_eLeft <= (UINT)_eRight)
	{
		iRow = (UINT)_eLeft;
		iCol = (UINT)_eRight;
	}
	else
	{
		iRow = (UINT)_eRight; 
		iCol = (UINT)_eLeft;
	}
		
	m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::CollisionLayerRelease(LAYER_TYPE _eLeft, LAYER_TYPE _eRight)
{
	// �� ���� ���ڸ� ��(�迭�� �ε���) ����, �� ū ���ڸ� ��(��Ʈ ��ġ) ��
	UINT iRow = 0, iCol = 0;

	if ((UINT)_eLeft <= (UINT)_eRight)
	{
		iRow = (UINT)_eLeft;
		iCol = (UINT)_eRight;
	}
	else
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	m_matrix[iRow] &= ~(1 << iCol);
}
