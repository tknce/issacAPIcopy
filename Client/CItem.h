#pragma once
#include "CObject.h"


class CImage;
class CPlayer;

class CItem :
    public CObject
{
    CImage*     m_ItemImage;
    ITEM_TYPE   m_Item_type;

    bool        m_bItemExist;

    
    
public:
    
    
    


    CImage* GetImg() { return m_ItemImage; }

    void Delete() { DeleteObject(this); }
    void SetItemType(ITEM_TYPE  _itemtype) { m_Item_type = _itemtype; }
    ITEM_TYPE GetItemType() { return m_Item_type; }

public:
    

    virtual CObject* Clone() = 0;

public:
    CItem();
    ~CItem();
};

