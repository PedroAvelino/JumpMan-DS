#include "Reverse.hpp"
#include "SpriteIDServer.hpp"
#include "GameScore.hpp"


Reverse::Reverse( const Vector2& p_spawnPos )
:speed(2)
{
    pos = p_spawnPos;
    size.x = 16.0f;
    size.y = 16.0f;
    active = false;
    spriteID = SpriteIDServer::GetInstance().GetID();

    //Create it and then hide it
    NF_CreateSprite(0,spriteID,2,2, pos.x, pos.y);
    NF_ShowSprite(0,spriteID, false);

}

int Reverse::ClassType()
{
    return 3;
}
void Reverse::Draw()
{
    if( active )
    {
        NF_ShowSprite(0,spriteID, true);
        NF_MoveSprite(0, spriteID, pos.x, pos.y );
    }
}


void Reverse::Update()
{
    if( active == false ) return;
    if( pos.y > 192 + size.y )
    {
        Destroy();
    }
    pos.y += speed;

}

void Reverse::Destroy()
{
    NF_ShowSprite(0,spriteID, false);
    active = false;
}

Reverse::~Reverse()
{

}