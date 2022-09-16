#include "Explosion.hpp"
#include "SpriteIDServer.hpp"
#include "GameScore.hpp"
#include <time.h>

Explosion::Explosion( float m_X, Collectable* p_TargetFire ) : 
explosionDuration(2.0f), currentExplositionDuration(0.0f)
{
    size.x = 32.0f;
    size.y = 64.0f;
    
    pos.x = m_X;
    targetFire = p_TargetFire;

    active = true;
    spriteID = SpriteIDServer::GetInstance().GetID();

    //Create it and then hide it
    NF_CreateSprite(0,spriteID,4,4, pos.x, pos.y);
    NF_ShowSprite(0,spriteID, true);
}
int Explosion::ClassType()
{
    return 6;
} 

void Explosion::SetActive( float m_Y )
{
    pos.y = m_Y;
    active = true;
    currentExplositionDuration = explosionDuration;
}

void Explosion::Update()
{
    if( targetFire == nullptr ) return;

    if( targetFire->IsActive() )
    {
        pos.y = (targetFire->pos.y - (size.y / 2) );
    }

}

void Explosion::Draw()
{
    if( active )
    {
        NF_ShowSprite(0,spriteID, true);
        NF_MoveSprite(0,spriteID,pos.x,pos.y);
    }
}
