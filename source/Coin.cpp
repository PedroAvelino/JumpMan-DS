#include "Coin.hpp"

Coin::Coin( const Vector2& p_spawnPos )
:speed(2)
{
    pos = p_spawnPos;
    size.x = 10;
    size.y = 10;
}

void Coin::Draw()
{
    glBoxFilled(pos.x, pos.y , (pos.x + size.x) , (pos.y + size.y) ,RGB15(252,240,3));
}

void Coin::Update()
{
    pos.y += speed;
}

void Coin::OnCollision( Entity* p_entity )
{

}

Coin::~Coin()
{

}