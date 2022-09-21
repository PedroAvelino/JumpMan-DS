#include "Fire.hpp"
#include "SpriteIDServer.hpp"
#include "GameScore.hpp"
#include "Explosion.hpp"

#define ROTATION_RATE 30

Fire::Fire( const Vector2& p_spawnPos, Explosion* m_explosion )
:speed(2),endTravel(false),rotationProgress(-512)
{
    pos = p_spawnPos;
    explosion = m_explosion;
    startX = pos.x;
    size.x = 16.0f;
    size.y = 16.0f;
    speed = 3;
    active = false;
    spriteID = SpriteIDServer::GetInstance().GetID();

    //Create it and then hide it
    NF_CreateSprite(0,spriteID,6,6, pos.x, pos.y);
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
        NF_EnableSpriteRotScale(0,spriteID, 12, false );

        rotationProgress += ROTATION_RATE;
        if (rotationProgress >= 512 ) 
        {
            rotationProgress = -512;
        }
        NF_SpriteRotScale(0,12, rotationProgress ,256,256);
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
    endTravel = false;
}

void Fire::TravelToOrigin()
{
    float dir = startX - pos.x;
    if( dir > 0 )
    {
        pos.x += speed;
        if( pos.x >= startX )
        {
            explosion->SetActive(pos.y);
            Destroy();
            return;
        }
    }
    else
    {
        pos.x -= speed;
        if( pos.x <= startX )
        {
            explosion->SetActive(pos.y);
            Destroy();
            return;
        }
    }
}


Fire::~Fire()
{

}