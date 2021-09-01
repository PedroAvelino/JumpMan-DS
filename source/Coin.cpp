#include "Coin.hpp"

Coin::Coin( const Vector2& p_spawnPos )
{
    pos = p_spawnPos;
}

void Coin::Draw()
{
    glBoxFilled(pos.x, pos.y , (pos.x + size.x) , (pos.y + size.y) ,RGB15(252,240,3));
}

void Coin::Update()
{
    
}

void Coin::OnCollision( Entity& p_entity )
{

}

Coin::~Coin()
{

}