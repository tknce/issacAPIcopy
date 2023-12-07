#pragma once
#include "CUI.h"


typedef void(*PFUNC)(void);
typedef void(*PFUNC1)(DWORD_PTR);
typedef void(*PFUNC2)(DWORD_PTR,DWORD_PTR);

typedef void(CEntity::* DELEGATE_FUNC)(void);
typedef void(CEntity::* DELEGATE_FUNC1)(DWORD_PTR);
typedef void(CEntity::* DELEGATE_FUNC2)(DWORD_PTR, DWORD_PTR);

struct  BtnDelegate
{
    CEntity*        pInst;
    DELEGATE_FUNC   pFunc;

    bool isValid()
    {
        if (pInst && pFunc)
        {
            return true;
        }
        return false;
    }

    BtnDelegate()
        : pInst(nullptr)
        , pFunc(nullptr)
    {}
};

struct  BtnDelegate1
{
    CEntity* pInst;
    DELEGATE_FUNC1   pFunc;
    DWORD_PTR       pPtr;

    bool isValid()
    {
        if (pInst && pFunc && pPtr)
        {
            return true;
        }
        return false;
    }

    BtnDelegate1()
        : pInst(nullptr)
        , pFunc(nullptr)
        , pPtr(0)
    {}
};




class CButton :
    public CUI
{
private:
    // 함수 포인터
    PFUNC           m_pFuncPointer;
    BtnDelegate     m_Delegate;
    BtnDelegate1    m_Delegate1;

    CImage*         m_pButtenAtlas;

    OBJECT_TYPE     m_ButtonType;

    ITEM_TYPE       m_ButtonItemType;

    bool            m_bCollidermode;

    int             m_iImgIdx;

public:
    void SetCallBack(PFUNC _pCallBack)
    {
        m_pFuncPointer = _pCallBack;
    }

    void SetDeletage(CEntity* _pInst, DELEGATE_FUNC _pFunc)
    {
        m_Delegate.pInst = _pInst;
        m_Delegate.pFunc = _pFunc;
    }

    void SetDeletage1(CEntity* _pInst, DELEGATE_FUNC1 _pFunc, DWORD_PTR _pPtr)
    {
        m_Delegate1.pInst = _pInst;
        m_Delegate1.pFunc = _pFunc;
        m_Delegate1.pPtr  = _pPtr;
        
    }
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void LBtnClicked() override;
public:
    void    SetIdx(int _Idx) { m_iImgIdx = _Idx; }
    void    SetImg(CImage* _ButtonAtlas) { m_pButtenAtlas = _ButtonAtlas; }
    void    SetButtonType(OBJECT_TYPE _type) { m_ButtonType = _type; }
    void    SetButtonType(ITEM_TYPE _type) { m_ButtonItemType = _type;  m_ButtonType = OBJECT_TYPE::DEFAULT;}
    void    SetButtonType(bool _button) { m_bCollidermode = _button; }

    OBJECT_TYPE GetType() { return m_ButtonType; }

    
    void    AddImgIdx();
    void    minusImgIdx();
    
    int     GetIdx() { return  m_iImgIdx; }

public:
    CLONE(CButton);

public:
    CButton();
    ~CButton();

};

