#pragma once

class CObject;
class CImage;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tCamEffectInfo
{
	float		fAccTime;	// ���� ���� �ð�
	float		fDuration;	// ����Ʈ �� ����ð�
	CAM_EFFECT	eEffect;	// ī�޶� ȿ�� Ÿ��
};




class CCamera
{
	SINGLE(CCamera);
private:
	Vec2					m_vResolution;	// ȭ�� �ػ�
	Vec2					m_vLook;		// ���� ī�޶� �����ִ� ��ǥ
	Vec2					m_vDiff;		// ȭ�� �ػ� �߽� ��ǥ�� ���� ī�޶� Look ���� ����
	float					m_shake;		// ȭ�� ���� 
	float					Wiggletime;		// ȭ�� ����� �ð�
	int						m_Score;		// ����


	CObject*				m_pTargetObj;

	// veil
	CImage*					m_pVeil;		// ������ �뵵 BitmapImage ����
	float					m_fAlpha;		// ���� ����
	
	list<tCamEffectInfo>	m_CamEffectInfo;
		
	


public:
	void init(); 
	void tick();	
	void render(HDC _dc);



public:
	Vec2 GetLookAt() { return m_vLook; }
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
	Vec2 GetResolution(){return m_vResolution;}

	void SetTargetObject(CObject* _pObj) { m_pTargetObj = _pObj; }
	void SetLookAt(Vec2 _look) { m_vLook = _look; }
	void SetCameraEffect(CAM_EFFECT _type, float _fDuration)
	{
		tCamEffectInfo info = {};
		info.eEffect = _type;
		info.fDuration = _fDuration;		
		m_CamEffectInfo.push_back(info);
	}

public:	
	void RemoveTargetObject() { m_pTargetObj = nullptr; }
	
public:	
	void WiggleStart() { Wiggletime = 0;}
	void CamaradurationWiggle(Vec2 _WigglePos, float Duration, float WigglePower);
	void ScoreUp(int _Scoreup) { m_Score += _Scoreup; }

private:
	void CamaraWiggle(float WigglePower);
};

