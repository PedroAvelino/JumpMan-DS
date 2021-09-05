#include "Coin.hpp"

Coin::Coin( const Vector2& p_spawnPos )
:speed(2)
{
    pos = p_spawnPos;
    size.x = 16.0f;
    size.y = 16.0f;
    active = true;
}

void Coin::Draw()
{      
    NF_CreateSprite(0,7,2,2, pos.x, pos.y);
}

void Coin::Update()
{
    if( pos.y > 192 + size.y )
    {
        pos.y = 0;
    }
    pos.y += speed;

}

void Coin::OnCollision( Entity* p_entity )
{
}

void Coin::Destroy()
{
    active = false;
    NF_DeleteSprite(0,7);
}

Coin::~Coin()
{

}