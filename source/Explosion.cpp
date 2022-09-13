#include "Explosion.hpp"
#include "SpriteIDServer.hpp"
#include "GameScore.hpp"
#include <time.h>

Explosion::Explosion( float m_X ) : explosionDuration(2.0f), currentExplositionDuration(0.0f)
{
    size.x = 32.0f;
    size.y = 64.0f;
    
    pos.x = m_X;

    active = false;
    spriteID = SpriteIDServer::GetInstance().GetID();

    //Create it and then hide it
    NF_CreateSprite(0,spriteID,2,2, pos.x, pos.y);
    NF_ShowSprite(0,spriteID, false);
}

void Explosion::SetActive( float m_Y )
{
    pos.y = m_Y;
    active = true;
    currentExplositionDuration = explosionDuration;
}

void Explosion::Update()
{
    //TODO: Deal with time

}

int Explosion::ClassType()
{
    return 6;
} 