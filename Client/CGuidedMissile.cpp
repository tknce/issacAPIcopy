#include "pch.h"
#include "CGuidedMissile.h"

#include "CTimeMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CMonster.h"
#include "CCollider.h"



CGuidedMissile::CGuidedMissile()
	: m_pTarget(nullptr)
	, m_fRotateSpeed(100.f)
	, m_fDetectRange(1000.f)
{
}

CGuidedMissile::~CGuidedMissile()
{
}


void CGuidedMissile::tick()
{
	FindTarget();

	if (nullptr != m_pTarget)
	{
		//Ÿ���� ���ؼ� ������ ȸ���Ѵ�.
		Vec2 vMonPos = m_pTarget->GetPos();
		Vec2 vMissilePos = GetPos();

		Vec2 vDirToMon = vMonPos - vMissilePos;
		Vec2 vMissileDir = GetDir();

		vDirToMon.Normalize();
		vMissileDir.Normalize();

		float fDot = vMissileDir.Dot(vDirToMon);
		float fAngle = acosf(fDot); // �̻����� �������� ���͸� ���ϴ� ���� ������ ������ ����
		fAngle = (fAngle / PI) * 180.f; // Radian to Degree

		float fRotateAngle = m_fRotateSpeed * DT; // ȸ�� ���� ũ��

		if (fAngle < fRotateAngle)
		{
			fRotateAngle = fAngle;
		}

		if (0.f < CrossVector(vDirToMon, vMissileDir))
			fRotateAngle *= -1.f;

		vMissileDir = RotateVector(vMissileDir, fRotateAngle);
		SetDir(vMissileDir);	
	}

	CMissile::tick();
}



void CGuidedMissile::FindTarget()
{
	if (IsValid(m_pTarget))
		return;

	Vec2 vMissilePos = GetPos();

	// ���� Scene�� ã�´�
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Monster Layer�� �����´�.
	const vector<CObject*>& vecMon = pCurScene->GetObjects(LAYER_TYPE::MONSTER);

	float fDistance = m_fDetectRange;
	for (size_t i = 0; i < vecMon.size(); ++i)
	{
		float fDist = vMissilePos.Distance(vecMon[i]->GetPos());

		if (fDist < fDistance)
		{
			fDistance = fDist;
			m_pTarget = vecMon[i];
		}

	}
	
}

void CGuidedMissile::render(HDC _dc)
{
	CMissile::render(_dc);
}

void CGuidedMissile::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	if (dynamic_cast<CMonster*>(_pOhterCollider->GetOwner()))
	{
		DeleteObject(this);
	}
}

