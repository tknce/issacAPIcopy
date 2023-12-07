#pragma once
#include "CObject.h"

class CImage;
class CPlayer;

class CMonster :
    public CObject
{
private:
    tMonsterInfo    m_info;
    



protected:
    tMonsterInfo& GetInfo1() { return m_info; }


public:    
    
    const tMonsterInfo& GetInfo() { return m_info; }

    void MonsterDemage(float Demage) { m_info.fCurHP = m_info.fCurHP - Demage; }


    virtual void tick() override;


    virtual CObject* Clone() = 0;

   /* void ThreeMissile();
    void GreatMissile();*/

public:
    CMonster();
    ~CMonster();

    friend class CMonsterTear;
};

