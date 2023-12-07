#pragma once
#include "CUI.h"


typedef void(*PFUNC)(void);
typedef void(*PFUNC1)(DWORD_PTR);
typedef void(*PFUNC2)(DWORD_PTR, DWORD_PTR);

typedef void(CEntity::* TAGDELEGATE_FUNC)(void);
typedef void(CEntity::* TAGDELEGATE_FUNC1)(DWORD_PTR);
typedef void(CEntity::* TAGDELEGATE_FUNC2)(DWORD_PTR, DWORD_PTR);

struct TagBtnDelegate
{
    CEntity* pInst;
    TAGDELEGATE_FUNC   pFunc;

    bool IsValid()
    {
        if (pInst && pFunc)
            return true;
        return false;
    }

    TagBtnDelegate()
        : pInst(nullptr)
        , pFunc(nullptr)
    {}
};

struct  TagBtnDelegate1
{
    CEntity* pInst;
    TAGDELEGATE_FUNC1   pFunc;
    DWORD_PTR       pPtr;

    bool isValid()
    {
        if (pInst && pFunc && pPtr)
        {
            return true;
        }
        return false;
    }

    TagBtnDelegate1()
        : pInst(nullptr)
        , pFunc(nullptr)
        , pPtr(0)
    {}
};




class CImage;

class CTagButton :
    public CUI
{
    PFUNC           m_pFuncPointer;
    TagBtnDelegate    m_Delegate;
    TagBtnDelegate1     m_Delegate1;
    CImage*         m_pNextPreButtenAtlas;
    int             m_iImgIdx;

public:
    void SetCallBack(PFUNC _pCallBack)
    {
        m_pFuncPointer = _pCallBack;
    }

    void SetDeletage(CEntity* _pInst, TAGDELEGATE_FUNC _pFunc)
    {
        m_Delegate.pInst = _pInst;
        m_Delegate.pFunc = _pFunc;
    }

    void SetDeletage1(CEntity* _pInst, TAGDELEGATE_FUNC1 _pFunc, DWORD_PTR _pPtr)
    {
        m_Delegate1.pInst = _pInst;
        m_Delegate1.pFunc = _pFunc;
        m_Delegate1.pPtr = _pPtr;
    }


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
    virtual void LBtnClicked() override;


public:
    void    SetImg(CImage* _Img) { m_pNextPreButtenAtlas = _Img; }
    void    SetbuttonIdx(int _Idx) { m_iImgIdx = _Idx; } 

        


public:
    CLONE(CTagButton);

public:
    CTagButton();
    ~CTagButton();


};

