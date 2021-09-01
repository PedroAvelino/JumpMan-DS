#include "Boxxy.hpp"

Boxxy::Boxxy()
:speed(2.0)
{
    pos.x = 10;
    pos.y = 10;
    size = 24;
}

void Boxxy::Draw()
{
    glBoxFilled(pos.x, pos.y , (pos.x + size) , (pos.y + size) ,RGB15(202,137,240));
}

void Boxxy::Move( const Vector2& p_direction )
{
    Vector2 direction;
    direction = p_direction;

    VectorScale(direction, direction, speed);

    VectorAdd( pos, pos, direction );
}

void Boxxy::Update()
{
    int held = keysHeld();

    if( held & KEY_LEFT )
    {
        Move(Vector2(-1.0, 0.0));
    }

    if( held & KEY_RIGHT )
    {
        Move(Vector2(1.0, 0.0));
    }
}

Boxxy::~Boxxy()
{
}