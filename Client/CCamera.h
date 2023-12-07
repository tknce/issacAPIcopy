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
	float		fAccTime;	// 누적 진행 시간
	float		fDuration;	// 이펙트 총 재생시간
	CAM_EFFECT	eEffect;	// 카메라 효과 타입
};




class CCamera
{
	SINGLE(CCamera);
private:
	Vec2					m_vResolution;	// 화면 해상도
	Vec2					m_vLook;		// 현재 카메라가 보고있는 좌표
	Vec2					m_vDiff;		// 화면 해상도 중심 좌표와 현재 카메라 Look 간에 차이
	float					m_shake;		// 화면 흔들기 
	float					Wiggletime;		// 화면 흔딜기 시간
	int						m_Score;		// 점수


	CObject*				m_pTargetObj;

	// veil
	CImage*					m_pVeil;		// 가림막 용도 BitmapImage 생성
	float					m_fAlpha;		// 투명 강도
	
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

