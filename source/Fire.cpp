#include "Fire.hpp"
#include "SpriteIDServer.hpp"
#include "GameScore.hpp"

Fire::Fire( const Vector2& p_spawnPos )
:speed(2)
{
    pos = p_spawnPos;
    startX = pos.x;
    size.x = 16.0f;
    size.y = 16.0f;
    speed = 3;
    active = false;
    spriteID = SpriteIDServer::GetInstance().GetID();

    //Create it and then hide it
    NF_CreateSprite(0,spriteID,2,2, pos.x, pos.y);
    NF_ShowSprite(0,spriteID, false);
}

int Fire::ClassType()
{
    return 5;
}

void Fire::Draw()
{
    if( active )
    {
        NF_ShowSprite(0,spriteID, true);
        NF_MoveSprite(0,spriteID,pos.x,pos.y);
    }
}

void Fire::Update()
{
    if( active == false ) return;
    TravelToOrigin();
}

void Fire::Destroy()
{
    NF_ShowSprite(0,spriteID, false);
    active = false;
}

void Fire::TravelToOrigin()
{
    float dir = startX - pos.x;
    if( dir > 0 )
    {
        pos.x += speed;
        if( pos.x >= startX )
        {
            Destroy();
            return;
        }
    }
    else
    {
        pos.x -= speed;
        if( pos.x <= startX )
        {
            Destroy();
            return;
        }
    }
}


Fire::~Fire()
{

}