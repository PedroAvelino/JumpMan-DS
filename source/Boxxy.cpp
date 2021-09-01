#include "Boxxy.hpp"

Boxxy::Boxxy()
:speed(2.0)
{
    pos.x = 10;
    pos.y = 10;

    size.x = 24.0f;
    size.y = 24.0f;
}

void Boxxy::Draw()
{
    glBoxFilled(pos.x, pos.y , (pos.x + size.x) , (pos.y + size.y) ,RGB15(202,137,240));
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

    if( held & KEY_UP )
    {
        Move(Vector2(0.0, -1.0));
    }

    if( held & KEY_DOWN )
    {
        Move(Vector2(0.0, 1.0));
    }
}

Boxxy::~Boxxy()
{
}