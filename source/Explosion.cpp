#include "Explosion.hpp"
#include "SpriteIDServer.hpp"
#include "GameScore.hpp"

Explosion::Explosion( float m_X ) : 
explosionDuration(45), currentExplositionDuration(0)
{
    size.x = 32.0f;
    size.y = 64.0f;
    
    pos.x = m_X;

    active = false;
    spriteID = SpriteIDServer::GetInstance().GetID();

    //Create it and then hide it
    NF_CreateSprite(0,spriteID,4,4, pos.x, pos.y);
    NF_ShowSprite(0,spriteID, false);
}
int Explosion::ClassType()
{
    return 6;
} 

void Explosion::SetActive( float m_Y )
{
    if( active ) return;

    pos.y = (m_Y - (size.y / 2) );
    active = true;
    currentExplositionDuration = explosionDuration;
}

void Explosion::Update()
{
    if( active )
    {
        currentExplositionDuration -= 1;
        if( currentExplositionDuration <= 0 )
        {
            Destroy();
        }
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

void Explosion::Destroy()
{
    NF_ShowSprite(0,spriteID, false);
    active = false;
}