#include "Bomb.hpp"
#include "SpriteIDServer.hpp"
#include "GameScore.hpp"

Bomb::Bomb( const Vector2& p_spawnPos )
:speed(2)
{
    pos = p_spawnPos;
    size.x = 16.0f;
    size.y = 16.0f;
    active = false;
    spriteID = SpriteIDServer::GetInstance().GetID();

    //Create it and then hide it
    NF_CreateSprite(0,spriteID,3,3, pos.x, pos.y);
    NF_ShowSprite(0,spriteID, false);
}

int Bomb::ClassType()
{
    return 4;
}

void Bomb::Draw()
{
    if( active )
    {
        NF_ShowSprite(0,spriteID, true);
        NF_MoveSprite(0,spriteID,pos.x,pos.y);
    }
}

void Bomb::Explode()
{
    if( active == false ) return;
    //Boom

    if( GameScore::GetInstance().isFireOn == false )
    {
        GameScore::GetInstance().explosionLocation =  Vector2(pos.x,pos.y);
        GameScore::GetInstance().isFireOn = true;
        GameScore::GetInstance().createFire = true;
    }

    Destroy();
}

void Bomb::Update()
{
    if( active == false ) return;

    if( pos.y >= heightToExplode)
    {
        Explode();
        return;
    }

    if( pos.y > 192 + size.y )
    {
        Destroy();
    }
    pos.y += speed;

}

void Bomb::SetHeightToExplode( float pY )
{
    heightToExplode = pY;
}

void Bomb::Destroy()
{
    NF_ShowSprite(0,spriteID, false);
    active = false;
}

Bomb::~Bomb()
{

}