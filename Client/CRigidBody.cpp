#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"

#include "CObject.h"

CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_fMass(1.f)
	, m_fFriction(100.f)
	, m_fMaxSpeed(200.f)
	, m_fMaxGravitySpeed(200.f)
	, m_bUseGravity(false)
	, m_bGround(false)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::tick()
{
	// F = M x A
	m_vAccel = m_vForce / m_fMass;

	// �ӵ��� ���ӵ��� ���Ѵ�.
	m_vVelocity += m_vAccel * DT;

	//// �߷� ���ӵ� ����
	//if (!m_bGround)
	//{
	//	m_vVelocity += m_vGravityAccel * DT;
	//}
	//else
	//{
	//	Vec2 vGravity = m_vGravityAccel;
	//	vGravity.Normalize();
	//	m_vVelocity -= vGravity * m_vVelocity.Dot(vGravity);
	//}

	// �ӵ� ���� ����
	Vec2 vGravity = m_vGravityAccel;

	// �߷��� ������ �Ѿ��.
	if (!m_vGravityAccel.IsZero()) 
	{
		vGravity.Normalize();
		vGravity = vGravity * m_vVelocity.Dot(vGravity); // �ӵ��� �߷¹������� ����
	}
	

	Vec2 vSideVelocity = m_vVelocity - vGravity;

	if (m_fMaxGravitySpeed < vGravity.Length())
	{
		vSideVelocity.Normalize();
		vSideVelocity *= m_fMaxGravitySpeed;
	}


	if (m_fMaxSpeed < vSideVelocity.Length())
	{
		vSideVelocity.Normalize();
		vSideVelocity *= m_fMaxSpeed;
	}

	m_vVelocity = vGravity + vSideVelocity;

	//������ ���� (����� ���� ����, �ӵ��� 0�� �ƴҶ�)
	if (!m_vVelocity.IsZero())
	{
		// �ӵ��� �ݴ�������� �������� ����
		Vec2 vFriction = -m_vVelocity;
		vFriction = vFriction.Normalize() * m_fFriction * DT * m_fMass;

		// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� �� ū ���
		if (m_vVelocity.Length() < vFriction.Length())
		{
			// �ӵ��� 0���� �����
			m_vVelocity = Vec2(0.f,0.f);
		}
		else
		{
			// �ӵ����� ���������� ���� �ݴ�������� �ӵ��� �����Ѵ�.
			m_vVelocity += vFriction;
		}

	}

	// �ӵ��� �°� ��ü�� �̵���Ų��.
	Vec2 vPos = GetOwner()->GetPos() + m_vVelocity * DT;
	GetOwner()->SetPos(vPos);

	m_vForce = Vec2(0.f, 0.f);
}
