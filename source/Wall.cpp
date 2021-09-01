#include "Wall.hpp"


Wall::Wall( bool p_Left )
:isLeft(p_Left)
{
    size.x = 24.0f;
    size.y = 192.0f;

    if(p_Left)
    {
        pos.x = 0;
        pos.y = 0;
    }
    else
    {
        pos.x = 232;
        pos.y = 0;
    }
}


void Wall::Draw()
{
    glBoxFilled(pos.x, pos.y , (pos.x + size.x) , (pos.y + size.y) ,RGB15(245,66,108));
}

Wall::~Wall()
{
}