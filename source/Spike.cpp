#include "Spike.hpp"
#include "SpriteIDServer.hpp"
#include "GameScore.hpp"

#define SPIKE 1

Spike::Spike( const Vector2& p_spawnPos )
:speed(2)
{
    pos = p_spawnPos;
    size.x = 16.0f;
    size.y = 16.0f;
    active = false;
    spriteID = SpriteIDServer::GetInstance().GetID();
}

int Spike::ClassType()
{
    return 1;
}

void Spike::Draw()
{
    if( active )
    {
        NF_ShowSprite(0,spriteID, true);
        NF_CreateSprite(0,spriteID,3,3, pos.x, pos.y);
    }
}

void Spike::Update()
{
    if( active == false ) return;
    if( pos.y > 192 + size.y )
    {
        Destroy();
    }
    pos.y += speed;

}

void Spike::OnCollision( Entity* p_entity )
{
}

void Spike::Destroy()
{
    active = false;
    GameScore::GetInstance().currentSpikesOnScreen--;
    NF_ShowSprite(0,spriteID, false);
}

Spike::~Spike()
{

}