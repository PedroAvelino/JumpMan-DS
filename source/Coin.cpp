#include "Coin.hpp"
#include "SpriteIDServer.hpp"
#include "GameScore.hpp"

Coin::Coin( const Vector2& p_spawnPos )
:speed(2)
{
    pos = p_spawnPos;
    size.x = 16.0f;
    size.y = 16.0f;
    active = false;
    spriteID = SpriteIDServer::GetInstance().GetID();
}

void Coin::Draw()
{
    if( active )
    {
        NF_ShowSprite(0,spriteID, true);
        NF_CreateSprite(0,spriteID,2,2, pos.x, pos.y);
    }
}

void Coin::Update()
{
    if( active == false ) return;
    if( pos.y > 192 + size.y )
    {
        Destroy();
    }
    pos.y += speed;

}

void Coin::OnCollision( Entity* p_entity )
{
}

void Coin::Destroy()
{
    active = false;
    GameScore::GetInstance().currentCoinsOnScreen--;
    NF_ShowSprite(0,spriteID, false);
}

Coin::~Coin()
{

}