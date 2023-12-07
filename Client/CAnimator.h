#pragma once
#include "CComponent.h"


class CAnimation;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;
    CAnimation*                 m_pCurAnim;


    bool                        m_bRepeat;      // �ݺ����

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    void CreateAnimation(const wstring& _strName, CImage* _pImage
        , Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vPrintSize, Vec2 _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation = true, bool _Blink = false, int _Alpha = 255);

    CAnimation* FindAnimation(const wstring& _strKey);
    void Play(const wstring& _strName, bool _bRepeat);

public:
    CLONE(CAnimator);

public:
    CAnimator();
    CAnimator(const CAnimator& _animator);
    ~CAnimator();
};

