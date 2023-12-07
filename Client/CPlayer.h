#pragma once
#include "CPlayerOwner.h"






class CImage;
class CPlayerHead;
class CHP;

class CPlayer :
    public CPlayerOwner
{
private:
    CPlayerHead*    m_PlayerHead;
    CHP*             m_CHP;

    float           m_fSpeed;
    float           m_fAccTime;
    float           m_fScoTime;
    float           m_fPlayerAngleUD;
    float           m_fPlayerAngleRL;

    bool            m_bUnique;
    bool            m_bSet;
    int             HP;
    int             Score;

    tPlayerInfo     m_PlayerInfo;
    

public:
    virtual void tick() override;
    
    void ScoreUp(int _Scoreup) { Score += _Scoreup; }    
    void SetUnique() { m_bUnique = true; }
    void SetUniquefalse();
    void Demage();
    void GetItem();
    void Healing() { if (m_PlayerInfo.fCurHP > m_PlayerInfo.fMaxHP)return; m_PlayerInfo.fCurHP = m_PlayerInfo.fCurHP + 0.5f; }
    void SetPlayerHead(CPlayerHead* _playerhead) { m_PlayerHead = _playerhead; }

    bool        GetUnique() { return m_bUnique; }
    tPlayerInfo GetPlayerInfo() { return m_PlayerInfo; }
    CPlayer*    GetPlayer() { return this; }

    void SetPlayerInfo(float _attack,float _rance, float _attackspeed, float _curHP, float _shotspeed, float _speed){
        m_PlayerInfo.fAttackPower += _attack;
        m_PlayerInfo.fAttackRance+= _rance;
        m_PlayerInfo.fAttackSpeed-= _attackspeed;
        m_PlayerInfo.fCurHP += _curHP;
        m_PlayerInfo.fShotSpeed+= _shotspeed;
        m_PlayerInfo.fSpeed+=_speed;
    }

public:

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;

public:
    




public:
    virtual CPlayer* Clone() { return new CPlayer(*this); }

public:
    CPlayer();
    ~CPlayer();
};

